#ifndef SPYDER_SRC_CARD_H_
#define SPYDER_SRC_CARD_H_

#include <SDL.h>
#include <iostream>

#include "const.h"

namespace spyder {

class Card {
 public:
  Card() = default;
  Card(Suit suit, Rank rank, SDL_Renderer* renderer);
  void Draw(int x, int y) const;

  Suit GetSuit() const;
  Rank GetRank() const;
  bool IsUp() const;
  void Flip();
 private:
  SDL_Renderer* renderer_ = nullptr;

  Suit suit_;
  Rank rank_;
  bool is_up_;
};

}

#endif //SPYDER_SRC_CARD_H_
