#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "Window.hpp"
#include "Math.hpp"

using namespace std;

const int screenWidth = 400;
const int screenHeight = 400;
float k = 0;

Color checkPoint(Vector2f ps){
    Vector2f z = Vector2f(ps.x, ps.y);

    for(float i = 0; i < 100; i++){
        // MandelBrot
        // float t = z.x * z.x - z.y * z.y + ps.x;
        // z.y = 2 * z.x * z.y + ps.y;
        // z.x = t;

        //Julia
        float t = z.x * z.x - z.y * z.y + sin(k);
        z.y = 2 * z.x * z.y + cos(k);
        z.x = t;

        if(z.x * z.x + z.y * z.y > 4){
            float t = i / 100;
            return Color((int)(9*(1-t)*t*t*t*255), (int)(15*(1-t)*(1-t)*t*t*255), (int)(8.5*(1-t)*(1-t)*(1-t)*t*255), 255);
        }
    }
    return Color(0, 0, 0, 255);
}

int main(int argv, char** args){
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window("julia", screenWidth, screenHeight);

    bool isRunning = true;
    SDL_Event event;

    //timeStep -> Allows rendering at 100 frames per second: 1/100
    float timeStep = 0.01f;
	float currentTime = SDL_GetTicks() * 0.001f;
	float accumulator = 0.0f;
	while (isRunning)
	{
		float newTime = SDL_GetTicks() * 0.001f;
		float f = newTime - currentTime;
		currentTime = newTime;
		
		accumulator += f;
        while(accumulator >= timeStep){
            while (SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
					isRunning = false;
					break;
				}
                //Register key events here ->
            }
            //Perform once per frame ->
            accumulator -= timeStep;
        }

        window.clearRenderer();

        for(float i = 0; i < screenWidth; i++){
            for(float j = 0; j < screenHeight; j++){       
                Vector2f p = Vector2f(((i / screenWidth) * 4) - 2, ((j / screenHeight) * 4) - 2);

                Color c = checkPoint(p);
                window.drawPoint(Vector2f(i, j), c);
            }   
        }
        k += 0.1f;
        //Render content here ->
        window.display();
    }
    window.end();
    SDL_Quit();

    return 0;
}
