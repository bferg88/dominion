#ifndef DOMINION_DOMINION_H
#define DOMINION_DOMINION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Dominion {

/* forward declaration of classes */
class Player;
/**/


class Game
{
  public:
    Game();
    void add_player(Player* player);
    void start();

  private:
    vector<Player*> players;
};


class Card
{
  public:
    Card();
    Card(string title, int cost);

    // required attributes
    string title;
    int cost = 0;
    vector<string> type;

    // trivial card abilities
    int card_increment = 0;
    int action_increment = 0;
    int buy_increment = 0;
    int coin_increment = 0;

    // special card values
    int treasure_value = 0;
    int victory_points = 0;

    // non-trivial card ability text and implementation
    string ability_text;
    void (*ability_function_ptr)(Game) = 0;
};


/*
 * Abstract implementation of Player is designed to be a base class
 * that could  be immplemented as human, AI, etc.
 *
 * todo: 
 * Validation: no playing cards, once buy phase begins
 */
class Player
{
  public:
    Player(); 
    Player(string name);

    string name="N/A"; //player name, used for user feedback

    vector<const Card*> deck;    // top card of deck is last element
    vector<const Card*> hand;    // order is irrelevant
    vector<const Card*> discard; // top card of discard is last element

    void draw_card();
    void draw_cards(int num_cards=5);

    void play_card(string card_title);
//    void play_card(const Card* card);

    void gain_card(string card_title);

    void buy_card(string card_title);
    //no more playing cards once buying begins

    void end_turn();

    /*
     * Virtual - requires implementation
     */
    virtual void take_turn() = 0;
  
  private:
    void replace_deck_from_discard();
};

/* Player Descendents */

class HumanPlayer : public Player
{
  public:
    HumanPlayer();
    HumanPlayer(string name);
    void take_turn();
};

class AutoPlayer : public Player
{
  public:
    AutoPlayer();
    AutoPlayer(string name);
    void take_turn();
};


/*
 * Functions for doing useful things
 */

// get card by title
const Card* get_card(string title);

// shuffle vector of (pointers to) cards
void shuffle_cards(vector<const Card*>& cards);


}//namespace Dominion


#endif
