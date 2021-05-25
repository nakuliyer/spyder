#ifndef SPYDER_SRC_PILE_H_
#define SPYDER_SRC_PILE_H_

#include <vector>

#include "card.h"

namespace spyder {

class Pile {
 public:
  Pile();
  void AddCard(const Card& card);
  void DrawFan(int x, int y) const;
  void DrawStack(int x, int y) const;
  Card RemoveAt(int i);
  Card RemoveTop();
  Card& Top();
  Card& CardAt(int i);
  int size() const;
  bool empty() const;
 private:
  std::vector<Card> cards = std::vector<Card>();
};

}

#endif //SPYDER_SRC_PILE_H_
