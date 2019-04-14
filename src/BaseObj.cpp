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

OBJTYPE BaseObj::type() const{
    return OBJTYPE::BASEOBJ;
}

const char* BaseObj::name() const{
    return "BaseObj";
}


//Method with vector<MyTexture> ver 0.6.1
void BaseObj::addMyTexture(){
    Func::MyTexture tmp = Func::MyTexture();
    arr_texture.push_back(tmp);
}

void BaseObj::setRect(int x, int y, int w, int h, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect = {x, y, w, h};
    }
}

void BaseObj::setRect(const SDL_Rect &rect, unsigned int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect = rect;
    } else {
        Func::log("Out of index arr_texture when setRect", this);
    }
}

void BaseObj::setTexture(SDL_Texture* texture, unsigned int id, bool destroy){
    if(arr_texture.size() > id){
        if(destroy && arr_texture[id].texture != NULL && arr_texture[id].texture != texture){
            SDL_DestroyTexture(arr_texture[id].texture);
            arr_texture[id].texture = NULL;
        }
        arr_texture[id].texture = texture;
    } else {
        Func::log("Out of index arr_texture when setTexture", this);
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
    } else {
        Func::log("Out of index arr_texture when getRect", this);
    }
    return {0,0,0,0};
}

SDL_Texture* BaseObj::getTexture(unsigned int id){
    if(arr_texture.size() > id){
        return arr_texture[id].texture;
    } else {
        Func::log("Out of index arr_texture when getTexture", this);
    }
    return NULL;
}

Func::MyTexture* BaseObj::getMyTexture(unsigned int id){
    if(arr_texture.size() > id){
        return &arr_texture[id];
    } else {
        Func::log("Out of index arr_texture when getMyTexture", this);
    }
    return NULL;
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

void BaseObj::ShowAll(){
    Func::log("_____________");
    for(int i = 0; i < arr_texture.size(); i++){
        if(arr_texture[i].texture != NULL)
            Show(i);
    }
}

void BaseObj::ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip,unsigned int id){
    if(arr_texture.size() > id){
        SDL_RenderCopyEx(gRenderer, arr_texture[id].texture, NULL, &arr_texture[id].rect, angle, center, flip);
    }
}

