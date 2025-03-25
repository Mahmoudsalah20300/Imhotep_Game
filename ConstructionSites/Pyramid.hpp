/**
 * Pyramid class contains all the prototypes for the Pyramid.
 * Pyramid inherits the ConstructionSite class.
 * 
 * Group : 19
 * Author : 12347028
 */

#ifndef PYRAMID_HEADER
#define PYRAMID_HEADER

#include "ConstructionSiteType.hpp"

class Pyramid : public ConstructionSite
{
    private:
    int site_id_;
    bool change_unload_order;
    std::vector<int> unload_order;

    public:
    /**
     * Constructor
     * 
     * Initializes a Pyramid object with the given site ID and number of players.
     * 
     * @param site_id The ID of the pyramid's site.
     * @param playernumbers The number of players associated with the pyramid.
     */
    Pyramid(int site_id, int playernumbers);

    /**
     * Copy Constructor
     * 
     * Performs a default copy of the Pyramid object.
     * 
     * @param local_arg The Pyramid object to copy from.
     */
    Pyramid(const Pyramid& local_arg) = default;

    /**
     * Destructor
     * 
     * Cleans up the Pyramid object when it goes out of scope.
     */
    ~Pyramid() = default;

    /**
     * Evaluates and retrieves the points for each player.
     * 
     * @return A vector containing the points of all players.
     */
    std::vector<int> evaluatePoints() override;

    /**
     * Retrieves all elements stored in the pyramid.
     * 
     * @return A vector containing all the elements inside the pyramid.
     */
    std::vector<int> getallelements();

    /**
     * Gets the site ID of the pyramid.
     * 
     * @return The site ID as an integer.
     */
    int getSiteId() const override;

    /**
     * Unloads all supplies from the ship and transfers them to the pyramid.
     * 
     * @param ship The Ship object containing the supplies to be unloaded.
     */
    void unloadShip(Ship ship) override;

    /**
     * Sets the Input Vector.
     * 
     * @param new_vector The Ship object containing the supplies to be unloaded.
     */
    void setInputVector(const std::vector<int>& new_vector) { input_vector = new_vector; }

    /**
     * adds elements to the allements vector.
     * 
     * @param allelemnts The Ship object containing the supplies to be unloaded.
     */
    void setAllElements(int value) { allelements.push_back(value); }

    /**
     * Sets the unload order.
     * 
     * @param new_order A pair consisting of a boolean flag and a vector of integers representing the new unload order.
     */
    void setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order) override;

    /**
     * Function to add all stones from the input vector to the pyramid.
     */
    void addStoneOnthePyramid();

    // The Pyramid class with three different level each level is a layer of the Pyramid 
    std::vector<std::vector<std::vector<int>>> pyramid = {
                                                            {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}},
                                                            {{-1,-1},{-1,-1}},
                                                            {{-1}}
                                                            };

    // The Pyramid Points the same layers as pyramid put for the points  
    std::vector<std::vector<std::vector<int>>> pyramidpoints = {
                                                            {{2, 2, 2},{1, 4, 1},{3, 3, 3}},
                                                            {{2, 1},{3, 3}},
                                                            {{4}}
                                                            };
    
    private:
    std::vector<int> otherStones;
    int otherpoint = 1;
    std::vector<int> playerspoints;
    std::vector<int> allelements;
    std::pair<int, int> current_position = {0, 0};
    int pyramidlevel = 0;
    std::vector<int> input_vector;

    /**
     * Private function to grant points to each player based on the game rules.
     */
    void grantedpoints();

    /**
     * Checks whether the current level of the pyramid is fully complete.
     *
     * @param level A 2D vector representing the current pyramid level.
     * @return True if the level is complete, false otherwise.
     */
    bool is_full_level(std::vector<std::vector<int>>& level);    
};

#endif
