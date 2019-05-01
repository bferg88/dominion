#ifndef DOMINION_PLAYER_IMPL_H
#define DOMINION_PLAYER_IMPL_H

#include "dominion.h"

#include <string>
#include <vector>

namespace Dominion {

class AutoPlayer : public Player
{
  public:
    AutoPlayer();
    AutoPlayer(std::string name);
    void take_turn_impl();
};

class HumanPlayer : public Player
{
  public:
    HumanPlayer();
    HumanPlayer(std::string name);
    void take_turn_impl();
};

/* Functions for doing useful things */
const Card* get_card(std::string title);
void shuffle_cards(std::vector<const Card*>& cards);

}//namespace Dominion

#endif
