/*
	Về Class BackGround:
		- Chứa texture và rect dùng cho Background
		- Có thể span bằng cách lặp các texture nếu kích thước của texture nhỏ hơn kích thước window
*/
#ifndef BACKGROUND
#define BACKGROUND

#include "Func.h"

class BackGround{
private:
    SDL_Rect bg_rect;
    SDL_Texture* bg_texture;
public:
	BackGround() {
		bg_texture = nullptr;
	}

    BackGround(std::string bg_img_path){
        bg_texture = Func::loadImg(bg_img_path);
    }

	void LoadBackgroundImg(std::string bg_img_path) {
		bg_texture = Func::loadImg(bg_img_path);
	}

    void render(){
        int w_img, h_img;
        if((SDL_QueryTexture(bg_texture, NULL, NULL,&w_img ,&h_img ))){
            SDL_Log("From BackGround.h: w: %d h: %d %s",w_img, h_img, SDL_GetError());
            SDL_Log("%d", SDL_QueryTexture(bg_texture, NULL, NULL,&w_img ,&h_img ));
        } else {
            for(int i = 0; i < SCREEN_WIDTH; i += w_img){
                for(int j = 0; j < SCREEN_HEIGHT;j += h_img){
                    SDL_Rect tmp{i, j , w_img, h_img};
                    SDL_RenderCopy(gRenderer, bg_texture, NULL, &tmp);
                }
            }
        }
    }

};

#else
#endif