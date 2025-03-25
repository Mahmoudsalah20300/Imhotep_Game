/**
 * game.cpp
 * 
 * Defines the Game class, which manages the overall game flow, 
 * including handling players, rounds, and turn-by-turn actions. The class interacts with 
 * the network server to send and receive messages and validates actions.
 * 
 * Group: 19
 * Author 12002760, 12347028
 */
#include "game.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "message.hpp"
#include "random/Random.hpp"
#include "ConstructionSites/ConstructionSiteType.hpp"
#include "ConstructionSites/marketPlace.hpp"
#include "ConstructionSites/Pyramid.hpp"
#include "ConstructionSites/temple.hpp"
#include "ConstructionSites/burial_chamber.hpp"
#include "ConstructionSites/Obelisk.hpp"

//--------------------------------------------------------------------------------------------------------------------
Game::Game(int player_count, int round_count, net::Server& server)
    : player_count_(player_count), round_count_(round_count), server_(server),
      current_round_(0), current_player_(0), action_(0), play_blue_card(false), take_market_card(false),
      must_sail_ship(false), action_count(0),
      message_(std::make_unique<Message>(player_count, round_count, server)) {}

//--------------------------------------------------------------------------------------------------------------------
Game::~Game() {}

//--------------------------------------------------------------------------------------------------------------------
void Game::startGame()
{
  //create player and supleySleds
  for(int i = 0; i < player_count_; i++)
  {
    player_.emplace_back(i, 0);
    supley_sled_.emplace_back(i, 5, (i + 2));
  }
  //create ship
  for(int i = 0; i < 4; i++)
  {
    ship_.emplace_back(i, 3, 0, false);
  }

  construction_sites_.push_back(std::make_shared<MarketPlace>(0, player_count_));
  construction_sites_.push_back(std::make_shared<Pyramid>(1, player_count_)); 
  construction_sites_.push_back(std::make_shared<temple>(2,player_count_)); 
  construction_sites_.push_back(std::make_shared<BurialChamber>(3, player_count_));
  construction_sites_.push_back(std::make_shared<Obelisk>(4, player_count_));
  market_place_ = std::dynamic_pointer_cast<MarketPlace>(construction_sites_.at(0));
  message_->sendStartMessage();
}

//--------------------------------------------------------------------------------------------------------------------
void Game::startRound()
{
  int ship_length;
  int market_card_id;
  ship_at_temple_ = false;
  
  if (current_round_ == 0)
  {
    round_start_player_ = 0;
  }
  else
  {
    round_start_player_ = (round_start_player_ + 1) % player_count_;
  }
  
  current_player_ = round_start_player_;
  for(auto& ship : ship_)
  {
    ship_length = Random::getInstance().getNextShipSize();
    ship.setShipDetails(ship_length);
  }
  
  auto marketPlace =
        std::dynamic_pointer_cast<MarketPlace>(construction_sites_.at(0));
        marketPlace->clearMarketPlace();

  for (int i = 0; i < 4; i++)
  {
    market_card_id = Random::getInstance().getNextMarketCard(); 
    marketPlace->setupMarketCards(market_card_id);
  }
  
  message_->sendStartRoundMessage(ship_, marketPlace->getCardsFromMarket());
}

//--------------------------------------------------------------------------------------------------------------------
void Game::startTurn()
{
  int command_type = INITIALIZE_NULL;
  int hold_current_player_;
  message_->sendStartTurnMessage(current_player_);
  message_->sendRequestInputMessage(current_player_, action_, market_place_->getCardsIDFromMarket());

  while (1)
  {
    net::Server::Message received_msg = server_.awaitAnyClientMessage();
    if (received_msg.player_id != current_player_)
    {
      message_->sendWrongPlayerMessage(received_msg);
      continue;
    }
    command_type = handlePlayerAction(received_msg.content);

    if (command_type == NOT_VALID_COMMAND)
    {
      message_->sendMalformedInputMessage(current_player_);
      message_->sendRequestInputMessage(current_player_, action_, market_place_->getCardsIDFromMarket());
      continue;
    }
    if (take_market_card == false)
    {
      hold_current_player_ = current_player_; // logic changes for taking cards
    }
    //compleat the player input
    if(!completePlayerAction(received_msg ,command_type))
    {
      message_->sendInexecutableInputMessage(current_player_);
      message_->sendRequestInputMessage(current_player_, action_, market_place_->getCardsIDFromMarket());
      continue;
    }
    if(take_market_card == true && action_count > 0)
    {
      current_player_ = input_vector.front();
      message_->sendRequestInputMessage(current_player_, action_, market_place_->getCardsIDFromMarket());
      input_vector.erase(input_vector.begin());
      action_count--;
      continue;
    }
    
    if(play_blue_card == true && action_count > 0) // depending on the blue card id the players have different actions
    {
      message_->sendRequestInputMessage(current_player_, action_, market_place_->getCardsIDFromMarket());
      action_count--;
      continue;
    }

    resetValues(hold_current_player_);
    
    
    //if playbluecard = true continue request input from beginning of while loop until condition is met
    message_->sendEndTurnMessage(current_player_);
    //not correct yet
    round_start_player_= current_player_;
    current_player_ = (current_player_ + 1) % player_count_;
    //checks for ent round
    if(endRound())
    {
      break;
    }

    message_->sendStartTurnMessage(current_player_);
    message_->sendRequestInputMessage(current_player_, action_, market_place_->getCardsIDFromMarket());
  }
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::completePlayerAction(net::Server::Message received_msg, int command_type)
{
  int added_removed_stones = INITIALIZE_NULL;
  std::vector<std::string> tokens;

  tokens = splitString(received_msg.content, ' ');
  int construction_position;
  if(!checkIfCorrectActionContext(command_type))
  {
    return false;
  }
  
  if(command_type == SAIL_AND_UNLOAD_SHIP) // player chooses the order of the stones
  {
    if(checkIfSailandUnloadShipInexecutable(tokens))
    {
      std::vector<int> new_unload_order;
      size_t i = 4;
      for(i = 4; i < tokens.size(); i++)
      {
        new_unload_order.push_back(ship_.at(stoi(tokens[1])).getStoneOnPosition(stoi(tokens[i])));
      }
      construction_sites_.at(stoi(tokens[2]))->setUnloadOrder({true, new_unload_order});
      command_type = SAIL_SHIP; // ships sailed directly after the chosen order of stones
    }
  }
  
  if(command_type == PLAY_BLUE_MARKET_CARD)
  {
    if(checkIfPlayBlueCardInexecutable(player_[current_player_].getPlayerCards(),
    stoi(tokens[1])))
    {
      std::shared_ptr<MarketCard> card = player_[current_player_].getBlueCard(stoi(tokens[1]));
      message_->sendPlayedMarketCardsMessage(current_player_, card->getId());
      playBlueMarketCards(card);
    }
  }
  if (command_type == GET_NEW_STONE)
  {
    if(checkGetNewStonesInexecutable())
    {
      added_removed_stones = supley_sled_.at(current_player_).placeNewStones(ADD_STONE);
      message_->sendUpdateStonesMessage(current_player_, added_removed_stones,
      supley_sled_.at(current_player_).getStorrageStatus());   
    }
    else
    {
      return false;
    }
  }

  if (command_type == PLACE_STONE_ON_SHIP)
  {
    if(checkPlaceStoneOnShipInexecutable(stoi(tokens[1]), stoi(tokens[2])))
    {
      added_removed_stones = supley_sled_.at(current_player_).placeNewStones(-1);
      ship_.at(stoi(tokens[1])).addStone(current_player_, stoi(tokens[2]));
      
      message_->sendUpdateStonesMessage(current_player_, added_removed_stones,
      supley_sled_.at(current_player_).getStorrageStatus());
      message_->sendUpdateShipMessage(ship_.at(stoi(tokens[1])).getShipId(),
      ship_.at(stoi(tokens[1])).getShipLenght(),
      ship_.at(stoi(tokens[1])).getStonesOnShip());
      if(must_sail_ship == true)
      {
        action_ = 1;
      }
    }
    else
    {
      return false;
    }
  }

  if (command_type == SAIL_SHIP)
  {
    if(checkSailShipInexecutable(stoi(tokens[1]), stoi(tokens[2])))  
    {
      ship_.at(stoi(tokens[1])).setShipStatus(true);
      message_->sendSailedShipMessage(ship_.at(stoi(tokens[1])).getShipId(),
      stoi(tokens[2]));
      //check if ID from site and set the construction site vector position
      construction_position = stoi(tokens[2]);
      construction_sites_.at(construction_position)->unloadShip(ship_.at(stoi(tokens[1])));

      sendSiteMessages(construction_position);
    }
    else
    {
      return false;
    }
  }
  if (command_type == TAKE_MARKET_CARD)
  {
    if(checkIfTakeCardInexecutable(stoi(tokens[1]),
    market_place_->getCardsIDFromMarket()))
    {
      std::shared_ptr<MarketCard> card = market_place_->takeCardFromMarket(stoi(tokens[1]));
      message_->sendUpdateConstructionSiteMessage(construction_sites_.at(0)->getSiteId(), player_count_, 
                                              market_place_->getCardsIDFromMarket());                            
      if (card->getColor() == "red")
      {
        std::shared_ptr<RedCard> redCard = std::dynamic_pointer_cast<RedCard>(card);
        message_->sendPlayedMarketCardsMessage(current_player_, card->getId());
        construction_position = redCard->playRedCardsEffect(construction_sites_, current_player_);  
        sendSiteMessages(construction_position);
      }
      else
      {
        player_[current_player_].addPlayerCard(card);
        message_->GrantMarketCard(current_player_, card->getId(),
        player_[current_player_].getCards());
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkGetNewStonesInexecutable()
{
  //check if supley sled storrage is allready full
  if(supley_sled_.at(current_player_).getStorrageStatus() < 5)
  {
    return true;
  }
  return false;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkPlaceStoneOnShipInexecutable(int ship_id, int position)
{
  std::vector<int> ship_occupied_places;
  //ship exist for 4 ships
  if(ship_id >= 0 && ship_id <= 3)
  {
    //min one stone in supleySled
    if(supley_sled_.at(current_player_).getStorrageStatus() >= 1)
    {
      //check if position exist in ship
      if(position <= ship_.at(ship_id).getShipLenght())
      {
        //check if position on ship not occupied
        ship_occupied_places = ship_.at(ship_id).getStonesOnShip();
        if(ship_occupied_places[position] == -1)
        {
          return true;
        }
      }
    }
  }
  return false;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkSailShipInexecutable(int ship_id, int construction_id)
{

  //check if ship id exist, 3 because there are 4 ship (0, 1, 2, 3)
  
  if(ship_id <= 3)
  {
    if(ship_.at(ship_id).checkSailAvailability()) 
    {
      for (const auto& site: construction_sites_) 
      {

        if (site->getSiteId() == construction_id) 
        {
          return true;
        }
      }
    }
  }
  return false;
  
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkIfTakeCardInexecutable(int chosen_card_position, std::vector<int> cards_id)
{
  if(chosen_card_position >= 0 && chosen_card_position <= 3)
  {
    if(cards_id[chosen_card_position] != -1)
    {
      return true;
    }
  }
  
  return false;
}

//--------------------------------------------------------------------------------------------------------------------
int Game::handlePlayerAction(const std::string& action)
{
  if (!checkForWrongWhitespaces(action))
  {
    return -1;
  }
  std::vector<std::string> tokens = splitString(action, ' ');
  std::string command = tokens[0];
  std::transform(command.begin(), command.end(), command.begin(), ::tolower);
  if (command == "getnewstones")
  {
    if (tokens.size() != 1)
    {
      return -1;
    }
    return 1;
  }
  else if (command == "placestoneonship")
  {
    if (tokens.size() != 3)
    {
      return -1;
    }
    if (!isValidInteger(tokens[1]) || !isValidInteger(tokens[2]))
    {
      return -1;
    }
    int ship_id = stoi(tokens[1]);
    int position_on_ship = stoi(tokens[2]);
    (void)ship_id;
    (void)position_on_ship;
    return 2;
  }
  else if (command == "sailship")
  {
    if (tokens.size() != 3)
    {
      return -1;
    }
    if (!isValidInteger(tokens[1]) || !isValidInteger(tokens[2]))
    {
      return -1;
    }
    int ship_id = stoi(tokens[1]);
    int site_id = stoi(tokens[2]);
    (void)ship_id;
    (void)site_id;
    return 3;
  }
  else if (command == "takemarketcard")
  {
    if (tokens.size() != 2)
    {
      return -1;
    }
    if (!isValidInteger(tokens[1]))
    {
      return -1;
    }
    return 4;
  }
  else if (command == "playbluemarketcard")
  {
    if (tokens.size() != 2)
    {
      return -1;
    }
    if (!isValidInteger(tokens[1]))
    {
      return -1;
    }
    return 5;
  }
  else if (command == "sailandunloadship")
  {
    if (!isValidInteger(tokens[1]))
    {
      return -1;
    }
    size_t length = 4 + ship_.at(stoi(tokens[1])).getStonesOnShipAmount();
    std::cout << "STONEONSHIPLENGHT"<< ship_.at(stoi(tokens[1])).getStonesOnShipAmount() << std::endl;
    std::cout << "  TOKENSIZE"<< tokens.size() << std::endl;
    if(tokens.size() != length)
    {
      return -1;
    }
    for (size_t i = 1; i < tokens.size(); ++i)
    {
      if (!isValidInteger(tokens[i]))
      {
        return -1;
      }
    }
    return 6;
  }
  return -1;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::endRound()
{
  for (auto& ship: ship_)
  {
    if(!ship.getShipStatus()) 
    {
      return false;
    }
  }
  if(ship_at_temple_ == true)
  {
    temple_points_  = construction_sites_.at(2)->evaluatePoints();
  }
  else
  {
    temple_points_.resize(player_count_, 0);
  }

  for(int i = 0; i < player_count_; i++)
  {
    player_[i].addPlayerPoints(temple_points_[i]);

    message_->sendGrantPointsMessage(player_[i].getPlayerId(), temple_points_[i],
                                  player_[i].getPlayerPoints());
  }
  
  current_round_++;
  message_->sendEndRoundMessage();
  return true;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkGameOver()
{
  if (current_round_ == round_count_)
  {
    burial_points_ = construction_sites_.at(3)->evaluatePoints();
    obelisk_points_ = construction_sites_.at(4)->evaluatePoints();
    green_card_points_.resize(player_count_, 0);
    purple_card_points_.resize(player_count_, 0);
    blue_card_points_.resize(player_count_, 0);

    int added_points = 0;

    addGreenCardsPoints();
    addPurpleCardsPoints();
    addBlueCardsPoints();

    for(int i = 0; i < player_count_; i++)
    {
      added_points = burial_points_[i] + obelisk_points_[i] + green_card_points_[i] + purple_card_points_[i]
      + blue_card_points_[i];
      player_.at(i).addPlayerPoints(added_points);
      message_->sendGrantPointsMessage(i, added_points, player_.at(i).getPlayerPoints());
      added_points = 0;
    }
    message_->sendEndGameMessage(player_count_, player_);
    return true;
  }
  return false;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkForWrongWhitespaces(const std::string& action)
{
  if (action.empty() || std::isspace(action.front()) || std::isspace(action.back()))
  {
    return false;
  }
  if (action.find("  ") != std::string::npos)
  {
    return false;
  }
  return true;
}

//--------------------------------------------------------------------------------------------------------------------
std::vector<std::string> Game::splitString(const std::string& input, char delimiter)
{
  std::vector<std::string> result;
  std::string current_token;
  for (char current_char : input)
  {
    if (current_char == delimiter)
    {
      if (!current_token.empty())
      {
        result.push_back(current_token);
        current_token.clear();
      }
    }
    else
    {
      current_token += current_char;
    }
  }
  if (!current_token.empty())
  {
    result.push_back(current_token);
  }
  return result;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::isValidInteger(const std::string& input)
{
  size_t start_index = (input[0] == '-') ? 1 : 0;
  if (!std::all_of(input.begin() + start_index, input.end(), ::isdigit))
  {
    return false;
  }
  try
  {
    int integer = std::stoi(input);
    (void)integer;
    return true;
  }
  catch (const std::invalid_argument& e)
  {
    return false;
  }
  catch (const std::out_of_range&)
  {
    return false;
  }
}

//--------------------------------------------------------------------------------------------------------------------
void Game::resetValues(int hold_current_player_)
{
  current_player_ = hold_current_player_;
  input_vector.clear();
  action_ = 0;
  play_blue_card = false;
  action_count = 0;
  take_market_card = false;
  must_sail_ship = false;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkIfCorrectActionContext(int command_type)
{
  if(action_ == 3)
  {
    if (command_type != TAKE_MARKET_CARD)
    {
      return false;
    }
  }
  else if(action_ == 2)
  {
    if (command_type != PLACE_STONE_ON_SHIP)
    {
      return false;
    }
  }
  else if(action_ == 4)
  {
    if (command_type != SAIL_AND_UNLOAD_SHIP)
    {
      return false;
    }
  }
  else if (action_ == 1)
  {
    if (command_type != SAIL_SHIP)
    {
      return false;
    }
  }
  return true;
}

//--------------------------------------------------------------------------------------------------------------------
void Game::sendSiteMessages(int construction_position)
{
  if(construction_position == 0) //go to market place
  {
  auto marketplace = 
        std::dynamic_pointer_cast<MarketPlace>(construction_sites_.at(construction_position));
  input_vector = market_place_->getInputVector();
  action_count = static_cast<int>(input_vector.size());
  take_market_card = true;
  action_ = 3;
  }

  else if(construction_position == 1) // construction is pyramide
  {
    auto pyramid = 
        std::dynamic_pointer_cast<Pyramid>(construction_sites_.at(construction_position));
    pyramid_points_ = construction_sites_.at(construction_position)->evaluatePoints();
    message_->sendUpdateConstructionSiteMessage
                  (construction_sites_.at(construction_position)->getSiteId(), player_count_, 
                  pyramid->getallelements());
    for(int i = 0; i < player_count_; i++)
    {
      player_[i].addPlayerPoints(pyramid_points_[i]);
      message_->sendGrantPointsMessage(player_[i].getPlayerId(), pyramid_points_[i],
                                player_[i].getPlayerPoints());
    }
  }

  else if (construction_position == 2) // temple
  {

    auto temple_t = 
        std::dynamic_pointer_cast<temple>(construction_sites_.at(construction_position));
    message_->sendUpdateConstructionSiteMessage
                  (construction_sites_.at(construction_position)->getSiteId(), player_count_, 
                  temple_t->getallelements());
    ship_at_temple_ = true;
  }

  else if (construction_position == 3) // burial
  {
    auto burial = 
        std::dynamic_pointer_cast<BurialChamber>(construction_sites_.at(construction_position));
    message_->sendUpdateConstructionSiteMessage(construction_position, player_count_,
    burial->getAllElements());
  }

  else if (construction_position == 4) // construction is obelisk
  {
    auto obelisk =
    std::dynamic_pointer_cast<Obelisk>(construction_sites_.at(construction_position));
    message_->sendUpdateConstructionSiteMessage(construction_position, player_count_,
    obelisk->getObeliskHeights());
  }
}

//--------------------------------------------------------------------------------------------------------------------
void Game::addGreenCardsPoints()
{
  for(int i = 0; i < player_count_; i++)
  {
    std::vector<std::shared_ptr<MarketCard>> cards = player_[i].getPlayerCards();
    std::shared_ptr<GreenCard> green_card = nullptr;

    for(auto &card : cards)
    {
      if(card->getColor() == "green")
      {
        green_card = std::dynamic_pointer_cast<GreenCard>(card);
        green_card_points_[i] += green_card->playGreenCardEffect(construction_sites_);
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------------------------
void Game::addPurpleCardsPoints()
{
  for(int i = 0; i < player_count_; i++)
  {
    int purple_cards_count = 0;
    std::shared_ptr<PurpleCard> purple_card = nullptr;
    std::vector<std::shared_ptr<MarketCard>> cards = player_[i].getPlayerCards();
    for(auto &card : cards)
    {
      if(card->getColor() == "purple")
      {
        purple_cards_count++;
        purple_card = std::dynamic_pointer_cast<PurpleCard>(card);
      }
    }
    if(purple_card)
    {
      purple_card_points_[i] += purple_card->playPurpleCardEffect(purple_cards_count);
    }
  }
}

//--------------------------------------------------------------------------------------------------------------------
void Game::addBlueCardsPoints()
{
  for(int i = 0; i < player_count_; i++)
  {
    int blue_cards_count = 0;
    std::shared_ptr<BlueCard> blue_card = nullptr;
    std::vector<std::shared_ptr<MarketCard>> cards = player_[i].getPlayerCards();
    for(auto &card : cards)
    {
      if(card->getColor() == "blue")
      {
        blue_cards_count++;
        blue_card = std::dynamic_pointer_cast<BlueCard>(card);
      }
    }
    if(blue_card)
    {
      blue_card_points_[i] += blue_cards_count;
    }
  }
}

//--------------------------------------------------------------------------------------------------------------------
void Game::playBlueMarketCards(std::shared_ptr<MarketCard> card)
{
  play_blue_card = true;
  if(card->getId() == 8)
  {
    action_ = 4;
    action_count = 1;
  }
  if(card->getId() == 9)
  {
    int added_removed_stones = supley_sled_.at(current_player_).placeNewStones(ADD_STONE);
    message_->sendUpdateStonesMessage(current_player_, added_removed_stones,
    supley_sled_.at(current_player_).getStorrageStatus());
    action_ = 2;
    action_count = 1;
  }
  if(card->getId() == 10)
  {
    action_ = 2;
    action_count = 2;
    must_sail_ship = true;
  }
  if(card->getId() == 11)
  {
    action_ = 2;
    action_count = 2;
  }
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkIfSailandUnloadShipInexecutable(std::vector<std::string> tokens)
{
  size_t i = 4;
  int highest_value = 0;
  for(i = 4; i < tokens.size(); i++)
  {
    int current_value = stoi(tokens[i]);
    if (current_value > highest_value)
    {
      highest_value = current_value;
    }
  }
  if(highest_value >= ship_.at(stoi(tokens[1])).getShipLenght())
  {
    return false;
  }
  for(i = 4; i < tokens.size(); i++)
  {
    if (stoi(tokens[i]) < 0)
    {
      return false;
    }
    if(ship_.at(stoi(tokens[1])).getStoneOnPosition(stoi(tokens[i])) == -1)
    {
      return false;
    }
  }
  return true;
}

//--------------------------------------------------------------------------------------------------------------------
bool Game::checkIfPlayBlueCardInexecutable(std::vector<std::shared_ptr<MarketCard>> players_cards, int card_id)
{
  for(auto &card : players_cards)
    {
      if(card->getColor() == "blue")
      {
        if(card->getId() == card_id)
        {
          return true;
        }
      }
    }
  return false;
}
