#include "player_impl.h"

using namespace std;

namespace Dominion {

/*AutoPlayer*/
AutoPlayer::AutoPlayer() {}
AutoPlayer::AutoPlayer(string name) : Player(name) {}

void AutoPlayer::take_turn_impl()
{
  start_buy_phase();
  int purse = get_purse();
  cout << "purse value: " << purse << endl;

  while(get_buys() > 0 && get_purse() >= 3)
  {
    int purse = get_purse();
    if(purse >= 8)
    {
      buy_card("Province");
    }
    else if(purse >= 6)
    {
      buy_card("Gold");
    }
    else
    {
      buy_card("Silver");
    }
  }
}

/* HumanPlayer */
HumanPlayer::HumanPlayer() {}

HumanPlayer::HumanPlayer(string name) : Player(name) {}

void HumanPlayer::take_turn_impl()
{
  //todo: implement command line interface for human player
}


}//namespace Dominion


