/**
 * GreenCard.hpp
 * 
 * The PurpleCard class represents a specific type of MarketCard with green color.
 * It provides methods to retrieve and modify its properties, as well as apply the card's effect.
 * 
 * Group: 19
 * Author 12002760
 */

#ifndef GREEN_CARD_HPP
#define GREEN_CARD_HPP

#include "marketCard.hpp"
#include "../ConstructionSites/ConstructionSiteType.hpp"
#include <vector>

class GreenCard : public MarketCard
{
  private:
  int points_;
  std::vector<int> elements;


  public:
  /**
   * Constructor
   * 
   * Initializes a GreenCard object with the given ID, color, and name.
   * 
   * @param card_id The unique ID of the card.
   * @param color The color of the card.
   * @param name The name of the card.
   */
  GreenCard(int card_id, const std::string& color, const std::string& name);

  /**
   * Destructor
   * 
   * Cleans up resources used by the GreenCard object when it is destroyed.
   */
  ~GreenCard() = default;

  /**
   * Copy Constructor (Deleted)
   * 
   */

  GreenCard(const GreenCard& other) = delete;

  /**
   * Gets the card's ID.
   * 
   * @return The unique ID of the card.
   */
  int getId() const override;

  /**
   * Gets the card's color.
   * 
   * @return The color of the card.
   */
  std::string getColor() const override;

  /**
   * Gets the card's name.
   * 
   * @return The name of the card.
   */
  std::string getName() const override;

  /**
   * Sets the card's ID.
   * 
   * @param id The new ID for the card.
   */
  void setId(int id) override;

  /**
   * Sets the card's color.
   * 
   * @param color The new color for the card.
   */
  void setColor(std::string& color) override;

  /**
   * Sets the card's name.
   * 
   * @param name The new name for the card.
   */
  void setName(std::string& name) override;

  /**
   * Applies the effect of the green card.
   *
   * 
   * @param construction_sites A vector of construction sites to apply the effect on.
   * @param current_player The ID of the current player applying the card.
   * 
   * @return An integer representing the result.
   */
  int playGreenCardEffect(std::vector<std::shared_ptr<ConstructionSite>>& construction_sites);
};

#endif
