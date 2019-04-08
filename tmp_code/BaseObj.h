#ifndef BASEOBJ
#define BASEOBJ

#include "gVar.h"
#include "Func.h"
#include <vector>

class BaseObj{
protected:
    SDL_Rect* p_rect;
    SDL_Texture* p_texture;

public:
    BaseObj();
    ~BaseObj();
    void setRect(int x, int y, int w, int h);
    void setRect(SDL_Rect* rect);
    void setPos(int x, int y);
    void setWH(int w, int h);
    SDL_Rect* getRect();
    int getX();
    int getY();
    int getW();
    int getH();
    void loadImg(std::string path);
    void Show();
    void ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip);

};

#endif