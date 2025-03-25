#include "GreenCard.hpp"
#include "../ConstructionSites/Pyramid.hpp"
#include "../ConstructionSites/temple.hpp"
#include "../ConstructionSites/burial_chamber.hpp"
#include "../ConstructionSites/Obelisk.hpp"



GreenCard::GreenCard(int card_id, const std::string& color, const std::string& name)
                   : MarketCard(card_id, color, name) {}

int GreenCard::getId() const
{
  return card_id_;
}

std::string GreenCard::getColor() const
{
  return color_;
}

std::string GreenCard::getName() const
{
  return name_;
}

void GreenCard::setId(int new_id)
{
  card_id_ = new_id;
}

void GreenCard::setColor(std::string& new_color)
{
  color_ = new_color;
}

void GreenCard::setName(std::string& new_name)
{
  name_ = new_name;
}

int GreenCard::playGreenCardEffect(std::vector<std::shared_ptr<ConstructionSite>>& construction_sites)
{
  int counter = 0;
  points_ = 0;
  
  if(card_id_ == 3)
  {
    auto pyramid = 
        std::dynamic_pointer_cast<Pyramid>(construction_sites.at(1));
    elements = pyramid->getallelements();
    counter = elements.size();
  }
  
  if(card_id_ == 4)
  {
    auto temple_t = 
        std::dynamic_pointer_cast<temple>(construction_sites.at(2));
    elements = temple_t->getallelements();
    counter = elements.size();

  }
  if(card_id_ == 5)
  {
    auto burial = 
        std::dynamic_pointer_cast<BurialChamber>(construction_sites.at(3));
    elements = burial->getAllElements();
    counter = elements.size();
    
  }
  
  if(card_id_ == 6)
  {
    auto obelisk = 
        std::dynamic_pointer_cast<Obelisk>(construction_sites.at(4));
    elements = obelisk->getObeliskHeights();

    for(auto &element : elements)
    {
      counter += element;
    }
  }

  points_ = counter / 3;

  return points_;
}




