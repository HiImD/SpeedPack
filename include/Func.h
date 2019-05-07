

#ifndef FUNC_H_
#define FUNC_H_

/*
	Về Func.h:
		- Chứa các hàm cơ bản như init, close, ...
		- Một số hàm không còn được sử dụng do đã tích hợp vào MyTexture
*/


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
	SDL_Texture* loadFromRenderText(std::string textureText, SDL_Color textColor);
    //void log(std::string mgs ,bool error = false , std::ostream &os = std::cout);
    
	//Các hàm chức năng
    bool inRange(int x, int a, int b);
	bool inRect(int x, int y, SDL_Rect* rect);
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

	//Ham sinh ngau nhien vi tri cac block trong pack
	//Tra ve vector kich thuoc RxC + 1x2 trong do:
	// RxC la bảng cùng kích thước với pack chứa thông tin về các block nằm trên đó
	// 1x2 chua thong tin [so FixedBlock][]
    std::vector< std::vector<int>> randUnion(int r, int c);
    //Tạo một texture trong suốt
	SDL_Texture* creatTransparentTexture(const Uint32 &format,const int &w,const int &h);
    //Thay đổi access của texture thành Target
	SDL_Texture* convertTextureToTarget(SDL_Texture* texture, SDL_Rect* rect = NULL, bool destroy = true);
    
	//Dán 1 texture lên một texture
    void parseToTexture(SDL_Texture* dsTexture,const SDL_Rect *dsRect, SDL_Texture* srcTexture, const SDL_Rect *srcRect);
    void parseToTextureEx(SDL_Texture* dsTexture,const SDL_Rect*  dsRect, SDL_Texture* srcTexture, const SDL_Rect* srcRect, const double angle, const SDL_Point* center,const SDL_RendererFlip flip);
    
    
    //Thay đổi kích thước của Texture
    SDL_Texture* resizeTexture(SDL_Texture* origin, int w, int h, bool destroy = true);
    //Thay đổi kích thước của texture thành hình thang
	SDL_Texture* resizeTextureWithTrapeZoidShape(SDL_Texture* origin,const int& len,const int& direct,int orient,const bool& destroy = false);
    

}


#else


#endif