#include "Component.h"

Component::Component(SDL_Color color) {
	bgColor = color;
	mRenderer = gRenderer;
	if (mRenderer == nullptr) {
		SDL_Log("Fail to create mRenderer");
		SDL_Log(SDL_GetError());
	}
	pTexture = new MyTexture(mRenderer);
}

Component::Component(const int& w,const int& h, SDL_Color color) {
	bgColor = color;
	mRenderer = gRenderer;
	if (mRenderer == nullptr) {
		SDL_Log("Fail to create mRenderer");
		SDL_Log(SDL_GetError());
	}
	pTexture = new MyTexture(mRenderer);
	pTexture->createTransparentTexture(SDL_PIXELFORMAT_ABGR8888, w, h, true, color);
	pTexture->setRect(0, 0, w, h);
	SDL_SetRenderTarget(mRenderer, pTexture->getTexture());
}

Component::~Component() {
	if (pTexture != nullptr) {
		delete pTexture;
		pTexture = nullptr;
	}
	if (mRenderer != nullptr && mRenderer != gRenderer) {
		SDL_DestroyRenderer(mRenderer);
	}
}

OBJTYPE Component::type() const {
	return OBJTYPE::COMPONENT;
}

const char* Component::toString() const {
	return "Component";
}

void Component::SetComponentSize(const int& w, const int& h, bool resizeTexture) {
	pTexture->getRectPointer()->w = w;
	pTexture->getRectPointer()->h = h;
	if (!pTexture->getTexture()) {
		pTexture->createTransparentTexture(SDL_PIXELFORMAT_ABGR8888, w, h, true, bgColor);
		return;
	}
	if (resizeTexture) {
		int wTexture, hTexture;
		SDL_QueryTexture(pTexture->getTexture(), nullptr, nullptr, &wTexture, &hTexture);
		if(wTexture != w || hTexture != h)
			pTexture->createTransparentTexture(SDL_PIXELFORMAT_ABGR8888, w, h, true, bgColor);
	}
}

void Component::GetComponentSize(int& w, int& h) {
	w = pTexture->getRectPointer()->w;
	h = pTexture->getRectPointer()->h;
}

int Component::GetComponentWSize() {
	return pTexture->getRectPointer()->w;
}

int Component::GetComponentHSize() {
	return pTexture->getRectPointer()->h;
}


void Component::SetComponentPos(const int& x,const int& y) {
	pTexture->getRectPointer()->x = x;
	pTexture->getRectPointer()->y = y;
}

void Component::GetComponentPos(int& x, int& y) {
	x = pTexture->getRectPointer()->x;
	y = pTexture->getRectPointer()->y;
}

int Component::GetComponentXPos() {
	return pTexture->getRectPointer()->x;
}

int Component::GetComponentYPos() {
	return pTexture->getRectPointer()->y;
}

//Background Color
void Component::setBGColor(const SDL_Color& color) {
	bgColor = color;
}

SDL_Color Component::getBGColor() {
	return bgColor;
}

void Component::ClearComponent() {
	SDL_SetRenderTarget(mRenderer, pTexture->getTexture());
	SDL_SetRenderDrawColor(mRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_SetTextureBlendMode(pTexture->getTexture(), SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(mRenderer, nullptr);
	SDL_SetRenderTarget(mRenderer, nullptr);
}

void Component::RenderToComponent(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dsRect, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, pTexture->getTexture());
	pTexture->parseTexture(texture, srcRect, dsRect, angle, center, flip);

}

void Component::Show(SDL_Rect* srcRect,const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, nullptr);
	SDL_RenderCopyEx(gRenderer, pTexture->getTexture(), srcRect, pTexture->getRectPointer(), angle, center, flip);
}

void Component::Slide(const int &vel_x, const int &vel_y) {
	pTexture->getRectPointer()->x += vel_x;
	pTexture->getRectPointer()->y += vel_y;

}

bool Component::SlideOut(const int& vel_x, const int& vel_y) {
	if ((pTexture->getRectPointer()->x < SCREEN_WIDTH || pTexture->getRectPointer()->x + pTexture->getRectPointer()->w > 0) && (pTexture->getRectPointer()->y < SCREEN_HEIGHT || pTexture->getRectPointer()->y + pTexture->getRectPointer()->h > 0)) {
		Slide(vel_x, vel_y);
		return false;
	}
	return true;
}

bool Component::SlideTo(const int& x, const int& y, const int& vel_x, const int& vel_y) { 
	bool done = true;
	if (x > -1)
	{
		if (abs(x - pTexture->getRectPointer()->x) > vel_x) {
			Slide(vel_x * abs(x - pTexture->getRectPointer()->x) / (x - pTexture->getRectPointer()->x), 0);
			done = false;
		}
		else if (abs(pTexture->getRectPointer()->x - x) <= vel_x) {
			pTexture->getRectPointer()->x = x;
		}
	}
	if (y > -1) {
		if (abs(y - pTexture->getRectPointer()->y) > vel_y) {
			Slide(0, vel_y * abs(y - pTexture->getRectPointer()->y) / (y - pTexture->getRectPointer()->y));
			done = false;
		}
		else if (abs(pTexture->getRectPointer()->y - y) <= vel_y) {
			pTexture->getRectPointer()->y = y;
		}
	}
	return done;

}