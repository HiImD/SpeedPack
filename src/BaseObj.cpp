#include "BaseObj.h"
#include <iostream>

BaseObj::BaseObj(){
    arr_texture = std::vector<Func::MyTexture>(1, Func::MyTexture()); //Co that thoat bo nho?
}

BaseObj::~BaseObj(){
    for(Func::MyTexture t: arr_texture ){
        if(t.texture != NULL){
            SDL_DestroyTexture(t.texture);
            t.texture = NULL;
        }
    }
}

/*Defaul method ver 0.2.1
void BaseObj::setRect(int x, int y, int w, int h){
    if(arr_texture.size()){
        arr_texture[0].rect = {x, y, w, h};
    }
}

void BaseObj::setRect(const SDL_Rect &rect){
    if(arr_texture.size()){
        arr_texture[0].rect = rect;
    }
}

void BaseObj::setPos(int x, int y){
    if(arr_texture.size()){
        arr_texture[0].rect.x = x;
        arr_texture[0].rect.y = y;
    }
}

void BaseObj::setWH(int w, int h){
    if(arr_texture.size()){
        arr_texture[0].rect.w = w;
        arr_texture[0].rect.h = h;
    }
}

SDL_Rect BaseObj::getRect(){
    if(arr_texture.size()){
        return arr_texture[0].rect;
    }
    return {0,0,0,0};
}

int BaseObj::getX(){
    if(arr_texture.size()){
        return arr_texture[0].rect.x;
    }
    return -1;
}

int BaseObj::getY(){
    if(arr_texture.size()){
        return arr_texture[0].rect.y;
    }
    return -1;
}

int BaseObj::getH(){
    if(arr_texture.size()){
        return arr_texture[0].rect.h;
    }
    return -1;
}

int BaseObj::getW(){
    if(arr_texture.size()){
        return arr_texture[0].rect.w;
    }
    return -1;
}

void BaseObj::loadImg(std::string path){
    if(arr_texture.size()){
        arr_texture[0].texture = Func::loadImg(path);
    }
}

void BaseObj::Show(){
    if(arr_texture.size()){
        SDL_RenderCopy(gRenderer, arr_texture[0].texture, NULL, &arr_texture[0].rect);
    }
}

void BaseObj::ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip){
    if(arr_texture.size()){
        SDL_RenderCopyEx(gRenderer, arr_texture[0].texture, NULL, &arr_texture[0].rect, angle, center, flip);
    }
}
*/
//Method with vector<MyTexture> ver 0.6.1
void BaseObj::setRect(int x, int y, int w, int h, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect = {x, y, w, h};
    }
}

void BaseObj::setRect(const SDL_Rect &rect, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect = rect;
    }
}

void BaseObj::setPos(int x, int y, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect.x = x;
        arr_texture[id].rect.y = y;
    }
}

void BaseObj::setWH(int w, int h, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect.w = w;
        arr_texture[id].rect.h = h;
    }
}

SDL_Rect BaseObj::getRect(unsigned int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect;
    }
    return {0,0,0,0};
}

int BaseObj::getX(unsigned int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.x;
    }
    return -1;
}

int BaseObj::getY(unsigned int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.y;
    }
    return -1;
}

int BaseObj::getH(unsigned int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.h;
    }
    return -1;
}

int BaseObj::getW(unsigned int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.w;
    }
    return -1;
}

void BaseObj::loadImg(std::string path, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].texture = Func::loadImg(path);
    }
}

void BaseObj::Show(unsigned int id){
    if(arr_texture.size() > id){
        SDL_RenderCopy(gRenderer, arr_texture[id].texture, NULL, &arr_texture[id].rect);
    }
}

void BaseObj::ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip,unsigned int id){
    if(arr_texture.size() > id){
        SDL_RenderCopyEx(gRenderer, arr_texture[id].texture, NULL, &arr_texture[id].rect, angle, center, flip);
    }
}

