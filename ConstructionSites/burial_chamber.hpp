/**
 * This class is the Burial Chamber.
 * This class inherits the ConstructionSite class. 
 * 
 * Group : 19
 * Author : 12241141 
 * 
 */

#ifndef BURIAL_CHAMBER
#define BURIAL_CHAMBER

#include "ConstructionSiteType.hpp"

class BurialChamber: public ConstructionSite
{
  private:
    int site_id_;
    int players_;
    std::vector<std::vector<int>> area_;
    std::vector<int> points_;
    std::vector<int> elements_;
    bool change_unload_order;
    std::vector<int> unload_order;

    /**
     * Finds the stone ID for a player.
     * 
     * Searches the points area for the given stone ID and updates the row and column indices.
     * 
     * @param row Reference to the row index to be updated.
     * @param col Reference to the column index to be updated.
     * @param stone_id The ID of the stone to find.
     * @param points_area_ A reference to the points area to search within.
     * @return True if the stone is found, otherwise false.
     */
    bool findPlayerStoneId(size_t &row, size_t &col, int stone_id, std::vector<std::vector<int>> points_area_);

    /**
     * Checks for a neighboring stone.
     * 
     * Determines whether a given stone has a neighbor in the points area.
     * 
     * @param stone_id The ID of the stone to check.
     * @param row Reference to the row index of the stone.
     * @param col Reference to the column index of the stone.
     * @param points_area_ A reference to the points area to search within.
     * @param place_holder A placeholder value for comparison.
     * @return True if a neighbor is found, otherwise false.
     */
    bool checkForNeighbour(int stone_id, size_t &row, size_t &col, std::vector<std::vector<int>> &points_area_, int place_holder);

    /**
     * Calculates points for a group of stones.
     * 
     * Computes the total points for a given group of stones.
     * 
     * @param group_stones The number of stones in the group.
     * @return The calculated points.
     */
    int calculatePoints(int group_stones);

  public:
    /**
     * Constructor
     * 
     * Initializes a BurialChamber object with the given site ID and number of players.
     * 
     * @param site_id The unique ID of the burial chamber.
     * @param players The number of players interacting with the burial chamber.
     */
    BurialChamber(int const site_id, int const players);

    /**
     * Destructor
     * 
     * Cleans up any resources used by the BurialChamber object.
     */
    ~BurialChamber();

    /**
     * Gets the site ID of the burial chamber.
     * 
     * @return The unique site ID.
     */
    int getSiteId() const override;

    /**
     * Sets the unload order for the burial chamber.
     * 
     * This method overrides the base class method to set the unload order.
     * 
     * @param new_order A pair consisting of a boolean flag and a vector of integers representing the new unload order.
     */
    void setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order) override;

    /**
     * Unloads a ship at the burial chamber.
     * 
     * This method overrides the base class method to handle unloading ships.
     * 
     * @param ship The ship to unload.
     */
    void unloadShip(Ship ship) override;

    /**
     * Gets all elements in the burial chamber.
     * 
     * @return A vector of integers representing all elements in the burial chamber.
     */
    std::vector<int> getAllElements();

    /**
     * Evaluates the points for the burial chamber.
     * 
     * This method overrides the base class method to calculate points based on the burial chamber's state.
     * 
     * @return A vector of integers representing the evaluated points.
     */
    std::vector<int> evaluatePoints() override;

};            

#endif
