#ifndef GVAR
#define GVAR

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;
extern SDL_Event events;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

extern std::vector< std::vector<std::vector<std::string>>> path_imgs;



#else
#endif