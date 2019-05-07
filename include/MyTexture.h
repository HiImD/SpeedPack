/*
	Về Class MyTexture:
		- Là một lớp bao gói SDL_Texture với dsRect của nó và các hàm chức năng
		- Thay thế cho SDL_Texture
*/
#ifndef MYTEXTURE_H_
#define MYTEXTURE_H_

#include "Func.h"
#include "MyObj.h"


class MyTexture: public MyObj {
private:
	SDL_Texture* mTexture = nullptr; //Texture
	SDL_Rect* mRect = nullptr;		//dsRect
	SDL_Renderer* mRenderer = nullptr;//Renderer gắn với MyTexture
	SDL_Texture* defaultRenderTarget = nullptr; //Đích render của MyTexture
protected:

public:
	MyTexture(SDL_Renderer* renderer, SDL_Texture* defaultRenderTarget = nullptr);
	
	//comtrucstor khong tham so chi duoc dung khi cap phat mang bo nho dong
	//Phai su dung init neu khoi tao bang constructor khong tham so
	MyTexture();

	//Ham khoi tao khong tuong minh
	void init(SDL_Renderer* renderer, SDL_Texture* defaultRenderTarget = nullptr);
	
	~MyTexture();

	virtual OBJTYPE type() const;
	virtual const char* toString() const;
	
	void free();  //Ham giai phong mTexture
	bool loadImg(std::string img_path); //Ham load anh tu file theo duong dan
	//Ham cai thong so cho mRect
	void setRect(int x, int y, int w, int h); 
	//
	void setRect(SDL_Rect* rect, bool deleted = true); 
	//Hàm thay đổi mTexture, nếu destroy == true free mTexture trước khi đổi
	void setTexture(SDL_Texture* texture, bool destroy = true);
	//Trả về con trỏ của dsRect
	SDL_Rect* getRectPointer();
	//Trả về mTexture
	SDL_Texture* getTexture();
	//Trả về mRenderer
	SDL_Renderer* getRenderer();
	
	//Cac ham xu li voi Texture
	SDL_Texture* createTransparentTexture(Uint32 format, int w, int h, bool replace = true, SDL_Color color = {0, 0, 0, 0});
	bool convertToTarget();
	bool parseTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dsRect, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Các hàm render texture đến defaultRendererTarget
	void render(SDL_Renderer* renderer = nullptr,  const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Render(const SDL_Rect* srcRect = nullptr,SDL_Renderer* renderer = nullptr, const double& angle = 0,const SDL_Point* center = nullptr,const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void RenderWithDesRect(SDL_Rect* dsRect, SDL_Rect* srcRect = nullptr, SDL_Renderer* renderer = nullptr, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(SDL_Rect* dsRect, SDL_Renderer* renderer = nullptr, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void RenderPartOfTexture(SDL_Rect* srcRect, SDL_Renderer* renderer = nullptr, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Cac ham xu li voi Rect
	

	//Cac ham xu li text
	bool RenderTextSolid(std::string text, SDL_Color fg, bool resize = false, bool destroy = true, TTF_Font* font = gFont);
	bool RenderTextShaded(std::string text, SDL_Color fg, SDL_Color bg, bool resize = false, bool destroy = true, TTF_Font* font = gFont);
	bool RenderTextBlended(std::string text, SDL_Color fg, bool resize = false, bool destroy = true, TTF_Font* font = gFont);

	//Animate
	void Slide(const int& vel_x, const int& vel_y);
};

#endif // !MYTEXTURE_H_

