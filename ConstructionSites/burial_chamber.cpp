#include "burial_chamber.hpp"


BurialChamber::BurialChamber(int const site_id, int const players)
                              : site_id_(site_id), players_(players), change_unload_order(false)
{
  area_.resize(3, std::vector<int> (1, -1));
  points_.resize(players_, 0);
}

BurialChamber::~BurialChamber() {}

int BurialChamber::getSiteId() const
{
  return site_id_;
}

void BurialChamber::setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order)
{
  auto [new_change_unload_order, new_unload_order] = new_order;
  change_unload_order = new_change_unload_order;
  unload_order = new_unload_order;
}

void BurialChamber::unloadShip(Ship ship)
{
  std::vector<int> stones_on_ship = ship.getStonesOnShip();
  bool placed_stone;

  for(size_t i = 0; i < stones_on_ship.size(); i++)
  {
    placed_stone = false;
    if(stones_on_ship[i] != -1)
    {
      if(!area_.empty() && !area_.back().empty() && area_.back().back() != -1)
      {
        for(auto& row : area_)
        {
          row.resize(row.size() + 1, -1);
        }
      }

      for(size_t col = 0; col < area_[0].size(); col++)
      {
        for(size_t row = 0; row < area_.size(); row++)
        {
          if(area_[row][col] == -1)
          {
            area_[row][col] = stones_on_ship[i];
            elements_.push_back(stones_on_ship[i]);
            placed_stone = true;
            break;
          }
        }
        if(placed_stone == true)
        {
          break;
        }
      }
    }
  }
}

std::vector<int> BurialChamber::getAllElements()
{
  return elements_;
}


std::vector<int> BurialChamber::evaluatePoints()
{
  std::vector<std::vector<int>> points_area_;
  size_t row = 0;
  size_t col = 0;
  int counter = 0;
  int adding_points;
  int exit_group = 0;

  points_area_ = area_;

  int i = 0;
  while(i < players_)
  {
    if(findPlayerStoneId(row, col, i, points_area_))
    {
      counter++;
      exit_group = 0;
      while(exit_group == 0)
      {
        if(checkForNeighbour(i, row, col, points_area_, -2))
        {
          counter++;
        }
        else
        {
          if(!checkForNeighbour(-2, row, col, points_area_, -3))
          {
            row = 0;
            col = 0;
            adding_points= calculatePoints(counter);
            points_[i] += adding_points;
            counter = 0;
            exit_group = 1;
          }
        }
      }
    }
    else
    {
      points_area_ = area_;
      i++;

    }
  }
  return points_;
}

bool BurialChamber::findPlayerStoneId(size_t &row, size_t &col, int stone_id, std::vector<std::vector<int>> points_area_)
{
  for(size_t y = 0; y < area_.size(); y++)
  {
    for(size_t x = 0; x < area_[0].size(); x++)
    {
      if(points_area_[y][x] == stone_id)
      {
        row = y;
        col = x;
        return true;
      }
    }
  }
  return false;
}

bool BurialChamber::checkForNeighbour(int stone_id, size_t &row, size_t &col,
                                      std::vector<std::vector<int>> &points_area_, int place_holder)
{
  points_area_[row][col] = place_holder;

  if(row > 0) //check up
  {
    if(points_area_[row - 1][col] == stone_id)
    {
      row--;
      return true;
    }
  }
  if(col < (points_area_[0].size() - 1)) //check right
  {
    if(points_area_[row][col + 1] == stone_id)
    {
      col++;
      return true;
    }
  }
  if(row < (points_area_.size() - 1)) //check down
  {
    if(points_area_[row + 1][col] == stone_id)
    {
      row++;
      return true;
    }
  }
  if(col > 0) //check left
  {
    if(points_area_[row][col - 1] == stone_id)
    {
      col--;
      return true;
    }
  }

  return false;
}

int BurialChamber::calculatePoints(int group_stones)
{
  if(group_stones == 1)
  {
    return 1;
  }
  if(group_stones == 2)
  {
    return 3;
  }
  if(group_stones == 3)
  {
    return 6;
  }
  if(group_stones == 4)
  {
    return 10;
  }
  if(group_stones == 5)
  {
    return 15;
  }
  if(group_stones > 5)
  {
    return (group_stones - 5) * 2 + 15;
  }

  return 0;
}


