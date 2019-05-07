#include "MyTimer.h"

MyTimer::MyTimer(SDL_Renderer* mRenderer, SDL_Texture* default_render_tezture): MyTexture(mRenderer, default_render_tezture), time_str() {
	
}

MyTimer::~MyTimer() {

}

// PROTECTED
void MyTimer::UpdateStringStream(const Uint32& range_time) {
	time_str = "TIME   ";
	minute = range_time  / 1000 / 60;
	second = range_time  / 1000 % 60;
	if (minute < 10) {
		time_str += std::string("0") + std::to_string(minute);
	}
	else {
		time_str += std::to_string(minute);
	}
	time_str += ":";
	if (second < 10) {
		time_str += std::string("0") + std::to_string(second);
	}
	else {
		time_str += std::to_string(second);
	}
}

// PUBLIC
void MyTimer::StartCount(const Uint32& range_time) {
	if (range_time <= 0) {
		SDL_Log("Invalid range_time");
	}
	else {
		time_remain = range_time * 1000;
		UpdateStringStream(time_remain);
		counting = true;
		update = true;
		timeout = false;
		pause = false;
		last_time = SDL_GetTicks();
	}
}

void MyTimer::Pause_Resume() {
	pause = !pause;
	if (pause) {
		SDL_Log("Time pause");
		counting = false;
		last_time = SDL_GetTicks() - last_time;
	}
	else {
		SDL_Log("Time resume");
		counting = true;
		last_time = SDL_GetTicks() - last_time;
	}

}

bool MyTimer::IsPausing() {
	return pause;
}

bool MyTimer::CheckTimeOut() {
	if (time_remain == 0) {
		return true;
	}
	if (timeout)
		return timeout;
	if (counting && (SDL_GetTicks() - last_time) > time_remain) {
		time_remain = 0;
		counting = false;
		return true;
	}
	return false;
}


void MyTimer::Render(SDL_Rect* srcRect, SDL_Renderer* renderer, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	if (SDL_GetTicks() - last_time >= 980  && counting ) {
		if (time_remain < SDL_GetTicks() - last_time) {
			time_remain = 0;
			counting = false;
			timeout = true;
		}
		else {
			Uint32 delta = SDL_GetTicks() - last_time;
			SDL_Log(std::to_string(time_remain).c_str());
			if ((time_remain - delta) % 1000 < 50) {
				time_remain -= delta;
				last_time = SDL_GetTicks();
				UpdateStringStream(time_remain);
				update = true;
			}
			
		}
		
	}

	if (update) {
		if (time_remain < 5000)
			RenderTextShaded(time_str, { 255, 100, 100 }, { 27, 27, 38 }, true);
		else
			RenderTextShaded(time_str, { 64, 54, 46 }, { 217, 142, 149, 150 }, true);

		update = false;
	}

	MyTexture::Render( srcRect, renderer, angle, center, flip);
}

void MyTimer::RenderWithDesRect(SDL_Rect* dsRect, SDL_Rect* srcRect,  SDL_Renderer* renderer, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	if (SDL_GetTicks() - last_time >= 1000 && counting) {
		time_remain -= SDL_GetTicks() - last_time;
		last_time = SDL_GetTicks();
		UpdateStringStream(time_remain);
		update = true;
	}

	if (update) {
		if (time_remain < 6000)
			RenderTextShaded(time_str, { 255, 100, 100 }, { 27, 27, 38 });
		else
			RenderTextShaded(time_str, { 64, 54, 46 }, { 217, 142, 149, 150 });
		if (getRectPointer() != nullptr)
		{
			int w, h;
			TTF_SizeText(gFont, ss.str().c_str(), &w, &h);
			getRectPointer()->w = w;
			getRectPointer()->h = h;
		}
		update = false;
	}

	MyTexture::RenderWithDesRect(dsRect, srcRect, renderer, angle, center, flip);
	if (time_remain <= 0) {
		counting = false;
		timeout = true;
		return;
	}
}
	
	