#ifndef SPYDER_SRC_CONST_H_
#define SPYDER_SRC_CONST_H_

#include <string>

#define FPS 60
#define TITLE "Spyder"
#define WIDTH 700
#define HEIGHT 500
#define PADDING 5
#define FAN_BACK_PADDING 10
#define FAN_FRONT_PADDING 25
#define CARD_WIDTH 65
#define CARD_HEIGHT 100

#define SUITS 2
#define DECKS 4 // this is the number of copies of each suit

#define PILES 10
#define INIT_PILES (int[]){6, 6, 6, 6, 5, 5, 5, 5, 5, 5}
#define SHUFFLE_SWAPS 1000

#define BACKGROUND_PATH "assets/bg.bmp"
#define CARDS_DIRECTORY "assets/cards/"
#define CARDS_EXTENSION ".bmp"

namespace spyder {

enum Suit {
  kClubs,
  kDiamonds,
  kHearts,
  kSpades
};

const Suit suits[4] = {kSpades, kHearts, kClubs, kDiamonds};

std::string SuitToString(Suit suit);

enum Rank {
  kA,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,
  k10,
  kJ,
  kQ,
  kK
};

const Rank ranks[13] = {kK, kQ, kJ, k10, k9, k8, k7, k6, k5, k4, k3, k2, kA};

std::string RankToString(Rank rank);
int RankToValue(Rank rank);

}

#endif //SPYDER_SRC_CONST_H_
