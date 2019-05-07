#pragma once
#include "Component.h"

class ButtonComponent : public Component {
private:
	MyTexture buttonIcon;
	MyTexture text;
	SDL_Rect renderRectOfButton;
	SDL_Rect dsRect1, dsRect2;
	SDL_Color bgColor;

	bool mouseIn;
	bool update;
	int theta;
	int type;
protected:
	bool CheckMouseOver();
public:
	ButtonComponent(const int& w, const int& h, SDL_Color color, std::string path, std::string _text);
	~ButtonComponent();

	bool SetButtonIcon(std::string path);
	void HandleInputEvents(SDL_Event& events);
	void MouseOnButton_Vertical();
	void MouseOnButton_Hozirontal();
	void Render();
	void Show(SDL_Rect* srcRect = NULL, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);;
};