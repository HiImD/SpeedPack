#include "TheCamera.h"

TheCamera::TheCamera(SDL_Renderer* mRenderer, SDL_Texture* default_render_texture) :Block(mRenderer, default_render_texture) {
	MyPos.set(-1, -1);
	loadImg(IMGPATH::BLOCK::CAMERA);
	is_running = false;
}

TheCamera::TheCamera(const int& x0, const int& y0, const int& i, const int& j,SDL_Renderer* mRenderer, SDL_Texture* default_render_texture):Block(mRenderer, default_render_texture),O(x0, y0), MyPos(-1, -1) {
	SlideTo(i, j);
	setRect(MyPos.x, MyPos.y, 92, 92);
	loadImg(IMGPATH::BLOCK::CAMERA);
	is_running = false;
}
TheCamera::~TheCamera() {

}

void TheCamera::init(const int& x0, const int& y0, const int& i, const int& j) {
	SlideTo(i, j);
	setRect(MyPos.x, MyPos.y, 92, 92);
}
void TheCamera::setOPos(const int& xO, const int& yO) {
	O.set(xO, yO);
}

bool TheCamera::SlideTo(const int& i,const int& j) {
	MyPos.set(j * (SIZE::BLOCK::UNIT_SIZE + 1), i * (SIZE::BLOCK::UNIT_SIZE + 1));
	MyPos = MyPos + O;
	if (MyPos.x == getRectPointer()->x && MyPos.y == getRectPointer()->y) {
		is_running = false;
	}
	else {
		is_running = true;
	}
	return is_running;
}

void TheCamera::render(SDL_Renderer* renderer, const double& angle,const SDL_Point* center,const SDL_RendererFlip& flip) {
	
	if (MyPos.x != -1)
	{
		if (MyPos.x == getRectPointer()->x && MyPos.y == getRectPointer()->y)
			is_running = false;
		else
			is_running = true;
		if (is_running)
		{
			SDL_Rect* mRect = getRectPointer();
			if (abs(MyPos.x - mRect->x) >= vel) {
				Slide(vel * abs(MyPos.x - mRect->x) / (MyPos.x - mRect->x), 0);
			}
			else if (abs(mRect->x - MyPos.x) < vel) {
				Slide((MyPos.x - mRect->x), 0);
			}
			if (abs(MyPos.y - mRect->y) >= vel) {
				Slide(0, vel * abs(MyPos.y - mRect->y) / (MyPos.y - mRect->y));
			}
			else if (abs(mRect->y - MyPos.y) < vel) {
				Slide(0, (MyPos.y - mRect->y));
			}
		}
	}
	MyTexture::Render(nullptr,renderer, angle, center, flip);
}

void TheCamera::ShowAnswer(const bool& answer) {
	if (answer) {
		loadImg(IMGPATH::ANSWER::RIGHT);
	}
	else {
		loadImg(IMGPATH::ANSWER::WRONG);
	}
}

bool TheCamera::IsRunning() {
	return is_running;
}