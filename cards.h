#ifndef DOMINION_CARDS_H
#define DOMINION_CARDS_H

#include <string>
#include <vector>

namespace Dominion {

class Game;
class Player;

class Card
{
  /* Card is basically a struct (all public access) for easy
   * definition with no member functions. Once created, Cards
   * should be stored, or at least only presented to users
   * as a pointer to a constant card (i.e. const Card*) to
   * prevent accidental modification.
   */
  public:
    Card();
    Card(std::string title, int cost);

    // required attributes
    std::string title;
    int cost = 0;
    std::vector<std::string> type;

    // trivial card abilities
    int card_increment = 0;
    int action_increment = 0;
    int buy_increment = 0;
    int coin_increment = 0;

    // special card values
    int treasure_value = 0;
    int victory_points = 0;

    // non-trivial card ability text and implementation
    std::string ability_text;
    void (*ability_function_ptr)(Game*, Player*) = 0;
};

//access card definitions by constant pointer
const Card* get_card(std::string title);

}//namespace Dominion

#endif
