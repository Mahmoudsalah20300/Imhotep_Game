/**
 * marketPlace.hpp
 * 
 * The MarketPlace class represents a marketplace in the game.
 * It handles the market cards, unloading ships, and managing the current marketplace state.
 * 
 * Group: 19
 * Author 12002760
 */
#ifndef MARKETPLACE_HPP
#define MARKETPLACE_HPP

#include <string>
#include <iostream>

#include "ConstructionSiteType.hpp"
#include "../MarketCards/marketCard.hpp"
#include "../MarketCards/RedCard.hpp"
#include "../MarketCards/GreenCard.hpp"
#include "../MarketCards/BlueCard.hpp"
#include "../MarketCards/PurpleCard.hpp"

#include <memory>
#include <algorithm>
#include <vector>

class MarketPlace : public ConstructionSite
{
  private:
  int site_id_;
  int player_count_;
  std::vector<std::shared_ptr<MarketCard>> cards; // all cards
  std::vector<std::shared_ptr<MarketCard>> market_cards; // the 4 cards
  std::shared_ptr<MarketCard> empty_card_;
  std::vector<int> input_vector; // store the stones
  bool change_unload_order;
  std::vector<int> unload_order;
  public:
    /**
     * Constructor
     * 
     * Initializes a MarketPlace object with the given site ID and number of players.
     * 
     * @param site_id The unique ID of the marketplace.
     * @param player_count The number of players participating in the game.
     */
    MarketPlace(int site_id, int player_count);

    /**
     * Copy constructor
     * 
     * Creates a copy of an existing MarketPlace object.
     * This constructor uses the default implementation to copy all members.
     */
    MarketPlace(const MarketPlace& local_arg) = default;

    /**
     * Copy assignment operator
     * 
     * Prevents the assignment of one MarketPlace object to another by deleting the operator.
     */
    MarketPlace& operator=(const MarketPlace& other) = delete;

    /**
     * Destructor
     * 
     * Cleans up any resources used by the MarketPlace object.
     */
    ~MarketPlace();

    /**
     * Sets the unload order for the marketplace.
     * 
     * This method overrides the base class method to set the unload order.
     * 
     * @param new_order A pair consisting of a boolean flag and a vector of integers representing the new unload order.
     */
    void setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order) override;

    /**
     * Evaluates the points for the marketplace.
     * 
     * This method overrides the base class method to calculate points based on the marketplace's state.
     * 
     * @return A vector of integers representing the evaluated points.
     */
    std::vector<int> evaluatePoints() override;

    /**
     * Gets the site ID of the marketplace.
     * 
     * @return The unique site ID.
     */
    int getSiteId() const override;
    /**
     * Unloads a ship at the marketplace.
     * 
     * This method overrides the base class method to handle unloading ships.
     * 
     * @param ship The ship to unload.
     */

    void unloadShip(Ship ship) override;
    /**
     * Sets up the market cards at the marketplace.
     * 
     * This method places 4 cards from the deck into the available spaces in the marketplace.
     * 
     * @param card_id The ID of the card to be used in the setup.
     */

    void setupMarketCards(int card_id); // places 4 cards from the deck into the spaces
    /**
     * Clears the marketplace and resets the market cards.
     * 
     * This method clears the 4 market spaces and puts the cards back into the deck.
     */

    void clearMarketPlace(); // clear the 4 spaces every round and puts the cards back to deck
    /**
     * Takes a card from the market.
     * 
     * Removes a card from the market at the given position.
     * 
     * @param position The position of the card to be taken from the market.
     * @return A shared pointer to the taken card.
     */

    std::shared_ptr<MarketCard> takeCardFromMarket(int position);
    /**
     * Gets the cards from the deck.
     * 
     * @return A constant reference to the vector of all cards in the deck.
     */

    const std::vector<std::shared_ptr<MarketCard>>& getCardsFromDeck() const;

    /**
     * Gets the cards currently available in the market.
     * 
     * @return A constant reference to the vector of cards in the market.
     */
    const std::vector<std::shared_ptr<MarketCard>>& getCardsFromMarket() const { return market_cards; }

    /**
     * Gets the vector of input values for the marketplace.
     * 
     * @return A constant reference to the vector of input values (stones).
     */
    const std::vector<int>& getInputVector() const { return input_vector; }

    /**
     * Gets the card IDs from the current market cards.
     * 
     * @return A constant reference to the vector of card IDs in the market.
     */
    const std::vector<int>& getCardsIDFromMarket() const;
  };

#endif
