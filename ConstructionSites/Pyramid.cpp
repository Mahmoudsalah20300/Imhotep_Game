

#include "Pyramid.hpp"



Pyramid::Pyramid(int site_id, int playernumbers):site_id_(site_id), change_unload_order(false)
{
    playerspoints.resize(playernumbers,0);

}

void Pyramid::setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order)
{
  auto [new_change_unload_order, new_unload_order] = new_order;
  change_unload_order = new_change_unload_order;
  unload_order = new_unload_order;
}
void Pyramid::unloadShip(Ship ship)
{   
    for(auto& player_points : playerspoints)
    {
        player_points = 0;
    }
    if(change_unload_order == true)
    {
        for(int stone : unload_order)
        {
            input_vector.push_back(stone); 
            allelements.push_back(stone);
        }
        change_unload_order = false;
        unload_order.clear();
        addStoneOnthePyramid();
        return;
    }
    for(auto it = ship.getStonesOnShip().begin() ; it != ship.getStonesOnShip().end() ; ++it)
    {
        if(*it != -1)
        {
            input_vector.push_back(*it); 
            allelements.push_back(*it);
        }
    }
    addStoneOnthePyramid();
}


bool Pyramid::is_full_level(std::vector<std::vector<int>>& level)
{
    for(size_t i = 0; i < level.size(); ++i)
    {
        for(size_t j = 0; j < level.size(); ++j)
        {
            if(level.at(j).at(i) == -1)
            {
                current_position = {j , i}; 
                return false;
            }
        }
    }
    current_position = {0,0};
    return true;
}


void Pyramid:: addStoneOnthePyramid()
{   
    for(size_t i = 0; i < input_vector.size(); ++i)
    { 
        if(!is_full_level(pyramid.at(0)))
        {
            pyramid.at(0).at(current_position.first).at(current_position.second) = input_vector.at(i);
            playerspoints.at(input_vector.at(i)) += 
                                pyramidpoints.at(0).at(current_position.first).at(current_position.second);
        }
        else if(!is_full_level(pyramid.at(1)))
        {
            pyramid.at(1).at(current_position.first).at(current_position.second) = input_vector.at(i);
            playerspoints.at(input_vector.at(i)) += 
                                pyramidpoints.at(1).at(current_position.first).at(current_position.second);
        }
        else if(!is_full_level(pyramid.at(2)))
        {
            pyramid.at(2).at(current_position.first).at(current_position.second) = input_vector.at(i);
            playerspoints.at(input_vector.at(i)) += 
                                pyramidpoints.at(2).at(current_position.first).at(current_position.second);
        }
        else
        {
            otherStones.push_back(input_vector.at(i));
            playerspoints.at(input_vector.at(i)) += 1 ;
        }
    }

    input_vector.resize(0,0);
}



std::vector<int> Pyramid::evaluatePoints()
{
    return playerspoints;
}

int Pyramid::getSiteId() const
{
    return site_id_;
}


std::vector<int> Pyramid::getallelements()
{
    return allelements;
} 

 
