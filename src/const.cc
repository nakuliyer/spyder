#include "const.h"

std::string spyder::SuitToString(Suit suit) {
  switch (suit) {
    case kClubs: return "C";
    case kDiamonds: return "D";
    case kHearts: return "H";
    case kSpades: return "S";
  }
}

std::string spyder::RankToString(Rank rank) {
  switch (rank) {
    case kA: return "A";
    case k2: return "2";
    case k3: return "3";
    case k4: return "4";
    case k5: return "5";
    case k6: return "6";
    case k7: return "7";
    case k8: return "8";
    case k9: return "9";
    case k10: return "10";
    case kJ: return "J";
    case kQ: return "Q";
    case kK: return "K";
  }
}

int spyder::RankToValue(Rank rank) {
  for (int i = 0; i < 13; ++i) {
    if (ranks[i] == rank) return i;
  }
  return -1;
}