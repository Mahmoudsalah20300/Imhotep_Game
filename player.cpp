#include "player.hpp"

//--------------------------------------------------------------------------------------------------------------------
Player::Player(const int player_id, const int points)
                :player_id_(player_id), points_(points) {}

//--------------------------------------------------------------------------------------------------------------------
Player::~Player() {}

//--------------------------------------------------------------------------------------------------------------------
int Player::getPlayerId() const
{
    return player_id_;
}

//--------------------------------------------------------------------------------------------------------------------
int Player::getPlayerPoints() const
{
    return points_;
}

//--------------------------------------------------------------------------------------------------------------------
void Player::addPlayerPoints(const int points)
{
    points_ += points; 
}


void Player::addPlayerCard(std::shared_ptr<MarketCard> card)
{
    player_cards_.push_back(card);
}

