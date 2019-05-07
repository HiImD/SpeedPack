#pragma once
#include "MyTimer.h"
#include "Component.h"

class TimerComponent: public Component, public MyTimer {
private:
protected:
public:
	TimerComponent(const int& w, const int& h);
	~TimerComponent();
	void Show(SDL_Rect* srcRect = NULL, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

};