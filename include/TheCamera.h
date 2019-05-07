/*
	TheCamera: Tuong trung cho cau tra loi nguoi choi lua chon
	Slide giua cac PickableBlock
*/

#pragma once
#include "Block.h"

class TheCamera: public Block {
private:
	int vel = 10;
	Func::Vector MyPos;
	Func::Vector O;
	bool is_running;
protected:
public:
	TheCamera(SDL_Renderer* mRenderer, SDL_Texture* default_render_texture);
	TheCamera(const int& x0, const int& y0, const int& i,const int& j, SDL_Renderer* mRenderer, SDL_Texture* default_render_texture);
	~TheCamera();
	
	void init(const int& x0, const int& y0, const int& i, const int& j);
	//Set vị trí gốc tọa độ trong hệ quy chiếu của camera
	void setOPos(const int& xO, const int& yO);
	//Slide đến ô (i, j)
	bool SlideTo(const int& i, const int& j);
	//Overide MyTexture::render
	void render(SDL_Renderer* renderer = nullptr, const double& angle = 0, const SDL_Point* center = nullptr,const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	//Hiển thị đáp án
	void ShowAnswer(const bool& answer);
	//Đang Slide ?
	bool IsRunning();
};