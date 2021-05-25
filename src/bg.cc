#include "bg.h"

#include "const.h"

spyder::Background::Background(SDL_Renderer* renderer) : renderer_(renderer) {}

void spyder::Background::Draw() {
  SDL_Surface* image = SDL_LoadBMP(BACKGROUND_PATH);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, image);
  SDL_FreeSurface(image);
  SDL_RenderCopy(renderer_, texture, nullptr, nullptr);
  SDL_DestroyTexture(texture);
}
