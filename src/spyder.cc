#include <iostream>
#include <iterator>
#include <random>

#include "spyder.h"
#include "card.h"

spyder::Spyder::Spyder() {
  SDL_Init(SDL_INIT_VIDEO);

  window_ =
      SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);

  bg_ = Background(renderer_);
  Deal();
}

void spyder::Spyder::GameLoop() {
  SDL_Event e;
  bool quit = false;
  bool redraw = true;
  int select_first = -1;
  int select_first_clicks = 0;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          select_first = -1;
        } else if (e.key.keysym.sym == SDLK_SPACE) {
          Spray();
          redraw = true;
        }
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        int i = (x - PADDING) / (PADDING + CARD_WIDTH);
        if (y < PADDING + CARD_HEIGHT && x < PADDING + CARD_WIDTH) {
          Spray();
          redraw = true;
        } else if (y > 2 * PADDING + CARD_HEIGHT) {
          if (select_first == -1) {
            select_first = i;
            select_first_clicks = 1;
          } else if (select_first == i) {
            ++select_first_clicks;
          } else {
            int select_second = i;
            Swap(select_first, select_second, select_first_clicks);
            redraw = true;
            select_first = -1;
          }
        }
      }

      if (redraw) {
        Redraw();
        redraw = false;
      }
      SDL_RenderPresent(renderer_);
      SDL_Delay(1000 / FPS);
    }
  }
}

void spyder::Spyder::Deal() {
  int cards_count = SUITS * 13 * DECKS;
  Card cards[cards_count];
  for (int i = 0; i < DECKS; ++i) {
    for (int j = 0; j < SUITS; ++j) {
      for (int k = 0; k < 13; ++k) {
        cards[i * SUITS * 13 + j * 13 + k] = Card(suits[j], ranks[k], renderer_);
      }
    }
  }
  Shuffle(cards);

  int k = 0;
  for (int i = 0; i < PILES; ++i) {
    for (int j = 0; j < INIT_PILES[i];
    ++j) {
      piles_[i].AddCard(cards[k++]);
      if (j == INIT_PILES[i] -1) {
        piles_[i].Top().Flip();
      }
    }
  }
  while (k < cards_count) {
    stock_.AddCard(cards[k++]);
  }
}

void spyder::Spyder::Shuffle(Card* cards) {
  int cards_count = SUITS * 13 * DECKS;

  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, cards_count - 1);

  for (int i = 0; i < SHUFFLE_SWAPS; ++i) {
    std::swap(cards[dist(rd)], cards[dist(rd)]);
  }
}

void spyder::Spyder::Spyder::Spray() {
  for (int i = 0; i < PILES; ++i) {
    if (stock_.empty()) return;
    Card back = stock_.RemoveTop();
    back.Flip();
    piles_[i].AddCard(back);
  }
  CheckWin();
}

void spyder::Spyder::Swap(int source, int dest, int clicks) {
  if (piles_[source].empty()) return;

  Rank seeking;
  if (piles_[dest].empty()) {
    Card& card_seeking = piles_[source].CardAt(piles_[source].size() - clicks);
    if (!card_seeking.IsUp()) return;
    seeking = card_seeking.GetRank();
  } else {
    seeking = ranks[RankToValue(piles_[dest].Top().GetRank()) + 1];
  }
  int k = GetLongestBottomSequence(source, seeking);
  if (piles_[dest].empty() && k != clicks) return;

  while (k > 0) {
    Card c = piles_[source].RemoveAt(piles_[source].size() - k);
    piles_[dest].AddCard(c);
    --k;
  }
  if (!piles_[source].Top().IsUp()) piles_[source].Top().Flip();

  CheckWin();
};

int spyder::Spyder::GetLongestBottomSequence(int pile, Rank rank) {
  if (piles_[pile].empty()) return 0;
  if (piles_[pile].size() == 1 && piles_[pile].Top().GetRank() == rank) return 1;
  else if (piles_[pile].size() == 1) return 0;

  int i = piles_[pile].size() - 1;
  while (i >= 1) {
    Card& next_up = piles_[pile].CardAt(i - 1);
    Card& current = piles_[pile].CardAt(i);

    if (current.GetRank() == rank) return 1;
    if (!next_up.IsUp() || RankToValue(next_up.GetRank()) + 1 != RankToValue(current.GetRank())
        || next_up.GetSuit() != current.GetSuit())
      return 0;
    else if (next_up.GetRank() == rank) return piles_[pile].size() - i + 1;
    --i;
  }
  return 0;
}

void spyder::Spyder::CheckWin() {
  for (int i = 0; i < PILES; ++i) {
    if (GetLongestBottomSequence(i, Rank::kK) == 13) {
      for (int j = 0; j < 13; ++j) {
        foundations_[foundation_i].AddCard(piles_[i].RemoveTop());
        foundations_[foundation_i].Top().Flip();
      }
      if (!piles_[i].Top().IsUp()) piles_[i].Top().Flip();
      ++foundation_i;
    }
  }
}

void spyder::Spyder::Redraw() {
  bg_.Draw();
  for (int i = 0; i < PILES; ++i) {
    piles_[i].DrawFan(PADDING + (CARD_WIDTH + PADDING) * i, 2 * PADDING + CARD_HEIGHT);
  }
  for (int i = 0; i < DECKS; ++i) {
    foundations_[i].DrawStack(PADDING + (CARD_WIDTH + PADDING) * (PILES - i - 1), PADDING);
  }
  stock_.DrawStack(PADDING, PADDING);
}

void spyder::Spyder::End() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
