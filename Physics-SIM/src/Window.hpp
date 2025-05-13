#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "Entity.hpp"
#include "UiComponent.hpp"

class Window {
    public:
        Window(const char* title, int w, int h);
        SDL_Texture* loadTexture(const char* fileName);
        void clearRenderer();
        void render(UiComponent& g);
        void render(Entity& ent);
        void display();
        void end();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};