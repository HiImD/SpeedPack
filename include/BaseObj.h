#ifndef BASEOBJ_H_
#define BASEOBJ_H_

#include "gVar.h"
#include "Func.h"
#include <vector>

class BaseObj{
protected:
    std::vector<Func::MyTexture> arr_texture;
public:
    BaseObj();
    ~BaseObj();
    
    virtual OBJTYPE type() const;
    virtual const char* name() const;

    //Method with vector<MyTexture> ver 0.6.1
    void addMyTexture();
    void setRect(int x, int y, int w, int h, unsigned int id = 0);
    void setRect(const SDL_Rect &rect, unsigned int id = 0);
    void setTexture(SDL_Texture* texture, unsigned int id = 0, bool destroy = false);
    void setPos(int x, int y, unsigned int id = 0);
    void setWH(int w, int h, unsigned int id = 0);
    SDL_Rect getRect(unsigned int id = 0);
    SDL_Texture* getTexture(unsigned int id = 0);
    Func::MyTexture* getMyTexture(unsigned int id = 0);
    int getX(unsigned int id = 0);
    int getY(unsigned int id = 0);
    int getW(unsigned int id = 0);
    int getH(unsigned int id = 0);
    void loadImg(std::string path , unsigned int id = 0);
    void Show(unsigned int id = 0);
    void ShowAll();
    void ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip, unsigned int id = 0);

};

#endif