#include "card.h"

spyder::Card::Card(Suit suit, Rank rank, SDL_Renderer* renderer)
    : renderer_(renderer), suit_(suit), rank_(rank), is_up_(false) {}

void spyder::Card::Draw(int x, int y) const {
  if (renderer_ == nullptr) return;

  SDL_Rect rect = {x, y, CARD_WIDTH, CARD_HEIGHT};
  if (is_up_) {
    std::string path = CARDS_DIRECTORY + RankToString(rank_) + SuitToString(suit_) + CARDS_EXTENSION;
    SDL_Surface* image = SDL_LoadBMP(path.c_str());
    SDL_Texture* card_front = SDL_CreateTextureFromSurface(renderer_, image);
    SDL_FreeSurface(image);
    SDL_RenderCopy(renderer_, card_front, nullptr, &rect);
  } else {
    std::string path = "assets/cards/blue_back.bmp";
    SDL_Surface* image = SDL_LoadBMP(path.c_str());
    SDL_Texture* card_back = SDL_CreateTextureFromSurface(renderer_, image);
    SDL_FreeSurface(image);
    SDL_RenderCopy(renderer_, card_back, nullptr, &rect);
  }
}

spyder::Suit spyder::Card::GetSuit() const {
  return suit_;
}

spyder::Rank spyder::Card::GetRank() const {
  return rank_;
}

bool spyder::Card::IsUp() const {
  return is_up_;
}

void spyder::Card::Flip() {
  is_up_ = !is_up_;
}
