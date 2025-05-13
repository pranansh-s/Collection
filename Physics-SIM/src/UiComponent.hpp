#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "Math.hpp"

class UiComponent {
    public:
        UiComponent(SDL_Texture* text, Vector2f posi, Vector2f size):pos(posi), tex(text), sz(size){
            init.x = 0;
            init.y = 0;
            init.w = size.x;
            init.h = size.y;
        }
        void setPos(Vector2f newPos){
            pos = newPos;
        }
        Vector2f getPos(){
            return pos;
        }
        SDL_Rect getInit(){
            return init;
        }
        SDL_Texture* getTexture(){
            return tex;
        }
    private:
        SDL_Rect init;
        SDL_Texture* tex;
        Vector2f pos, sz;
};