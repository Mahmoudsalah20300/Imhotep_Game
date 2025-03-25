#include "marketPlace.hpp"

#include <vector>

MarketPlace::MarketPlace(int site_id, int player_count) : site_id_(site_id), player_count_(player_count),
empty_card_(std::make_shared<RedCard>(-1, "", "empty")), change_unload_order(false)
{
  cards.emplace_back(std::make_shared<RedCard>(0, std::string("red"), std::string("Entrance")));
  cards.emplace_back(std::make_shared<RedCard>(1, std::string("red"),
  std::string("Sarcophagus")));
  cards.emplace_back(std::make_shared<RedCard>(2, std::string("red"),
  std::string("Paved path")));
  cards.emplace_back(std::make_shared<GreenCard>(3, std::string("green"),
  std::string("Pyramid decoration")));
  cards.emplace_back(std::make_shared<GreenCard>(4, std::string("green"),
  std::string("Temple decoration")));
  cards.emplace_back(std::make_shared<GreenCard>(5, std::string("green"),
  std::string("Burial chamber decoration")));
  cards.emplace_back(std::make_shared<GreenCard>(6, std::string("green"),
  std::string("Obelisk decoration")));
  cards.emplace_back(std::make_shared<PurpleCard>(7, std::string("purple"),
  std::string("Statue")));
  cards.emplace_back(std::make_shared<BlueCard>(8, std::string("blue"), std::string("Lever")));
  cards.emplace_back(std::make_shared<BlueCard>(9, std::string("blue"), std::string("Hammer")));
  cards.emplace_back(std::make_shared<BlueCard>(10, std::string("blue"), std::string("Sail")));
  cards.emplace_back(std::make_shared<BlueCard>(11, std::string("blue"), std::string("Chisel")));
}

MarketPlace::~MarketPlace() {}

std::vector<int> MarketPlace::evaluatePoints()
{
  return {};
}

int MarketPlace::getSiteId() const
{
  return site_id_;
}

void MarketPlace::setUnloadOrder(const std::pair<bool, std::vector<int>>& new_order)
{
  auto [new_change_unload_order, new_unload_order] = new_order;
  change_unload_order = new_change_unload_order;
  unload_order = new_unload_order;
}

void MarketPlace::unloadShip(Ship ship)
{
  input_vector.clear();
  if(change_unload_order == true)
  {
      for(int stone : unload_order)
      {
        input_vector.push_back(stone); 
      }
      change_unload_order = false;
      unload_order.clear();
      return;
  }
  for(auto it = ship.getStonesOnShip().begin() ;
  it != ship.getStonesOnShip().end() ; ++it)
  {
      if(*it != -1)
      {
          input_vector.push_back(*it); 
      }
  }
}

const std::vector<std::shared_ptr<MarketCard>>& MarketPlace::getCardsFromDeck() const
{
  return cards;
}

void MarketPlace::clearMarketPlace()
{
  market_cards.clear();
}

void MarketPlace::setupMarketCards(int card_id)
{
  
  for (auto it = cards.begin(); it != cards.end(); ++it)
  {
    if ((*it)->getId() == card_id)
    {
      std::shared_ptr<MarketCard> card = *it;
      market_cards.push_back(card);
      return;
    }
  }
}

std::shared_ptr<MarketCard> MarketPlace::takeCardFromMarket(int position)
{
  std::shared_ptr<MarketCard> card = market_cards[position];
  market_cards[position] = empty_card_;
  return card;
}

const std::vector<int>& MarketPlace::getCardsIDFromMarket() const
{
  static std::vector<int> cards_id;
  cards_id.clear(); // Clear the vector to avoid stale data from previous calls
  for (auto& card : market_cards)
  {
    cards_id.push_back(card->getId()); // Add each card's ID to the vector
  }
  return cards_id;
}
