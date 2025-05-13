#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "Entity.hpp"
#include "Math.hpp"

class MovableObject {
    public:
        MovableObject(Entity entity, Vector2f velocity, Vector2f acceleration):ent(entity), vel(velocity), acc(acceleration){}
        void setVel(Vector2f vell){
            vel = vell;
        }
        void setAcc(Vector2f accc){
            acc = accc;
        }
        void incSize(Vector2f inc){
            ent.setSize(Vector2f(inc.x + ent.getSize().x, inc.y + ent.getSize().y));
        }
        Entity getEntity(){
            return ent;
        }
        void update();
        void update(Vector2f pxy);
    private:
        Entity ent;
        Vector2f vel, acc;
};