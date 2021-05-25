#include "pile.h"

spyder::Pile::Pile() {}

void spyder::Pile::AddCard(const Card& card) {
  cards.push_back(card);
}

void spyder::Pile::DrawFan(int x, int y) const {
  int i = 0;
  int k = 0;
  for (const Card& card : cards) {
    card.Draw(x, y + i * FAN_BACK_PADDING + k * FAN_FRONT_PADDING);
    if (k == 0 && !card.IsUp()) ++i;
    else ++k;
  }
}

void spyder::Pile::DrawStack(int x, int y) const {
  if (cards.empty()) return;
  cards[cards.size() - 1].Draw(x, y);
}

spyder::Card spyder::Pile::RemoveAt(int i) {
  Card back = cards[i];
  cards.erase(cards.begin() + i);
  return back;
}

spyder::Card spyder::Pile::RemoveTop() {
  return RemoveAt(size() - 1);
}

spyder::Card& spyder::Pile::CardAt(int i) {
  return cards[i];
}

spyder::Card& spyder::Pile::Top() {
  return CardAt(size() - 1);
}

int spyder::Pile::size() const {
  return cards.size();
}

bool spyder::Pile::empty() const {
  return cards.empty();
}
