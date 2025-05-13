#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "Math.hpp"

class Entity {
    public:
        Entity(Vector2f position, Vector2f size, SDL_Texture* texture):pos(position), tex(texture), sz(size){
            init.x = 0;
            init.y = 0;
            init.w = size.x;
            init.h = size.y;
        }
        void setPos(Vector2f newPos){
            pos = newPos;
        }
        void setSize(Vector2f bumpSize){
            init.w = bumpSize.x;
            init.h = bumpSize.y;
            sz.x = bumpSize.x;
            sz.y = bumpSize.y;
        }
        Vector2f getSize(){
            return sz;
        }
        Vector2f getPos(){
            return pos;
        }
        SDL_Texture* getTexture(){
            return tex;
        }
        SDL_Rect getInit(){
            return init;
        }
    private:
        Vector2f pos, sz;
        SDL_Rect init;
        SDL_Texture* tex;
};