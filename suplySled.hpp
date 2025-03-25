/**
 * The SupleySled class represents a supply sled that holds stones.
 * Every Player has one SupleySled
 * It manages the storage of stones, including adding new stones, checking the storage status, 
 * and ensuring that the sled does not exceed its maximum capacity.
 */

#ifndef SUPLEYSLED_HPP
#define SUPLEYSLED_HPP

class SupleySled
{
    private:
        int supley_sled_id_;
        int storrage_;
        int initial_stone_count_;

    public:
        /**
         * Constructor
         * 
         * Initializes a SupleySled object with the given sled ID, storage capacity, and initial stone count.
         * 
         * @param supley_sled_id The ID of the supply sled.
         * @param storrage The storage capacity of the sled.
         * @param stones The initial number of stones on the sled.
         */
        SupleySled(const int supley_sled_id, const int storrage, int stones);
        
        /**
         * Destructor
         * 
         * Cleans up resources used by the SupleySled object when it is destroyed.
         */
        ~SupleySled();

        /**
         * Gets the number of stones currently stored on the Supley Sled.
         * 
         * @return The current number of stones stored in the sled.
         */
        int getStorrageStatus();

        /**
         * Places new stones on the Supley Sled, up to a maximum of 5 stones.
         * 
         * If more than 5 stones are added, the sled will only hold 5 stones, and the excess stones will not be placed.
         * This function also returns the number of stones actually added or removed.
         * 
         * @param added_stones The number of stones to add (positive) or remove (negative).
         * @return The number of stones actually added or removed.
         */
        int placeNewStones(int added_stones);
};

#endif
