#include "Func.h"
#include "BackGround.h"
#include "Pack2x4.h"
#include <time.h>

#ifdef BASEOBJ_H_
#define LOG
void Func::log(std::string mgs,void* from, bool error, std::ostream &os){
    if(from != NULL){
        if(error){
            os << "From " << ((BaseObj*) from)->name() << ": " << mgs << SDL_GetError() <<std::endl;
        } else {
            os << "From " << ((BaseObj*) from)->name() << ": " << mgs << std::endl;
        }
    } else {
        if(error){
            os << mgs  << " "<< SDL_GetError() << std::endl;
        } else {
            os << mgs << std::endl;
        }
    } 
}
#endif

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
    BackGround background(IMGPATH::BACKGROUNG);
    Pack2x4* pack = new Pack2x4;

    pack->init();
    int id = 0;
#ifdef LOG
    Func::log("Start Game Loop");
#endif
    while(!quit){
        SDL_SetRenderTarget(gRenderer, NULL);
        if(pack->wasClose()){
            delete pack;
            pack = new Pack2x4;
            id++;
            pack->init();
        }
        while(SDL_PollEvent(&events)){
            if(events.type == SDL_QUIT){
                quit = true;
                break;
            }
            pack->HandleInputEvents(events);
        }
        SDL_RenderClear(gRenderer);
        background.render();
        pack->Show();
        SDL_RenderPresent(gRenderer);
    }
    
    
    
    Func::Close();
    return 0;
}