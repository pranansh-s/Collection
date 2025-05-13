#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Window.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "MovableObject.hpp"
#include "UiComponent.hpp"

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window window("physics", 700, 700);
	SDL_Texture *ball = window.loadTexture("gfx/circle.png");
	SDL_Texture *rampL = window.loadTexture("gfx/rampL.png");
	SDL_Texture *rampR = window.loadTexture("gfx/rampR.png");
	SDL_Texture *wall = window.loadTexture("gfx/wall.png");

	SDL_Texture *bottomTab = window.loadTexture("gfx/bottomTab.png");

	Vector2f initialVel = Vector2f(0, 0);
	Vector2f initialAcc = Vector2f(0, 9.8f);
	std::vector<MovableObject> objects = {MovableObject(Entity(Vector2f(300, 300), Vector2f(32, 32), ball), initialVel, initialAcc),
										  MovableObject(Entity(Vector2f(150, 650), Vector2f(16, 16), ball), initialVel, initialAcc)};	
	std::vector<UiComponent> guiComponents = {UiComponent(bottomTab, Vector2f(-42, 650), Vector2f(784, 300))};

	bool isRunning = true;
	bool isleftDown = false;
	bool lctr = false;
	bool bottom = false;
	MovableObject *selected = NULL;
	Vector2f mousePos;
	Vector2f savedPos;
	SDL_Event event;

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
			while (SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT){
					isRunning = false;
					break;
				}
				else if(event.type == SDL_MOUSEMOTION){
					mousePos = Vector2f(event.motion.x, event.motion.y);
				}
				else if(event.type == SDL_MOUSEBUTTONDOWN){
					if(event.button.button == SDL_BUTTON_LEFT && !isleftDown){
						isleftDown = true;
						if(!lctr){
							for(MovableObject &e : objects){
								Vector2f p = e.getEntity().getPos();
								if((mousePos.x >= p.x && mousePos.x <= p.x + e.getEntity().getSize().x) 
								&& (mousePos.y >= p.y && mousePos.y <= p.y + e.getEntity().getSize().y)){
									e.setVel(Vector2f(0, 0));
									selected = &e;
								}
							}
						}
						else if(bottom){
							
						}
					}
				}
				else if(event.type == SDL_KEYUP){
					if(event.key.keysym.sym == SDLK_LCTRL && lctr){
						lctr = false;
					}
				}
				else if(event.type == SDL_MOUSEBUTTONUP){
					if(isleftDown && event.button.button == SDL_BUTTON_LEFT){
						if(lctr){
							for(MovableObject &e : objects){
								if(selected == &e){
									float xx = e.getEntity().getPos().x - mousePos.x;
									float yy = e.getEntity().getPos().y - mousePos.y;

									e.setVel(Vector2f(xx * 4, yy * 4));
									e.setAcc(Vector2f(0, 9.8f));
								}
							}
						}
						selected = NULL;
						isleftDown = false;
					}
				}
				else if(event.type == SDL_KEYDOWN){
					if(event.key.keysym.sym == SDLK_LCTRL && selected && !lctr){
						lctr = true;
						for(MovableObject &e : objects){
							if(selected == &e){
								savedPos = Vector2f(mousePos.x - e.getEntity().getSize().x / 2, 
													mousePos.y - e.getEntity().getSize().y / 2);
							}
						}			
					}
				}
				else if(event.type == SDL_MOUSEWHEEL){
					for(MovableObject &e : objects){
						if(selected == &e){
							if(event.wheel.y > 0 && e.getEntity().getSize().x < 100 && e.getEntity().getSize().y < 100){
								e.incSize(Vector2f(4, 4));
							}
							else if(event.wheel.y < 0 && e.getEntity().getSize().x > 10 && e.getEntity().getSize().y > 10){
								e.incSize(Vector2f(-4, -4));
							}
						}
					}
				}
			}
			UiComponent& b = guiComponents[0];
			if(mousePos.y >= 650 && b.getPos().y >= 500){
				b.setPos(Vector2f(b.getPos().x, b.getPos().y - 10));
				bottom = true;
			}
			else if(mousePos.y < 500 && b.getPos().y < 650){
				b.setPos(Vector2f(b.getPos().x, b.getPos().y + 10));
				bottom = false;
			}
			
			for(MovableObject &e : objects){
				if(selected == &e && lctr){
					e.update(savedPos);
				}
				else if(selected == &e){
					e.update(Vector2f(mousePos.x - e.getEntity().getSize().x / 2, 
									  mousePos.y - e.getEntity().getSize().y / 2));
				}				
				else e.update();
			}
			accumulator -= timeStep;
		}

		window.clearRenderer();
		for(MovableObject& e : objects){
			Entity x = e.getEntity();
			window.render(x);
		}
		for(UiComponent& e : guiComponents){
			window.render(e);
		}
		window.display();
	}

	window.end();
	SDL_Quit();
	
	return 0;
}