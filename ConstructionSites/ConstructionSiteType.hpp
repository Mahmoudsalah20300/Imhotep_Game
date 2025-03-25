/**
 * ConstructionSiteType class contains all the prototypes for the Construction sites.
 * ConstructionSiteType serves all other  ConstructionSite classes.
 * 
 * Group : 19
 * Author : 12002760, 12347028, 12241141 
 */



#ifndef CONSTRUCTION_SITE_TYPE_HPP
#define CONSTRUCTION_SITE_TYPE_HPP
#include "../game.hpp"
#include <map>
#include <vector>
        

/**************************************************************************
  The Construction site contains all the common prototypes that can be used
  by other classes defined as Construction sites.
 **************************************************************************/
class ConstructionSite
{

  public:
    /**
     * Constructor
     * 
     * Initializes a ConstructionSite object.
     */
    ConstructionSite();

    /**
     * Destructor
     * 
     * Cleans up the ConstructionSite object when it goes out of scope.
     */
    ~ConstructionSite();

    /**
     * Retrieves the site ID of the construction site.
     * 
     * @return The site ID as an integer.
     */
    virtual int getSiteId() const = 0;

    /**
     * Unloads the supplies from the ship and transfers them to the construction site.
     * 
     * @param ship The Ship object containing the supplies to be unloaded.
     */
    virtual void unloadShip(Ship ship) = 0;

    /**
     * Evaluates and retrieves the points for each player at the construction site.
     * 
     * @return A vector containing the points of all players.
     */
    virtual std::vector<int> evaluatePoints() = 0;

    /**
     * Sets the unload order.
     * 
     * @param new_order A pair consisting of a boolean flag and a vector of integers representing the new unload order.
     */
    virtual void setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order) = 0;

};

#endif
