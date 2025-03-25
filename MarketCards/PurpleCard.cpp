#include "PurpleCard.hpp"

PurpleCard::PurpleCard(int card_id, const std::string& color, const std::string& name)
                   : MarketCard(card_id, color, name) {}

int PurpleCard::getId() const
{
  return card_id_;
}

std::string PurpleCard::getColor() const
{
  return color_;
}

std::string PurpleCard::getName() const
{
  return name_;
}

void PurpleCard::setId(int new_id)
{
  card_id_ = new_id;
}

void PurpleCard::setColor(std::string& new_color)
{
  color_ = new_color;
}

void PurpleCard::setName(std::string& new_name)
{
  name_ = new_name;
}

int PurpleCard::playPurpleCardEffect(int number_of_cards)
{
  if (number_of_cards <= 0)
  {
    return 0;
  }
  if (number_of_cards == 1)
  {
      return 1;
  }
  else if (number_of_cards == 2)
  {
    return 3;
  }
  else if (number_of_cards == 3)
  {
    return 6;
  }
  else if (number_of_cards == 4)
  {
    return 10;
  }
  else if (number_of_cards == 5)
  {
    return 15;
  }
  else 
  {
    return 2 * (number_of_cards - 5) + 15;
  }
  return points_;
}




