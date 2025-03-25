/**
 * markeCard.hpp
 * 
 * The MarketCard class represents a card in the marketplace.
 * It holds the card's ID, color, and name, and provides methods to retrieve and modify these properties.
 * 
 * Group: 19
 * Author 12002760
 */
#ifndef MARKETCARD_HPP
#define MARKETCARD_HPP

#include <string>
#include <iostream>

class MarketCard
{
  protected:
  int card_id_;
  std::string color_;
  std::string name_;

  public:
   /**
     * Constructor
     * 
     * Initializes a MarketCard object with the given ID, color, and name.
     * 
     * @param id The unique ID of the card.
     * @param color The color of the card.
     * @param name The name of the card.
     */
    MarketCard(int id, const std::string& color, const std::string& name);
    
    /**
     * Destructor
     * 
     * The destructor cleans up any resources used by the MarketCard object.
     */
    virtual ~MarketCard() {};

    /**
     * Gets the card's ID.
     * 
     * @return The unique ID of the card.
     */
    virtual int getId() const = 0;
    
    /**
     * Gets the card's color.
     * 
     * @return The color of the card.
     */
    virtual std::string getColor() const = 0;
    
    /**
     * Gets the card's name.
     * 
     * @return The name of the card.
     */
    virtual std::string getName() const = 0;

    /**
     * Sets the card's ID.
     * 
     * @param id The new ID for the card.
     */
    virtual void setId(int id) = 0;

    /**
     * Sets the card's color.
     * 
     * @param color The new color for the card.
     */
    virtual void setColor(std::string& color) = 0;
    
    /**
     * Sets the card's name.
     * 
     * @param name The new name for the card.
     */
    virtual void setName(std::string& name ) = 0;  

};

#endif
