#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "Window.hpp"

//Initializes a window and renderer
Window::Window(const char* title, int w, int h):window(NULL), renderer(NULL){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

//Loads and returns texture to program
SDL_Texture* Window::loadTexture(const char* filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    return texture;
}

void Window::drawPoint(Vector2f pos, Color co){
    SDL_SetRenderDrawColor(renderer, co.r, co.g, co.b, co.a);
    SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

//Sets a background colour and clears renderer (used before each frame)
void Window::clearRenderer(){
    SDL_SetRenderDrawColor(renderer, 106, 106, 106, 255);
    SDL_RenderClear(renderer);
}

//Draws whatever has been rendered to the window
void Window::display(){
    SDL_RenderPresent(renderer);
}

//Destroys window and renderer (used before quitting to avoid memory leak)
void Window::end(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
