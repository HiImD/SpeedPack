#ifndef BASEOBJ
#define BASEOBJ

#include "gVar.h"
#include "Func.h"
#include <vector>

class BaseObj{
protected:
    std::vector<Func::MyTexture> arr_texture;
public:
    BaseObj();
    ~BaseObj();

    //Defaul method ver 0.2.1
    // void setRect(int x, int y, int w, int h);
    // void setRect(const SDL_Rect &rect);
    // void setPos(int x, int y);
    // void setWH(int w, int h);
    // SDL_Rect getRect();
    // int getX();
    // int getY();
    // int getW();
    // int getH();
    // void loadImg(std::string path);
    // void Show();
    // void ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip);

    //Method with vector<MyTexture> ver 0.6.1
    void setRect(int x, int y, int w, int h, unsigned int id = 0);
    void setRect(const SDL_Rect &rect, unsigned int id = 0);
    void setPos(int x, int y, unsigned int id = 0);
    void setWH(int w, int h, unsigned int id = 0);
    SDL_Rect getRect(unsigned int id = 0);
    int getX(unsigned int id = 0);
    int getY(unsigned int id = 0);
    int getW(unsigned int id = 0);
    int getH(unsigned int id = 0);
    void loadImg(std::string path , unsigned int id = 0);
    void Show(unsigned int id = 0);
    void ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip, unsigned int id = 0);
};

#endif