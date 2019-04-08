#ifndef FUNC
#define FUNC

#ifndef GVAR
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

    void log(std::string mgs);
    void ImgsData();

    bool inRange(int x, int a, int b);
    bool inRange(int x, int y, int a, int b);
    bool avaiIndex(int i, int r, int j, int c);
    

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

        void operator+(const Vector& other){
            set(x + other.x, y + other.y);
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
                case 0:
                    return up;
                case 1:
                    return down;
                case 2:
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
    };

    Vector* randUnion(int r, int c);
    void randnNum(int n, std::vector<int>& id);
    void parseToTexture(SDL_Texture* dsTexture,const SDL_Rect & dsRect, SDL_Texture* srcTexture, const SDL_Rect &srcRect);
}
#else
#endif