#include "RedCard.hpp"
#include "../ship.hpp"
#include "../ConstructionSites/ConstructionSiteType.hpp"
#include "../ConstructionSites/Pyramid.hpp"
#include "../ConstructionSites/burial_chamber.hpp"
#include "../ConstructionSites/Obelisk.hpp"
#include "../message.hpp"

RedCard::RedCard(int card_id, const std::string& color, const std::string& name)
                   : MarketCard(card_id, color, name) {}

//getter
int RedCard::getId() const
{
  return card_id_;
}

std::string RedCard::getColor() const
{
  return color_;
}

std::string RedCard::getName() const
{
  return name_;
}

//setter
void RedCard::setId(int new_id)
{
  card_id_ = new_id;
}

void RedCard::setColor(std::string& new_color)
{
  color_ = new_color;
}

void RedCard::setName(std::string& new_name)
{
  name_ = new_name;
}

int RedCard::playRedCardsEffect( std::vector<std::shared_ptr<ConstructionSite>>& construction_sites,
                                     int current_player)
{
  Ship ship(-1, 1, 0, false);
  ship.setShipDetails(3);
  ship.addStone(current_player, 0);
  if(card_id_ == 0)
  {
    construction_sites.at(1)->unloadShip(ship);
    return 1;
  }
  else if(card_id_ == 1)
  {
    construction_sites.at(3)->unloadShip(ship);
    return 3;
  }
  else if(card_id_ == 2)
  {
    construction_sites.at(4)->unloadShip(ship);
    return 4;
  }

  return -1;
}




