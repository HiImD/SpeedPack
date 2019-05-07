/*
	Về Class MyTimer:
		- Kế thừa MyTexture
		- Tạo một đồng hồ đếm ngược, có thể Pause, Resume, hiển thị đồng hồ lên màn hình
*/
#pragma once
#include "MyTexture.h"
#include <sstream>
#include <iomanip>

class MyTimer: public MyTexture{
private:
protected:
	Uint32 minute = 0, second = 0, last_time = 0, time_remain = 0, pause_time = 0;
	std::string time_str;
	bool update = false, counting = false;
	std::stringstream ss;
	bool timeout = false, pause = false;

	void UpdateStringStream(const Uint32& range_time);
public:
	
	MyTimer(SDL_Renderer* mRenderer, SDL_Texture* default_render_tezture);
	~MyTimer();

	//Bắt đầu đếm ngược với khoảng thời gian range_time
	void StartCount(const Uint32& range_time);
	//Tạm dừng hoặc tiếp tục
	void Pause_Resume();
	//Kiểm tra hiện đồng hồ có tạm dừng ?
	bool IsPausing();
	//Kiểm tra hết giờ
	bool CheckTimeOut();

	//Overide Render của MyTexture
	//Hiển thị đồng hồ
	void Render(SDL_Rect* srcRect = nullptr, SDL_Renderer* renderer = nullptr, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	//Hàm không nên sử dụng
	void RenderWithDesRect(SDL_Rect* dsRect, SDL_Rect* srcRect= nullptr, SDL_Renderer* renderer = nullptr, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
};