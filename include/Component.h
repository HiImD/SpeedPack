/*
	Về Class Component: 
		- Là lớp có Renderer (logic) và Texture riêng - pTexture , có thể render 1 hay nhiều texture lên pTexture của nó.
		- Có thể dùng để gói một nhóm các đối tượng có liên quan đến nhau.
		- Sử dụng các hàm tạo animation.
*/

#pragma once
#include "MyObj.h"
#include "MyTexture.h"

class Component: public MyObj {
private:
	
protected:
	MyTexture* pTexture = nullptr;
	SDL_Renderer* mRenderer = nullptr;
	SDL_Color bgColor; // Background Color
public:
	Component(SDL_Color bgColor = { 0, 0, 0, 0 }); //Hàm khởi tạo không tạo mới một Texture
	Component(const int& w, const int& h, SDL_Color bgColor = {0, 0, 0, 0}); //Hàm khởi tạo tạo mới một Texture có kích thước theo w và h
	~Component();

	//Overide MyObj.h
	virtual OBJTYPE type() const;
	virtual const char* toString() const;
	
	//Các hàm Set và Get kích thước
	void SetComponentSize(const int& w, const int& h, bool resizeTexture = false);
	void GetComponentSize(int& w, int& h);
	int GetComponentWSize();
	int GetComponentHSize();
	void SetComponentPos(const int& x,const int& y);
	void GetComponentPos(int& x, int& y);
	int GetComponentXPos();
	int GetComponentYPos();

	//Set và Get Background color
	void setBGColor(const SDL_Color& color);
	SDL_Color getBGColor();

	//Các hàm render
	void ClearComponent(); //Fill pTexture với màu là BgColor
	void RenderToComponent(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dsRect, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE); //Dán một Texture vào pTexture
	void Show(SDL_Rect* srcRect = NULL, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE); //Render Component lên màn hình


	//Các hàm tạo animation slide
	void Slide(const int& vel_x, const int& vel_y); // Slide với vận tốc (vel_x, vel_y)
	bool SlideOut(const int& vel_x, const int& vel_y); //Slide ra khỏi màn hình, trả về true nếu đã thoát khỏi màn hình, false nếu ngược lại
	bool SlideTo(const int& x, const int& y, const int& vel_x, const int& vel_y); // trả về true nếu đang ở (x, y), false nếu ngược lại
};
