#ifndef DOMINION_PLAYER_IMPL_H
#define DOMINION_PLAYER_IMPL_H

#include "dominion.h"

#include <string>
#include <vector>

namespace Dominion {

using namespace std;

class AutoPlayer : public Player
{
  public:
    AutoPlayer();
    AutoPlayer(string name);
    void take_turn_impl();
};


class HumanPlayer : public Player
{
  public:
    HumanPlayer();
    HumanPlayer(string name);
    void take_turn_impl();
};


/* Functions for doing useful things */
const Card* get_card(string title);
void shuffle_cards(vector<const Card*>& cards);


}//namespace Dominion


#endif
