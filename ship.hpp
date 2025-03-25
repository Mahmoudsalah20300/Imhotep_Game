/**
 * The Ship class represents a ship in the game.
 * It manages the ship's ID, length, current load, and capacity. It also provides functions for adding stones,
 * checking if the ship can sail, and managing the ship's status.
 */

#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>

class Ship
{
    private: 
        int ship_id_;
        int ship_lenght_;
        std::vector<int> capacity_;
        int min_load_;
        int current_load_;
        bool sailed_;

    public:
        /**
         * Constructor
         * 
         * Initializes a Ship object with the given ship ID, ship length, current load, and sailed status.
         * 
         * @param ship_id The ID of the ship.
         * @param ship_lenght The length of the ship.
         * @param current_load The current load on the ship.
         * @param sailed The sailing status of the ship (true if sailed, false otherwise).
         */
        Ship(const int ship_id, const int ship_lenght, int current_load, bool sailed);

        /**
         * Destructor
         * 
         * Cleans up resources used by the Ship object when it is destroyed.
         */
        ~Ship();

        
        /**
         * Sets the details of the ship, including its length, capacity, and minimum load.
         * 
         * Resizes the capacity vector to the ship's length and sets the capacity to -1.
         * Sets the minimum load required for the ship to depart based on its length.
         * 
         * @param lenght The length of the ship.
         */
        void setShipDetails(const int lenght);

        /**
         * Adds a stone to the ship at the specified position.
         * 
         * Updates the capacity at the given position with the stone ID and recalculates the current load.
         * 
         * @param stone_id The ID of the stone (same as player ID) to be added.
         * @param position The position on the ship where the stone will be placed.
         */
        void addStone(int stone_id, int position);

        /**
         * Increases the current load by one.
         * 
         * This function is used when a new stone is added to the ship.
         */
        void setCurrentLoad();

        /**
         * Sets the sailing status of the ship.
         * 
         * @param sailed The sailing status to set (true if sailed, false otherwise).
         */
        void setShipStatus(const bool sailed);

        /**
         * Checks if the ship has enough stones to sail(minimum load).
         * 
         * The ship can sail if the current load is greater than or equal to the minimum load.
         * 
         * @return true if the ship can sail (current load >= minimum load), false otherwise.
         */
        bool checkSailAvailability();

        /**
         * Gets the sailing status of the ship.
         * 
         * @return true if the ship has sailed, false otherwise.
         */
        bool getShipStatus();

        
        /**
         * Gets the ship's ID.
         * 
         * @return The ID of the ship.
         */
        int getShipId();

        /**
         * Gets the list of stones currently on the ship.
         * 
         * @return A constant reference to the vector of stones on the ship.
         */
        const std::vector<int>& getStonesOnShip() const;

        /**
         * Gets the length of the ship.
         * 
         * @return The length of the ship.
         */
        int getShipLenght();

        /**
         * Retrieves the number of stones currently on the ship.
         * 
         * This function iterates over the ship's capacity vector and counts how many positions contain a stone (excluding -1).
         * 
         * @return The total number of stones currently on the ship.
         */
        int getStonesOnShipAmount();

        /**
         * Retrieves the current load of the ship.
         * 
         * This function returns the current number of stones on the ship.
         * 
         * @return The current load (number of stones) on the ship.
         */
        int getShipCurrentLoad();

        /**
         * Retrieves the stone at a specific position on the ship.
         * 
         * This function returns the stone ID located at a given position on the ship.
         * 
         * @param position The position on the ship where the stone is located.
         * @return The stone ID at the specified position.
         */
        int getStoneOnPosition(int position);
};

#endif
