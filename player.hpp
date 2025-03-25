/**
 * The Player class represents a player in the game.
 * It holds the player's ID, points, and provides methods to manage their points.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <memory>
#include <string>
#include <vector>
#include "MarketCards/marketCard.hpp"


class Player
{
    private:
        int player_id_;
        int points_;
        std::vector<std::shared_ptr<MarketCard>> player_cards_;

    public:
        /**
         * Constructor
         * 
         * Initializes a Player object with the given player ID and points.
         * 
         * @param player_id The ID of the player.
         * @param points The starting points of the player.
         */
        Player(const int player_id, const int points);
        
        /**
         * Destructor
         * 
         * Cleans up resources used by the Player object when it is destroyed.
         */
        ~Player();

        /**
         * Gets the player's ID.
         * 
         * @return The player ID.
         */
        int getPlayerId() const;

        /**
         * Gets the player's current points.
         * 
         * @return The player's current points.
         */
        int getPlayerPoints() const;

        /**
         * Adds points to the player's current points.
         * 
         * @param points The number of points to add to the player's current points.
         */
        void addPlayerPoints(const int points);

        void addPlayerCard(std::shared_ptr<MarketCard> card);

        std::vector<std::shared_ptr<MarketCard>> getPlayerCards() { return player_cards_; }

        const std::vector<int>& getCards() const 
        {
        static std::vector<int> cards_id;
            cards_id.clear(); // Clear the vector to avoid stale data from previous calls

            for (auto& card : player_cards_) {
                cards_id.push_back(card->getId()); // Add each card's ID to the vector
            }

            return cards_id;
        }

       std::shared_ptr<MarketCard> getBlueCard(int card_id)
       {
        for (auto it = player_cards_.begin(); it != player_cards_.end(); ++it)
        {
            // Check if the card is blue and matches the given ID
            if ((*it)->getColor() == "blue" && (*it)->getId() == card_id)
            {
                std::shared_ptr<MarketCard> card = *it; // Store the found card
                player_cards_.erase(it); // Remove the card from the vector
                return card; // Return the card
            }
        }        
        return nullptr;
        }
       
};

#endif
