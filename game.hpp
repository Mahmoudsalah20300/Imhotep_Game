#ifndef GAME_HPP
#define GAME_HPP
/**
 * game.hpp
 * 
 * Defines the Game class, which manages the overall game flow, 
 * including handling players, rounds, and turn-by-turn actions. The class interacts with 
 * the network server to send and receive messages and validates actions.
 * 
 * Group: 19
 * Author 12002760, 12347028, 12241141
 */

#include "network/Server.hpp"
#include "random/Random.hpp"
#include "message.hpp"
#include <format>
#include <string>
#include <vector>

#include "player.hpp"
#include "suplySled.hpp"
#include "ship.hpp"
#include "MarketCards/marketCard.hpp"



class ConstructionSite;
class MarketPlace;

constexpr int INITIALIZE_NULL = 0;
constexpr int NOT_VALID_COMMAND = -1;
constexpr int GET_NEW_STONE = 1;
constexpr int PLACE_STONE_ON_SHIP = 2;
constexpr int SAIL_SHIP = 3;
constexpr int TAKE_MARKET_CARD = 4;
constexpr int PLAY_BLUE_MARKET_CARD = 5;
constexpr int SAIL_AND_UNLOAD_SHIP = 6;
constexpr int ADD_STONE = 3;

class Game
{
  private:
    int player_count_;
    int round_count_;
    net::Server& server_;
    int current_round_;
    int current_player_;
    int round_start_player_;
    int action_;
    bool play_blue_card;
    bool take_market_card;
    bool must_sail_ship;
    int action_count;
    std::vector<int> input_vector;
    std::shared_ptr<MarketPlace> market_place_;
    std::unique_ptr<Message> message_;
    std::vector<Player> player_;
    std::vector<SupleySled> supley_sled_;
    std::vector<Ship> ship_;
    std::vector<std::shared_ptr<ConstructionSite>> construction_sites_;

    //addingg points
    std::vector<int> pyramid_points_;
    std::vector<int> temple_points_;
    std::vector<int> burial_points_;
    std::vector<int> obelisk_points_;
    std::vector<int> green_card_points_;
    std::vector<int> purple_card_points_;
    std::vector<int> blue_card_points_;

    //check if it was sailed on Site
    bool ship_at_temple_;


    bool checkForWrongWhitespaces(const std::string& action);

    /**
     * Splits a string by a specified delimiter.
     * 
     * @param input The string to split
     * @param delimiter The character to split by
     * @return A vector of split substrings
     */
    std::vector<std::string> splitString(const std::string& input, char delimiter);

    /**
     * Checks if a string represents a valid integer.
     * 
     * @param input The string to validate
     * @return true if the string is a valid integer, false otherwise
     */
    bool isValidInteger(const std::string& input);

    /**
     * Processes the action provided by the player.
     *
     * @param received_msg the action from the player
     * @param command_type the command type
     * @return true if the message is valid, false otherwise
     */
    bool completePlayerAction(net::Server::Message received_msg, int command_type);
    
    /**
     * Checks if GetNewStones action has Inexecutable errors.
     * 
     * @return true if no errors, false if error
     */
    bool checkGetNewStonesInexecutable();

    /**
     * Checks if PlaceStoneOnShip action has Inexecutable errors.
     * 
     * @param ship_id the id from the ship
     * @param position the position where the ship sails to
     * @return true if no errors, false if error
     */
    bool checkPlaceStoneOnShipInexecutable(int ship_id, int position);


    /**
     * Checks if SailShip action has Inexecutable errors.
     * 
     * @param ship_id the id from the ship
     * @param construction_id the id from the construction site
     * @return true if no errors, false if error
     */
    bool checkSailShipInexecutable(int ship_id, int construction_id);

    /**
     * Processes the action provided by the player.
     * 
     * @param action The action string received from the player
     * @return true if the action is valid, false otherwise
     */
    int handlePlayerAction(const std::string& action);

    /**
     * Checks if the round has reached its end condition.
     * 
     * @return true if the game is over, false otherwise.
     */
    bool endRound();

  public:
    /**
     * Constructs a Game object with specified player and round counts, and a reference to the server.
     * 
     * @param player_count The number of players in the game
     * @param round_count The total number of rounds to be played
     * @param server Reference to the network server handling communication
     */
    Game(int player_count, int round_count, net::Server& server);

    /**
     * Destroys the Game object and cleans up resources.
     */
    ~Game();

    /**
     * Starts the game.
     */
    void startGame();

    /**
     * Starts a new round of the game.
     */
    void startRound();

    /**
     * Manages the turn of the players.
     */
    void startTurn();

    /**
     * Checks if the game has reached its end condition.
     * 
     * @return true if the game is over, false otherwise.
     */
    bool checkGameOver();

    void resetValues(int hold_current_player_);

    bool checkIfTakeCardInexecutable(int chosen_card_position, std::vector<int> cards_id);

    bool checkIfCorrectActionContext(int command_type);

    bool checkIfSailandUnloadShipInexecutable(std::vector<std::string> tokens);

    bool checkIfPlayBlueCardInexecutable(std::vector<std::shared_ptr<MarketCard>> players_cards, int card_id);

    void sendSiteMessages(int construction_position);

    void addGreenCardsPoints();

    void addPurpleCardsPoints();

    void addBlueCardsPoints();

    void playBlueMarketCards(std::shared_ptr<MarketCard> card);

};

// This is a simple line 

#endif
