#include "Obelisk.hpp"




Obelisk::Obelisk(const int site_id, int obelisk_number)
                :change_unload_order(false), site_id_(site_id), obelisk_number_(obelisk_number)
                {resizeObeliskVector();}


Obelisk::~Obelisk() {}


void Obelisk::resizeObeliskVector()
{
    obelisk_height_.resize(obelisk_number_);
    points_.resize(obelisk_number_);

    for(int i = 0; i < obelisk_number_; i++)
    {
        obelisk_height_[i] = 0;
        points_[i] = 0;
    }
}


void Obelisk::setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order)
{
  auto [new_change_unload_order, new_unload_order] = new_order;
  change_unload_order = new_change_unload_order;
  unload_order = new_unload_order;
}

int Obelisk::getSiteId() const
{
    return site_id_;
}


std::vector<int> Obelisk::getObeliskHeights() const
{
    return obelisk_height_;
}


void Obelisk::unloadShip(Ship ship)
{
    std::vector<int> stones_on_ship = ship.getStonesOnShip();
        if(change_unload_order == true)
    {
        for(int stone : unload_order)
        {
            placeStoneOnObelisk(stones_on_ship[stone]);
        }
        change_unload_order = false;
        unload_order.clear();
        return;
    }
    for(int i = (stones_on_ship.size() - 1); i >= 0; i--)
    {
        if(stones_on_ship[i] != -1)
        {
            placeStoneOnObelisk(stones_on_ship[i]);
        }
    }
}

// This function is used to put a stone on the Obelisk belong to the player's id 
void Obelisk::placeStoneOnObelisk(int stone_id)
{
    obelisk_height_[stone_id]++;
}

// This function is constructed to evaluate points of the player based on the number of player
std::vector<int> Obelisk::evaluatePoints()
{   
    std::vector <int> rank_points;
    if(!rank_points.empty())
    {
        rank_points.clear();
    }

    if(obelisk_number_ == 2)
    {   
        rank_points.push_back(1);
        rank_points.push_back(10);
    }   
    if(obelisk_number_ == 3)  // if the number of players/obelisks = 3 
    {   
        rank_points.push_back(1);
        rank_points.push_back(6);
        rank_points.push_back(12);
    }
    if(obelisk_number_ == 4) // if the number of players/obelisks = 4 
    {
        rank_points.push_back(1);
        rank_points.push_back(5);
        rank_points.push_back(10);
        rank_points.push_back(15);
    }

    setPointsForPlayer (rank_points);

    return points_;
}

void Obelisk::setPointsForPlayer (std::vector<int> rank_points)
{
    int rank_count;
    int equal_count;


    for (int i = 0; i < obelisk_number_; i++)
    {
        equal_count = 0;
        rank_count = 0;

        for (int x = 0; x < obelisk_number_; x++)
        {
            if (i != x)
            {
                if (obelisk_height_[i] > obelisk_height_[x])
                {
                    rank_count++;  
                }
                if (obelisk_height_[i] == obelisk_height_[x])
                {
                    equal_count++;
                }
            }
        }

        if (obelisk_height_[i] > 0)
        {
            if (equal_count == 0)
            {
                points_[i] = rank_points[rank_count];
            }
            else
            {
                for (int z = rank_count; z <= (equal_count + rank_count); z++)
                {
                    points_[i] += rank_points[z];
                }
                points_[i] = points_[i] / (equal_count + 1);
            }
        }
    }
}
