
/**
 * temple class contains all the prototypes for the temple.
 * temple inherits the ConstructionSite class.
 * 
 * Group : 19
 * Author : 12347028
 */


#ifndef TEMPLE_HPP
#define TEMPLE_HPP

#include "ConstructionSiteType.hpp"


class temple: public ConstructionSite{
  private:
    int temple_length_;
    std::vector<std::vector<int>> templeLevel_ = {};
    int siteid_;
    int player_count_;
    int level_ = 0;
    std::vector<int> shipLoad;
    int position_ = 0;
    std::vector<int> points_;
    std::vector<int> AllElmenets_;
    bool change_unload_order;
    std::vector<int> unload_order;
    /**
     * Checks if a temple level is empty.
     * 
     * Determines whether the provided level contains any elements.
     * 
     * @param level A reference to the level to check.
     * @return True if the level is empty, otherwise false.
     */
    bool isempty_(std::vector<int>& level);

    /**
     * Creates a new level for the temple.
     * 
     * Adds a new level to the temple structure, initializing it as needed.
     */
    void creatnewLevel_();

    /**
     * Adds stones to the temple.
     * 
     * Places stones onto the current structure of the temple.
     */
    void addStonesOntemple_();

  public:
    /**
     * Constructor
     * 
     * Initializes a temple object with the given site ID and number of players.
     * 
     * @param site_id The unique ID of the temple.
     * @param player_count The number of players interacting with the temple.
     */
    temple(int site_id, int player_count);

    /**
     * Destructor
     * 
     * Cleans up any resources used by the temple object.
     */
    ~temple() = default;

    /**
     * Copy constructor
     * 
     * Creates a copy of an existing temple object.
     * This constructor uses the default implementation to copy all members.
     * 
     * @param c The temple object to copy.
     */
    temple(const temple & c) = default;

    /**
     * Gets the site ID of the temple.
     * 
     * @return The unique site ID.
     */
    int getSiteId() const override;

    /**
     * Unloads a ship at the temple.
     * 
     * This method overrides the base class method to handle unloading ships.
     * 
     * @param ship The ship to unload.
     */
    void unloadShip(Ship ship) override;

    /**
     * Evaluates the points for the temple.
     * 
     * This method overrides the base class method to calculate points based on the temple's state.
     * 
     * @return A vector of integers representing the evaluated points.
     */
    std::vector<int> evaluatePoints() override;

    /**
     * Gets the length of the temple.
     * 
     * @return The length of the temple.
     */
    int getLength();

    /**
     * Gets all elements in the temple.
     * 
     * @return A vector of integers representing all elements in the temple.
     */
    std::vector<int> getallelements();

    /**
     * Sets the unload order for the temple.
     * 
     * This method overrides the base class method to set the unload order.
     * 
     * @param new_order A pair consisting of a boolean flag and a vector of integers representing the new unload order.
     */
    void setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order) override;
};

#endif
