#include "suplySled.hpp"

//--------------------------------------------------------------------------------------------------------------------
SupleySled::SupleySled(const int supley_sled_id, const int storrage, int stones)
        : supley_sled_id_(supley_sled_id), storrage_(storrage), initial_stone_count_(stones) {}

//--------------------------------------------------------------------------------------------------------------------
SupleySled::~SupleySled() {}

//--------------------------------------------------------------------------------------------------------------------
int SupleySled::getStorrageStatus()
{
    return initial_stone_count_;
}

//--------------------------------------------------------------------------------------------------------------------
int SupleySled::placeNewStones(int added_stones)
{   
    initial_stone_count_ += added_stones; //+ 3 new stones  // or -1 when moving to ship
    //if more than 5 stones after adding, stones will remain 5
    if(initial_stone_count_ > 5)
    {   
        //added_stones 5(full) - initial_stone_count before adding 3 stones
        added_stones = 5 - (initial_stone_count_ - 3);
        initial_stone_count_ = 5;
    }
    return added_stones;
}
