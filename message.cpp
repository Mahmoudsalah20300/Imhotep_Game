/**
 * message.cpp
 * 
 * Defines the Message class, which manages the sending of the messages to the Server.
 * 
 * Group: 19
 * Author 12002760, 12347028
 */
#include "message.hpp"

Message::Message(int player_count, int round_count, net::Server& server)
    : player_count_(player_count), round_count_(round_count), server_(server) {}



void Message::sendStartMessage()
{
  std::string message = "StartGame " + std::to_string(player_count_) + " ";
  int number_of_stones = 2;
  for(int i = 0; i < player_count_; i++)
  {
    message += std::to_string(number_of_stones) + " ";
    number_of_stones++;
  }

  message+= std::to_string(player_count_) + " ";
  for(int i = 0; i < player_count_; i++)
  {
    message += server_.getPlayerName(i);
    if (i < player_count_ - 1)
    {
      message += " ";
    }
  }
  server_.sendToAllClients(message);
}

void Message::sendStartRoundMessage(std::vector<Ship> ships, const std::vector<std::shared_ptr<MarketCard>>& market_cards) //second parameter: const std::shared_ptr<MarketCard>& market_cards
{
  std::string message = "StartRound 4";
  for(Ship& ship : ships)
  {
    message += " " + std::to_string(ship.getShipLenght());
  }
  
  message+= " 4";
  for (const auto& card : market_cards)
  {
    message += " " + std::to_string(card->getId());
  }

  server_.sendToAllClients(message);
}

void Message::sendStartTurnMessage(int current_player)
{
  std::string message = "StartTurn " + std::to_string(current_player);
  server_.sendToAllClients(message);
}

void Message::sendRequestInputMessage(int current_player, int input_type, std::vector<int> cards_id)
{
  std::string message = "RequestInput " + std::to_string(current_player) + " " +std::to_string(input_type);
  if (input_type == 3)
  {
    message += " 4";
    for (int card : cards_id)
    {
      message += " " + std::to_string(card);
    }
  }
  server_.sendToAllClients(message);
}

void Message::sendWrongPlayerMessage(net::Server::Message received_msg)
{
  std::string message = "WrongPlayer " + std::to_string(received_msg.player_id);
  server_.sendToAllClients(message);
}

void Message::sendMalformedInputMessage(int current_player)
{
  std::string message = "MalformedInput " + std::to_string(current_player);
  server_.sendToAllClients(message);
}

void Message::sendEndTurnMessage(int current_player)
{
  std::string message = "EndTurn " + std::to_string(current_player);
  server_.sendToAllClients(message);
}

void Message::sendEndRoundMessage()
{
  std::string message = "EndRound";
  server_.sendToAllClients(message);
}

void Message::sendEndGameMessage(int player_count, std::vector<Player> player_)
{
  std::string message = "EndGame " + std::to_string(player_count);
  std::sort(player_.begin(), player_.end(), [](const Player& a, const Player& b)
  {
    if (a.getPlayerPoints() == b.getPlayerPoints())
    {
      return a.getPlayerId() < b.getPlayerId();
    }
    return a.getPlayerPoints() > b.getPlayerPoints();
  });

  for (const Player& player : player_)
  {
    message += " " + std::to_string(player.getPlayerId());
  }
  server_.sendToAllClients(message);
}

void Message::sendInexecutableInputMessage(int current_player)
{
  std::string message = "InexecutableInput " + std::to_string(current_player);
  server_.sendToAllClients(message);
}

void Message::sendSailedShipMessage(int ship_id, int site_id)
{
  std::string message = "SailedShip " + std::to_string(ship_id) + " " + std::to_string(site_id);
  server_.sendToAllClients(message);
}

void Message::sendUpdateConstructionSiteMessage(int site_id, int player_count, const std::vector<int>& site_content)
{
  std::string message = "UpdateConstructionSite " + std::to_string(site_id);
  if (site_id == 1 || site_id == 2 || site_id == 3)
  {
    message += " " + std::to_string(site_content.size());
    for (int content : site_content)
    {
        message += " " + std::to_string(content);
    }
  }
  else if (site_id == 4)
  {
    message +=  " " + std::to_string(player_count);
    for (int content : site_content)
    {
        message += " " + std::to_string(content);
    }
  }
    else if (site_id == 0)
  {
    message +=  " 4";
    for (int content : site_content)
    {
        message += " " + std::to_string(content);
    }
  }


  server_.sendToAllClients(message);
}

void Message::sendUpdateShipMessage(int ship_id, int ship_lenght, const std::vector<int>& stones_on_ship)
{
  std::string message = "UpdateShip " + std::to_string(ship_id) + " " + std::to_string(ship_lenght);
  for (int stone : stones_on_ship)
  {
      message += " " + std::to_string(stone);
  }
  server_.sendToAllClients(message);
}

void Message::sendUpdateStonesMessage(int player_id, int stone_count_difference, int new_total_amount)
{
  std::string message = "UpdateStones " + std::to_string(player_id) + " " +
                        std::to_string(stone_count_difference) + " " + std::to_string(new_total_amount);
  server_.sendToAllClients(message);
}

void Message::sendGrantPointsMessage(int player_id, int added_points, int total_points)
{
  std::string message;
  if (added_points > 0)
  {
    message = "GrantPoints " + std::to_string(player_id) + " " + std::to_string(added_points) +
    " " + std::to_string(total_points);
  }
  else
  {
    return;
  }
  server_.sendToAllClients(message);
}


void Message::GrantMarketCard(int current_player, int card_id, std::vector<int> player_cards_)
{
  std::string message = "GrantMarketCard " + std::to_string(current_player)+ " " +std::to_string(card_id);
  int cards_amount = 0;
  for (int card : player_cards_)
  {
    (void) card;
    cards_amount++;
  }
    message += " "+ std::to_string(cards_amount);
  for (int card : player_cards_)
  {
    message += " "+ std::to_string(card);
  }
  server_.sendToAllClients(message);
}

void Message::sendPlayedMarketCardsMessage(int current_player, int card_id)
{
  std::string message = "PlayedMarketCard " + std::to_string(current_player)+ " " + std::to_string(card_id);
  server_.sendToAllClients(message);
}


