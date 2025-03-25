/**
 * message.hpp
 * 
 * Defines the Message class, which manages the sending of the messages to the Server.
 * 
 * Group: 19
 * Author 12002760, 12347028
 */
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "network/Server.hpp"
#include "ship.hpp"
#include "player.hpp"
#include "MarketCards/marketCard.hpp"
#include <string>
#include <iostream>
#include <algorithm>


class Message
{
  private:
    std::string message_content;
    int player_count_;
    int round_count_;
    net::Server& server_;

  public:
  /**
   * Constructs a Message object with specified player and round counts, and a reference to the server.
   * 
   * @param player_count The number of players in the game
   * @param round_count The total number of rounds to be played
   * @param server Reference to the network server handling communication
   */
  Message(int player_count, int round_count, net::Server& server);

  /**
   * Default copy constructor.
   */
  Message(const Message&) = default;

  /**
   * Default destructor.
   */
  ~Message() = default;

  /**
   * Deleted copy assignment operator to ensure unique server reference ownership.
   */
  Message& operator=(const Message&) = delete;

  /**
   * Sends a message indicating the start of the game.
   */
  void sendStartMessage();

  /**
   * Sends a message indicating the start of a new round.
   */
  void sendStartRoundMessage(std::vector<Ship> ships, const std::vector<std::shared_ptr<MarketCard>>& market_cards);

  /**
   * Sends a message to indicate the start of a player's turn.
   */
  void sendStartTurnMessage(int current_player);

  /**
   * Requests input from the current player.
   */
  void sendRequestInputMessage(int current_player, int input_type, std::vector<int> cards_id);

  /**
   * Sends a message if an action is received from the wrong player.
   * 
   * @param received_msg The message sent by the incorrect player.
   */
  void sendWrongPlayerMessage(net::Server::Message received_msg);

  /**
   * Sends a message for malformed input received from a player.
   */
  void sendMalformedInputMessage(int current_player);

  /**
   * Sends a message indicating the end of the current turn.
   */
  void sendEndTurnMessage(int current_player);

  /**
   * Sends a message indicating the end of the round..
   */
  void sendEndRoundMessage();

  /**
   * Sends a message indicating the end of the game.
   */
  void sendEndGameMessage(int player_count, std::vector<Player> player_);

  /**
   * Sends a message indicating a non-executable action.
   */
  void sendInexecutableInputMessage(int current_player);

  /**
   * Sends a message indicating that a ship successfully sailed to a construction site.
   */
  void sendSailedShipMessage(int ship_id, int site_id);

  /**
   * Sends a message indicating that a specific construction site was updated and what it's updated content is.
   */
  void sendUpdateConstructionSiteMessage(int site_id, int player_count, const std::vector<int>& site_content);

  /**
   * Sends a message indicating that a ship's load was successfully changed.
   */
  void sendUpdateShipMessage(int ship_id, int ship_lenght, const std::vector<int>& stones_on_ship);

  /**
   * Sends a message indicating that the stone count of a player was changed.
   */
  void sendUpdateStonesMessage(int player_id, int stone_count_difference, int new_total_amount);

  /**
   * Sends a message indicating that a player's score was updated.
   */
  void sendGrantPointsMessage(int player_id, int added_points, int total_points);

  void GrantMarketCard(int current_player, int card_id, std::vector<int> player_cards_);

  void sendPlayedMarketCardsMessage(int current_player, int card_id);
};

#endif
