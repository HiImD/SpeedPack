#ifndef FUNC_H_
#define FUNC_H_

#ifndef GVAR_H_
#include "gVar.h"
#endif

#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>

namespace Func{
    
    bool init();
    void Close();
    SDL_Texture* loadImg(std::string path);

    //void log(std::string mgs ,bool error = false , std::ostream &os = std::cout);
    


    bool inRange(int x, int a, int b);
    bool inRange(int x, int y, int a, int b);
    bool avaiIndex(int i, int r, int j, int c);
    void log(std::string mgs,void* from = NULL, bool error = false, std::ostream &os = std::cout);

    struct Vector{
        int x;
        int y;
        Vector(){
            x = 0;
            y = 0;
        }

        void set(int x, int y){
            this->x = x;
            this->y = y;
        }

        Vector(int x, int y){
            set(x, y);
        }

        ~Vector(){}
        
        void operator=(const Vector& other){
            set(other.x, other.y);
        }

        Vector operator+(const Vector& other){
            return Vector(x + other.x, y + other.y);
        }

        Vector operator-(const Vector& other){
            return Vector(x - other.x, y - other.y);
        }

        std::string toString(){
            std::stringstream ss;
            ss << "(" << x << " " << y << ")";
            return ss.str();
        }
    };

    struct UnitVec{
        Vector up;
        Vector down;
        Vector left;
        Vector right;
        Vector zero;
        UnitVec(){
            up.set(0,1);
            down.set(0,-1);
            left.set(-1,0);
            right.set(1,0);
            zero.set(0,0);
        }
        
        Vector& operator[] (int x){
            switch (x)
            {
                case 2:
                    return up;
                case 0:
                    return down;
                case 1:
                    return left;
                case 3:
                    return right;
                default:
                    return zero;
            }
        }

    };

    struct MyTexture{
        SDL_Texture* texture;
        SDL_Rect rect;

        MyTexture(){
            texture = NULL;
            rect = {0,0,0,0};
        }
        ~MyTexture(){
            if(texture != NULL){
                Func::log("Destroying Texture");
                SDL_DestroyTexture(texture);
                texture = NULL;
            }
        }
    };

    std::vector< std::vector<int>> randUnion(int r, int c);
    void randnNum(int n, std::vector<int>& id);
    SDL_Texture* creatTransparentTexture(Uint32 format, int w, int h);
    SDL_Texture* convertTextureToTarget(SDL_Texture* texture, SDL_Rect* rect = NULL, bool destroy = true);
    
    SDL_Texture* parseToTexture(MyTexture* dsTexture,const SDL_Rect *dsRect, SDL_Texture* srcTexture, const SDL_Rect *srcRect);
    SDL_Texture* parseToTextureEx(MyTexture* dsTexture,const SDL_Rect*  dsRect, SDL_Texture* srcTexture, const SDL_Rect* srcRect, const double angle, const SDL_Point* center,const SDL_RendererFlip flip);
    
    
    
    SDL_Texture* resizeTexture(SDL_Texture* origin, int w, int h, bool destroy = true);
    SDL_Texture* resizeTextureWithTrapeZoidShape(SDL_Texture* origin, int len, int direct,int orient, bool destroy = false);
    

}


#else


#endif