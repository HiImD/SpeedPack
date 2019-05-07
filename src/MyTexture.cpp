#include "MyTexture.h"
//comtrucstor khong tham so chi duoc dung khi cap phat mang bo nho dong
//Phai su dung init neu khoi tao bang constructor khong tham so
MyTexture::MyTexture() {
	mRect = new SDL_Rect;
	mTexture = nullptr;
}

//Ham khoi tao khong tuong minh
void MyTexture::init(SDL_Renderer* renderer, SDL_Texture* defaultRenderTarget) {
	mRenderer = renderer;
	this->defaultRenderTarget = defaultRenderTarget;
}

MyTexture::MyTexture(SDL_Renderer* renderer, SDL_Texture* defaultRenderTarget) {
	mRect = new SDL_Rect;
	mTexture = nullptr;
	mRenderer = renderer;
	this->defaultRenderTarget = defaultRenderTarget;
}

MyTexture::~MyTexture() {
	free();
	delete mRect;
}

OBJTYPE MyTexture::type() const {
	return OBJTYPE::MYTEXTURE;
}

const char* MyTexture::toString() const {
	return "MyTexture";
}


void MyTexture::free() {
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

bool MyTexture::loadImg(std::string path) {
	free();
	mTexture = Func::loadImg(path);
	if (mTexture != nullptr) {
		return true;
	}
	return false;
}

void MyTexture::setRect(int x, int y, int w, int h) {
	(*mRect) = { x, y, w, h };
}

void MyTexture::setRect(SDL_Rect* rect, bool deleted) {
	if (deleted && mRect != nullptr) {
		delete mRect;
	}
	mRect = rect;
}


void MyTexture::setTexture(SDL_Texture* texture, bool destroy) {
	if (destroy) {
		free();
	}
	mTexture = texture;
}

SDL_Rect* MyTexture::getRectPointer() {
	return mRect;
}

SDL_Texture* MyTexture::getTexture() {
	return mTexture;
}

SDL_Renderer* MyTexture::getRenderer() {
	return mRenderer;
}

SDL_Texture* MyTexture::createTransparentTexture(Uint32 format, int w, int h, bool replace, SDL_Color color) {
	SDL_SetRenderTarget(mRenderer, nullptr);
	SDL_Texture* transparentTexture = SDL_CreateTexture(mRenderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
	if (transparentTexture == nullptr) {
		SDL_Log("Fail to create transparent texture");
	}
	SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
	SDL_SetRenderTarget(mRenderer, transparentTexture);
	SDL_SetTextureBlendMode(transparentTexture, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(mRenderer, nullptr);
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	if (replace) {
		free();
		mTexture = transparentTexture;
	}
	return transparentTexture;
}

bool MyTexture::convertToTarget() {
	int w, h, access;
	Uint32 format;
	SDL_QueryTexture(mTexture, &format, &access, &w, &h);
	if (access == SDL_TEXTUREACCESS_TARGET)
		return true;
	SDL_Texture* newTexture = createTransparentTexture(format, w, h, false);
	if (newTexture == nullptr) 
		return false;
	SDL_SetRenderTarget(mRenderer, newTexture);
	SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	free();
	mTexture = newTexture;
	return true;
}

bool MyTexture::parseTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dsRect, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	if (convertToTarget()) {
		SDL_SetRenderTarget(mRenderer, mTexture);
		SDL_RenderCopyEx(mRenderer, texture, srcRect, dsRect, angle, center, flip);
		SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	}
	return false;
}


void MyTexture::render(SDL_Renderer* renderer,const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	if(renderer == nullptr)
		SDL_RenderCopyEx(mRenderer, mTexture, nullptr, mRect, angle, center, flip);
	else 
		SDL_RenderCopyEx(renderer, mTexture, nullptr, mRect, angle, center, flip);
}

void MyTexture::Render(const SDL_Rect* srcRect,SDL_Renderer* renderer, const double& angle,const SDL_Point* center,const SDL_RendererFlip& flip) {
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	if (renderer == nullptr)
		SDL_RenderCopyEx(mRenderer, mTexture, srcRect, mRect, angle, center, flip);
	else
		SDL_RenderCopyEx(renderer, mTexture, srcRect, mRect, angle, center, flip);
}

void MyTexture::RenderWithDesRect(SDL_Rect* dsRect, SDL_Rect* srcRect, SDL_Renderer* renderer, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	if (renderer == nullptr)
		SDL_RenderCopyEx(mRenderer, mTexture, srcRect, dsRect, angle, center, flip);
	else
		SDL_RenderCopyEx(renderer, mTexture, srcRect, dsRect, angle, center, flip);
}

void MyTexture::render(SDL_Rect* dsRect, SDL_Renderer* renderer, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	if (renderer == nullptr)
		SDL_RenderCopyEx(mRenderer, mTexture, nullptr, dsRect, angle, center, flip);
	else
		SDL_RenderCopyEx(renderer, mTexture, nullptr, dsRect, angle, center, flip);
}

void MyTexture::RenderPartOfTexture(SDL_Rect* srcRect , SDL_Renderer* renderer, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, defaultRenderTarget);
	if (renderer == nullptr)
		SDL_RenderCopyEx(mRenderer, mTexture, srcRect, mRect, angle, center, flip);
	else
		SDL_RenderCopyEx(renderer, mTexture, srcRect, mRect, angle, center, flip);
}

void MyTexture::Slide(const int& vel_x, const int& vel_y) {
	mRect->x += vel_x;
	mRect->y += vel_y;
}

//Cac ham xu li voi text
bool MyTexture::RenderTextSolid(std::string text, SDL_Color fg, bool resize, bool destroy, TTF_Font* font) {
	SDL_Texture* textTexture = nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), fg);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (textTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			setTexture(textTexture, destroy);
			if (resize) {
				int w, h;
				TTF_SizeText(font, text.c_str(), &w, &h);
				mRect->h = h;
				mRect->w = w;
			}
		}

		SDL_FreeSurface(textSurface);
		return true;
	}
}

bool MyTexture::RenderTextShaded(std::string text, SDL_Color fg, SDL_Color bg,bool resize, bool destroy, TTF_Font* font) {
	SDL_Texture* textTexture = nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Shaded(gFont, text.c_str(), fg, bg);
	
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (textTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			setTexture(textTexture, destroy);
			if (resize) {
				int w, h;
				TTF_SizeText(font, text.c_str(), &w, &h);
				mRect->h = h;
				mRect->w = w;
			}
		}
		
		SDL_FreeSurface(textSurface);
		return true;
	}
}

bool MyTexture::RenderTextBlended(std::string text, SDL_Color fg, bool resize, bool destroy, TTF_Font* font) {
	SDL_Texture* textTexture = nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), fg);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (textTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			setTexture(textTexture, destroy);
			if (resize) {
				int w, h;
				TTF_SizeText(font, text.c_str(), &w, &h);
				mRect->h = h;
				mRect->w = w;
			}
		}

		SDL_FreeSurface(textSurface);
		return true;
	}
}