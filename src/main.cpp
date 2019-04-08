#include "Func.h"
#include "BackGround.h"
#include "Pack2x4.h"
#include <time.h>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Event events;
int SCREEN_HEIGHT = 1000;
int SCREEN_WIDTH = 1000;
std::vector< std::vector<std::vector<std::string>>> path_imgs = std::vector< std::vector<std::vector<std::string>>>(3, std::vector<std::vector<std::string>>(3, std::vector<std::string>()));

int main(){
    srand(time(NULL));
    bool quit = false;
    Func::init();
    Func::ImgsData();
    BackGround background("src/img_src/Screenshot_2019-03-31-12-00-20.png");
    
    
    Pack2x4 pack;
    pack.init();
    while(!quit){
        while(SDL_PollEvent(&events)){
            if(events.type == SDL_QUIT){
                quit = true;
                break;
            }
            pack.HandleInputEvents(events);
        }
        SDL_RenderClear(gRenderer);
        background.render();
        pack.Show();
        SDL_RenderPresent(gRenderer);
        Func::Close();
    }
    
    
    
    Func::Close();
    return 0;
}