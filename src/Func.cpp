#include "Func.h"

bool Func::init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        success = false;
        SDL_Log("Fail to init! %s", SDL_GetError());
    }
    else {
        gWindow = SDL_CreateWindow("Train of Thought", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            success = false;
            SDL_Log("Fail created window! %s", SDL_GetError());
        }
        else {
            int imgFlag = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlag) & imgFlag)){
                SDL_Log("Init IMG failed! %s", SDL_GetError());
                success = false;
            } else {
                gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
                if (gRenderer == NULL) {
                    success = false;
                    SDL_Log("Fail created gRenderer! %s", SDL_GetError());
                }
                else {
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            }
        }
    }
    return success;
}

void Func::Close() {
    if (gRenderer != NULL) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }
    if (gWindow != NULL) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }
    if (gTexture != NULL) {
        SDL_DestroyTexture(gTexture);
    }
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Func::loadImg(std::string path){
    SDL_Surface* tmp_sur = IMG_Load(path.c_str());
    SDL_Texture* texture = NULL;
    if(tmp_sur == NULL){
        SDL_Log("Surface .. %s", SDL_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(gRenderer, tmp_sur);
        if(texture ==  NULL){
            SDL_Log("Texture .. %s", SDL_GetError());
        }
    }
    SDL_FreeSurface(tmp_sur);
    return texture;
}


void Func::log(std::string mgs){
    std::cout << mgs << std::endl;
}

void Func::ImgsData(){
    path_imgs[0][0] = {
        "src/img_src/block1x1_1_92x92.png",
        "src/img_src/block1x1_2_142x142.png",
        "src/img_src/block1x1_3_142x142.png",
        "src/img_src/block1x1_4_142x142.png",
        "src/img_src/block1x1_5_142x142.png",
        "src/img_src/block1x1_6_142x142.png",
        "src/img_src/block1x1_7_142x142.png"
    };

    path_imgs[1][0] = {
        "src/img_src/block2x1_1_92x185.png",
        "src/img_src/block2x1_2_142x286.png"
    };

    path_imgs[0][1] = {
        "src/img_src/block1x2_1_286x142.png",
        "src/img_src/block1x2_2_286x142.png"
    };
}

bool Func::inRange(int x, int a, int b){
    int min = a < b ? a : b;
    x = x - min; 
    return ( x > 0 && x < abs(b - a) );
}

bool Func::inRange(int x, int y,  int a, int b){
    int min = a < b ? a : b;
    x = x - min;
    y = y - min; 
    return ( x >= 0 && x <= abs(b - a) ) && ( y >= 0 && y <= abs(b - a) );
}

bool Func::avaiIndex(int i, int r,  int j, int c){
    return i >= 0 && i < r && j >= 0 && j < c;
}

Func::Vector* Func::randUnion(int r, int c){
    static UnitVec unitVec;
    int table[r][c];
    int ra;
    int count_activeBlock = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            table[i][j] = 1;
        }
    }
    
    std::vector<Vector> list;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(!table[i][j]){
                continue;
            }
            table[i][j] = 0;
            Vector point(i, j);
            ra = rand() % 8;  
            Vector nextPoint(point.x + unitVec[ra].x, point.y + unitVec[ra].y);
            if(avaiIndex(nextPoint.x, r, nextPoint.y , c) && table[nextPoint.x][nextPoint.y] == 1){
                
                list.push_back(point);
                list.push_back(nextPoint);
                table[nextPoint.x][nextPoint.y] = 0;
            } else {
                count_activeBlock++;
                list.push_back(point);
                list.push_back(point);
            }

        }
    }

    int len_list = list.size();
    Vector* init_arr = new Vector[len_list + 1];
    init_arr[0] = Vector(len_list + 1, count_activeBlock);
    for(int i = 1; i < len_list + 1; i++){
        init_arr[i] = list[i - 1];
    }

    return init_arr;
}

void Func::randnNum(int n,std::vector<int>& id){
    int len = id.size();
    int tmp;
    for(int i = 0; i < n && i < len; i++){
        tmp = rand() % len;
        if(id[i]){
            id[tmp] = 0;
        } else {
            i--;
        }
    }
}

void Func::parseToTexture(SDL_Texture* dsTexture,const SDL_Rect & dsRect, SDL_Texture* srcTexture, const SDL_Rect &srcRect){
    int access, w, h;
    Uint32 format;
    SDL_QueryTexture(dsTexture, &format, &access, &w, &h);
    if(access != SDL_TEXTUREACCESS_TARGET){
        
    }
}
