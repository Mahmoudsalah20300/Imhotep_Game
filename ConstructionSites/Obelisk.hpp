
/**
 * Obelisk class contains all the prototypes for the Obelisk.
 * Obelisk inherits the ConstructionSite class.
 * 
 * Group : 19
 * Author : 12241141
 */


#ifndef OBELISK_HEADER__
#define OBELISK_HEADER__

#include "ConstructionSiteType.hpp"
#include <vector>
#include <algorithm>

class Obelisk : public ConstructionSite
{
    private:
    bool change_unload_order;
    std::vector<int> unload_order;
    int site_id_;
    int obelisk_number_;
    std::vector<int> obelisk_height_;
    std::vector<int> points_;

    /**
     * Resizes the obelisk height vector to accommodate additional entries.
     */
    void resizeObeliskVector();

    /**
     * Places a stone on the obelisk at the specified position.
     * 
     * @param stone_id The ID of the stone to be placed.
     */
    void placeStoneOnObelisk(int stone_id);

    /**
     * Sets the points for players based on their ranks.
     * 
     * @param first_rank Points for the player in first place.
     * @param second_rank Points for the player in second place.
     * @param third_rank Points for the player in third place.
     * @param last_rank Points for the player in the last place.
     */
    void setPointsForPlayer(std::vector<int> rank_points);

public:
    /**
     * Constructor
     * 
     * Initializes an Obelisk object with the given site ID and obelisk number.
     * 
     * @param site_id The ID of the construction site.
     * @param obelisk_number The ID of the obelisk.
     */
    Obelisk(const int site_id, int obelisk_number);

    /**
     * Destructor
     * 
     * Cleans up the Obelisk object when it goes out of scope.
     */
    ~Obelisk();

    /**
     * Retrieves the site ID of the obelisk's construction site.
     * 
     * @return The site ID as an integer.
     */
    int getSiteId() const override;

    /**
     * Retrieves the heights of all obelisks as a vector.
     * 
     * @return A vector containing the heights of the obelisks.
     */
    std::vector<int> getObeliskHeights() const;

    /**
     * Unloads all supplies from the ship and transfers them to the obelisk's construction site.
     *
     *  
     * @param ship The Ship object containing the supplies to be unloaded.
     */
    void unloadShip(Ship ship) override;

    /**
     * Evaluate and retrieves the points for each player.
     *@return A vector containing the points of all players.
     */
    std::vector<int> evaluatePoints() override;

    /**
     * Sets the unload order for the obelisk.
     * 
     * This method overrides the base class method to set the unload order.
     * 
     * @param new_order A pair consisting of a boolean flag and a vector of integers representing the new unload order.
     */
    void setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order) override;

};

#endif
