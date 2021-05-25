#ifndef SPYDER_SRC_SPYDER_H_
#define SPYDER_SRC_SPYDER_H_

#include <SDL.h>

#include "bg.h"
#include "pile.h"
#include "const.h"

namespace spyder {

class Spyder {
 public:
  Spyder();

  void GameLoop();
  void End();
 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;

  Background bg_;
  Pile piles_[PILES];
  Pile stock_;
  Pile foundations_[DECKS * SUITS];
  int foundation_i = 0;

  void Redraw();
  void Deal();
  void Shuffle(Card* cards);
  void Spray();
  void Swap(int source, int dest, int clicks);

  int GetLongestBottomSequence(int pile, Rank rank);
  void CheckWin();
};

}

#endif //SPYDER_SRC_SPYDER_H_
