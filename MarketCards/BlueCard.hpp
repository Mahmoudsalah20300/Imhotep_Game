/**
 * BlueCard.hpp
 * 
 * The BlueCard class represents a specific type of MarketCard with blue color.
 * It provides methods to retrieve and modify its properties.
 * 
 * Group: 19
 * Author 12002760
 */

#ifndef BLUE_CARD_HPP
#define BLUE_CARD_HPP

#include "marketCard.hpp"

class BlueCard : public MarketCard
{
  public:
  /**
   * Constructor
   * 
   * Initializes a BlueCard object with the given ID, color, and name.
   * 
   * @param card_id The unique ID of the card.
   * @param color The color of the card.
   * @param name The name of the card.
   */
  BlueCard(int card_id, const std::string& color, const std::string& name);

  /**
   * Destructor
   * 
   * Cleans up resources used by the BlueCard object when it is destroyed.
   */
  ~BlueCard() = default;

  /**
   * Copy Constructor (Deleted)
   * 
   */
  BlueCard(const BlueCard& other) = delete;

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
};

#endif
