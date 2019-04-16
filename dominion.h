#ifndef DOMINION_DOMINION_H
#define DOMINION_DOMINION_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Dominion {

using namespace std;

class Player;
class Card;

class Supply
{
  /* card_piles holds pairs representing the cards
   * available in the supply and their remaining quantity */
  public:
    map<const Card*, int> card_piles;
    void pop_card(const Card*);
    /* if security were of utmost importance, I would need to create a
     * read-only map for card_piles, but I'm choosing to trust Player
     * implementations to only make modifications to Supply via pop_card()
     * for the sake of speed and reduced complexity.
     */

  private:
    void setup(vector<Player*> players);
    bool is_game_over();
    int piles_empty = 0;
    friend class Game;
};


class Game
{
  public:
    Game();
    void add_player(Player* player);
    void start();

  private:
    Supply supply;
    vector<Player*> players;
};


/*
 * Abstract implementation of Player is designed to be a base class
 * that could  be immplemented as human, AI, etc.
 */
class Player
{
  public:
    Player(); 
    Player(string name);

    Supply* supply;

    // accessors and convenience functions
    int get_buys();
    int get_purse();
    /* purse is equal to temporary treasure gained from
     * action cards until "start_buy_phase()" is callrd
     * at which point the value of any present treasure
     * cards is added to purse. This happens when 
     * start_buy_phase() is called.*/
    int count_treasure();
    
    /* Player turn overview:
     * A) Action phase - play action card(s)
     * B) Buy phase - buy card(s)
     * C) Clean-up phase - discard played cards and remainder of hand
     *
     * These functions are used by an implementation to
     * take part in a turn. If functions are called at the wrong time
     * (wrong phase, already in buy phase, etc) they will do nothing.
     */

    // functions necessary to take complete tur
    void play_action_card(string title); //during Action phase
    void start_buy_phase(); //start Buy phase
    void buy_card(string title); // during Buy phase


  protected:
    virtual void take_turn_impl() = 0;
  
  private:
    string name="N/A"; //player name, used for user feedback

    vector<const Card*> deck;    // top card of deck is last element
    vector<const Card*> hand;    // order is irrelevant
    vector<const Card*> play_area; // cards activated on turn
    vector<const Card*> discard_pile; // top card of discard pile is last element

    void draw_card();
    void draw_cards(int num_cards=5);
    void take_turn();

    /* for tracking the current turn */
    int actions = 1;
    int card_draws = 0;
    int buys = 1; 
    int purse = 0;
    bool buy_phase = false;

    friend class Game;
};


/* Player descendents */

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
