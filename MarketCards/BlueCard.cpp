#include "BlueCard.hpp"

BlueCard::BlueCard(int card_id, const std::string& color, const std::string& name)
                   : MarketCard(card_id, color, name) {}

int BlueCard::getId() const
{
  return card_id_;
}

std::string BlueCard::getColor() const
{
  return color_;
}

std::string BlueCard::getName() const
{
  return name_;
}

void BlueCard::setId(int new_id)
{
  card_id_ = new_id;
}

void BlueCard::setColor(std::string& new_color)
{
  color_ = new_color;
}

void BlueCard::setName(std::string& new_name)
{
  name_ = new_name;
}





