#include "TimerComponent.h"

TimerComponent::TimerComponent(const int& w, const int& h) :Component(w, h), MyTimer(Component::mRenderer, pTexture->getTexture()) {
	setBGColor({ 255, 100, 100, 150 });
}

TimerComponent::~TimerComponent() {

}

void TimerComponent::Show(SDL_Rect* srcRect, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	ClearComponent();
	pTexture->getRectPointer()->h = MyTimer::getRectPointer()->h;
	pTexture->getRectPointer()->w = MyTimer::getRectPointer()->w;
	MyTimer::Render(nullptr);
	Component::Show(srcRect, angle, center, flip);
}

