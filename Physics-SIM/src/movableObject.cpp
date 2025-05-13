#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "MovableObject.hpp"
#include "Math.hpp"
#include "Entity.hpp"

const int boxSize = 10;

void MovableObject::update(){
    if(ent.getPos().y <= 700 - ent.getSize().y - boxSize - 100 && ent.getPos().y >= boxSize){
        vel.y += acc.y;
        Vector2f newPos = Vector2f(ent.getPos().x, ent.getPos().y + 0.01f * vel.y);
        ent.setPos(newPos);
    }
    else {
        vel.y = 0;
        if(ent.getPos().y < boxSize) ent.setPos(Vector2f(ent.getPos().x, boxSize));
        if(ent.getPos().y > 700 - ent.getSize().y - boxSize - 100) ent.setPos(Vector2f(ent.getPos().x, 700 - ent.getSize().y - boxSize - 100));
    }

    if(ent.getPos().x <= 700 - ent.getSize().x - boxSize && ent.getPos().x >= boxSize){
        vel.x += acc.x;
        Vector2f newPos = Vector2f(ent.getPos().x + 0.01f * vel.x, ent.getPos().y);
        ent.setPos(newPos);
    }
    else{
        vel.x = 0;
        if(ent.getPos().x < boxSize) ent.setPos(Vector2f(boxSize, ent.getPos().y));
        if(ent.getPos().x > 700 - ent.getSize().x - boxSize) ent.setPos(Vector2f(700 - ent.getSize().x - boxSize, ent.getPos().y));
    }
}

void MovableObject::update(Vector2f pxy){
    if(pxy.x <= 700 - ent.getSize().x - boxSize && pxy.x >= boxSize){
        ent.setPos(Vector2f(pxy.x, ent.getPos().y));
    }
    if(pxy.y <= 700 - ent.getSize().y - boxSize && pxy.y >= boxSize){
        ent.setPos(Vector2f(ent.getPos().x, pxy.y));
    }
}