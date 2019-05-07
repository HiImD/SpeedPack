#include "BaseObj.h"
#include <iostream>

BaseObj::BaseObj(){
    p_rect = NULL;   
    p_texture = NULL;
}

BaseObj::~BaseObj(){
    if(p_texture != NULL){
        SDL_DestroyTexture(p_texture);
        p_texture = NULL;
    }
    if(p_rect != NULL){
        delete p_rect;
        p_rect = NULL;
    }
}

void BaseObj::setRect(int x, int y, int w, int h){
    if(p_rect == NULL){
        p_rect = new SDL_Rect();
    }
    p_rect->x = x;
    p_rect->y = y;
    p_rect->w = w;
    p_rect->h = h;
}

void BaseObj::setRect(SDL_Rect* rect){
    p_rect = rect;
}

void BaseObj::setPos(int x, int y){
    if(p_rect == NULL){
        p_rect = new SDL_Rect();
    }
    p_rect->x = x;
    p_rect->y = y;
}

void BaseObj::setWH(int w, int h){
    if(p_rect == NULL){
        p_rect = new SDL_Rect();
    }
    p_rect->w = w;
    p_rect->h = h;
}


SDL_Rect* BaseObj::getRect(){
    return p_rect;
}

int BaseObj::getX(){
    if(p_rect != NULL)
        return p_rect->x;
    return -1;
}

int BaseObj::getY(){
    if(p_rect != NULL)
        return p_rect->y;
    return -1;
}

int BaseObj::getH(){
    return p_rect->h;
}

int BaseObj::getW(){
    return p_rect->w;
}

void BaseObj::loadImg(std::string path){
    p_texture = Func::loadImg(path);
}

void BaseObj::Show(){
    SDL_RenderCopy(gRenderer, p_texture, NULL, p_rect);
}

void BaseObj::ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_RenderCopyEx(gRenderer, p_texture, NULL, p_rect, angle, center, flip);
}


