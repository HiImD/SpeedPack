#include "ButtonComponent.h"



ButtonComponent::ButtonComponent(const int& w, const int& h, SDL_Color color, std::string path, std::string _text) : Component(w, h, color), buttonIcon(mRenderer, pTexture->getTexture()), text(mRenderer, pTexture->getTexture()), renderRectOfButton({ 0 ,0, 60, 60 }) {
	SetButtonIcon(path);
	buttonIcon.setRect(0,0 , 60, 60);
	mouseIn = CheckMouseOver();
	setBGColor(color);
	dsRect1 = {0, 10 , 60, 60};
	dsRect2 = { 0, -70, 60, 60 };
	update = true;
	theta = 0;
	type = 1;
	text.RenderTextSolid(_text, {255, 255, 255});
	TTF_SizeText(gFont, _text.c_str(), &text.getRectPointer()->w, &text.getRectPointer()->h);
	text.getRectPointer()->x = -text.getRectPointer()->w;
	text.getRectPointer()->y = (GetComponentHSize() - text.getRectPointer()->h)/ 2;
}

ButtonComponent::~ButtonComponent() {

}

bool ButtonComponent::SetButtonIcon(std::string path) {
	return buttonIcon.loadImg(path);
}

void ButtonComponent::HandleInputEvents(SDL_Event& events) {
	switch (events.type) {
	case SDL_MOUSEMOTION:
		mouseIn = CheckMouseOver();
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (events.button.button == SDL_BUTTON_LEFT) {
			text.RenderTextSolid("  PLAY  ", { 255, 255, 255 });
			int oldW = text.getRectPointer()->w;
			TTF_SizeText(gFont, "  PLAY  ", &text.getRectPointer()->w, &text.getRectPointer()->h);
			text.getRectPointer()->x -= text.getRectPointer()->w - oldW;
			update = true;
		}
	}
	
}

bool ButtonComponent::CheckMouseOver() {
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse, &yMouse);
	if (Func::inRange(xMouse, pTexture->getRectPointer()->x, pTexture->getRectPointer()->x + pTexture->getRectPointer()->w)
		&&
		Func::inRange(yMouse, pTexture->getRectPointer()->y, pTexture->getRectPointer()->y + pTexture->getRectPointer()->h)
		) {
		return true;
	}
}

void ButtonComponent::MouseOnButton_Vertical () {
	if (mouseIn) {
		if (dsRect2.y < 10) {
			dsRect1.y += 8;
			dsRect2.y += 8;
			update = true;
		}
	}
	else {
		if (dsRect1.y > 10) {
			dsRect1.y -= 5;
			dsRect2.y -= 5;
			update = true;
		}
	}	
}

void ButtonComponent::MouseOnButton_Hozirontal() {
	if (mouseIn) {
		if (theta < round((text.getRectPointer()->w + 10) *6 / PI)) {
			theta += 10;
			buttonIcon.getRectPointer()->x += round( 10 * PI * 30 / 180);
			text.getRectPointer()->x += round(30 * PI * 10 / 180);
			renderRectOfButton.w += round(30 * PI * 10 / 180);
			pTexture->getRectPointer()->w = renderRectOfButton.w;
			update = true;
		}
	}
	else {
		if (theta > 0)
		{
			theta -= 10;
			buttonIcon.getRectPointer()->x -= round(10 * PI * 30 / 180);
			text.getRectPointer()->x -= round(10 * PI * 30 / 180);
			renderRectOfButton.w -= round(30 * PI * 10 / 180);
			pTexture->getRectPointer()->w = renderRectOfButton.w;
			update = true;
		}
	}
}

void ButtonComponent::Render() {
	ClearComponent();
	if (type == 0)
	{
		if (dsRect1.y < GetComponentHSize())
			buttonIcon.render(&dsRect1);
		if (dsRect2.y > -60)
			buttonIcon.render(&dsRect2);
	}
	else if (type == 1) {
		buttonIcon.render(mRenderer, theta);
	}
	text.render();
}

void ButtonComponent::Show(SDL_Rect* srcRect, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	MouseOnButton_Hozirontal();
	if (update) {
		Render();
		update = false;
	}
	pTexture->RenderPartOfTexture(&renderRectOfButton);
}
