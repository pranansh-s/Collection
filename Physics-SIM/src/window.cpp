#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "Window.hpp"
#include "Entity.hpp"
#include "UiComponent.hpp"

Window::Window(const char* title, int w, int h):window(NULL), renderer(NULL){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* Window::loadTexture(const char* filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    return texture;
}

void Window::clearRenderer(){
    SDL_SetRenderDrawColor(renderer, 106, 106, 106, 255);
    SDL_RenderClear(renderer);
}

void Window::render(UiComponent& g){
    SDL_Rect src;
    src.x = g.getInit().x;
    src.y = g.getInit().y;
    src.w = g.getInit().w;
    src.h = g.getInit().h;

    SDL_Rect dst;
    dst.x = g.getPos().x;
    dst.y = g.getPos().y;
    dst.w = g.getInit().w;
    dst.h = g.getInit().h;
    SDL_RenderCopy(renderer, g.getTexture(), &src, &dst);
}

void Window::render(Entity& ent){
    SDL_Rect src;
    src.x = ent.getInit().x;
    src.y = ent.getInit().y;
    src.w = ent.getInit().w;
    src.h = ent.getInit().h;

    SDL_Rect dst;
    dst.x = ent.getPos().x;
    dst.y = ent.getPos().y;
    dst.w = ent.getInit().w;
    dst.h = ent.getInit().h;
    SDL_RenderCopy(renderer, ent.getTexture(), &src, &dst);
}

void Window::display(){
    SDL_RenderPresent(renderer);
}

void Window::end(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
