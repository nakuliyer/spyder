#ifndef SPYDER_SRC_BG_H_
#define SPYDER_SRC_BG_H_

#include <SDL.h>
#include <iostream>

namespace spyder {

class Background {
 public:
  Background() = default;
  explicit Background(SDL_Renderer* renderer);

  void Draw();
 private:
  SDL_Renderer* renderer_;
};

}

#endif //SPYDER_SRC_BG_H_
