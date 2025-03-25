#include "ship.hpp"
#include "player.hpp"
#include <iostream>

//--------------------------------------------------------------------------------------------------------------------
Ship::Ship(const int ship_id, const int ship_lenght, int current_load, bool sailed)
            : ship_id_(ship_id), ship_lenght_(ship_lenght), current_load_(current_load), sailed_(sailed)
            {}

//--------------------------------------------------------------------------------------------------------------------
Ship::~Ship() {}

//--------------------------------------------------------------------------------------------------------------------
void Ship::setShipDetails(const int lenght)
{   
    //set current load to zero at beginn of a new round
    current_load_ = 0;
    //set ship lenght
    ship_lenght_ = lenght;
    //capacity vector lenght = ship_lenght
    capacity_.resize(ship_lenght_);
    //set capacity to minus1
    for(auto& capacity : capacity_)
    {
        capacity = -1;
    }

    sailed_ = false;
    //set minimum load to depart
    if(lenght == 1)
    {
        min_load_ = lenght;
    }
    else
    {
        min_load_ = lenght - 1;
    }
}

//--------------------------------------------------------------------------------------------------------------------
void Ship::addStone(int stone_id, int position)
{
    capacity_[position] = stone_id;
    setCurrentLoad();
}

//--------------------------------------------------------------------------------------------------------------------
void Ship::setCurrentLoad()
{
    current_load_++;
}

//--------------------------------------------------------------------------------------------------------------------
void Ship::setShipStatus(const bool sailed)
{
    sailed_ = sailed;
}

//--------------------------------------------------------------------------------------------------------------------
bool Ship::checkSailAvailability()
{
    if(current_load_ >= min_load_)
    {
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------------------------
bool Ship::getShipStatus()
{
    return sailed_;
}

//--------------------------------------------------------------------------------------------------------------------
int Ship::getShipId()
{
    return ship_id_;
}

//--------------------------------------------------------------------------------------------------------------------
const std::vector<int>& Ship::getStonesOnShip() const
{
    return capacity_;
}

int Ship::getStonesOnShipAmount()
{
    int total_stones = 0;
    for (int stone : capacity_)
    {
        if (stone != -1)
        {
            total_stones ++;
        }
    }
    return total_stones;
}

//--------------------------------------------------------------------------------------------------------------------
int Ship::getShipLenght()
{
    return ship_lenght_;
}

//--------------------------------------------------------------------------------------------------------------------
int Ship::getShipCurrentLoad()
{
    return current_load_;
}

//--------------------------------------------------------------------------------------------------------------------
int Ship::getStoneOnPosition(int position)
{
    int stone = capacity_[position];
    return stone;
}
