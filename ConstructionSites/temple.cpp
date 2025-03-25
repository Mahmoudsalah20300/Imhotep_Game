

#include "temple.hpp"



temple::temple(int site_id, int player_count) : siteid_(site_id), player_count_(player_count), 
                                                change_unload_order(false)
{
  points_.resize(player_count, 0);
  if ( player_count == 2 )
  {
    temple_length_ = 4;
  }  
  else
  { 
    temple_length_ = 5;  
  }

  creatnewLevel_();
}

void temple::unloadShip(Ship ship)
{
  std::vector<int> currentShipLoad = ship.getStonesOnShip();
  if ( change_unload_order == true )
  {
    for ( int stone : unload_order )
    {
      shipLoad.push_back(stone);
      AllElmenets_.push_back(stone);
    }
    change_unload_order = false;
    unload_order.clear();
    addStonesOntemple_();
    shipLoad.clear();
    return;
  }
  for (auto it = currentShipLoad.begin(); it != currentShipLoad.end(); ++it)
  {
    if (*it != -1)
    {
      shipLoad.push_back(*it);
      AllElmenets_.push_back(*it);
    }
  }
  addStonesOntemple_();
  shipLoad.clear();
}

void temple::addStonesOntemple_()
{
  for (auto it = shipLoad.begin(); it != shipLoad.end(); ++it)
  {
    if (!isempty_(templeLevel_.at(level_))) //ship 0 0 1 // 0 1 0 -1 -1
    {
      templeLevel_.at(level_).at(position_) = *it;
    }
    else{
      ++level_;
      creatnewLevel_();
      position_ = 0;
      templeLevel_.at(level_).at(position_) = *it;
    }
  }
}

bool temple::isempty_(std::vector<int>& level)
{
  for (auto it = level.begin(); it != level.end(); ++it)
  {
    if (*it == -1 )
    {
      position_ = std::distance(level.begin(), it);
      return false;
    }    
  }
  return true;
}

std::vector<int> temple::evaluatePoints()
{
  for (size_t i = 0; i < points_.size(); i++)
  {
    points_.at(i) = 0;  
  }

  for (int i = 0; i <= position_; ++i) //for the last level
  {
    points_.at(templeLevel_.at(level_).at(i)) += 1;
  }
  
  if (level_ > 0)
  {
    for (int i = position_ + 1; i < temple_length_; i++)
    {
      points_.at(templeLevel_.at(level_- 1).at(i)) += 1;
    }  
  }

  return points_;
}

int temple::getLength()
{
  return AllElmenets_.size();
}

std::vector<int> temple::getallelements()
{
  return AllElmenets_;
}

void temple::creatnewLevel_()
{
  if(temple_length_ == 4)
  {
    std::vector <int> newLevel = {-1, -1, -1, -1};
    templeLevel_.push_back(newLevel);
  }
  else
  {
    std::vector <int> newLevel = {-1, -1, -1, -1, -1};
    templeLevel_.push_back(newLevel);
  }
}

int temple::getSiteId() const
{
  return siteid_;
}

void temple::setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order)
{
  auto [new_change_unload_order, new_unload_order] = new_order;
  change_unload_order = new_change_unload_order;
  unload_order = new_unload_order;
}

