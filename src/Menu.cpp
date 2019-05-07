#include "Menu.h"

Menu::Menu(TTF_Font* font, SDL_Color fg_text, SDL_Color bg_text) {
	this->font = font;
	this->fg_text = fg_text;
	this->bg_text = bg_text;
	TTF_SizeText(font, "A", nullptr, &h_button_size);
	mouseOnButton = 0;
}

Menu::~Menu() {
	for (MyTexture* b : pMyTexture_arr) {
		delete b;
	}
}

OBJTYPE Menu::type() const {
	return OBJTYPE::MENU;
}

const char* Menu::toString() const {
	return "Menu";
}


void Menu::AddButton(const std::string& id, const std::string& text, const int& index) {
	if (id == "") {
		SDL_Log("Invalid id");
		return;
	}
	if (button_id.find(id) != button_id.end()) {
		SDL_Log("Id already been taken");
		return; 
	} 
	else {
		Button* new_button = new Button(id, mRenderer, pTexture->getTexture());
		new_button->RenderTextShaded(text, fg_text, bg_text, true, true, font);
		button_id.insert(id);
		if (index == -1) {
			PushBack((MyTexture*)new_button);
		}
		else {
			InsertMyTexture(index, (MyTexture*)new_button);
		}
	}	
}

void Menu::EraseButton(const int& index) {	
	if (index == -1) {
		if ((**pMyTexture_arr.end()).type() == OBJTYPE::BUTTON) {
			button_id.erase((*((Button*) *pMyTexture_arr.end())).GetID());
			PopBack();
		}
	}
	else {
		if (pMyTexture_arr[index]->type() == OBJTYPE::BUTTON) {
			button_id.erase((*((Button*) pMyTexture_arr[index])).GetID());
			EraseMyTexture(index, true);
		}
	}
}

void Menu::CheckMouse() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (Func::inRect(x, y, pTexture->getRectPointer())) {
		y -= GetComponentYPos() + margin.top;
		if (y % (h_button_size + margin.between) > h_button_size || y / (h_button_size + margin.between) >= pMyTexture_arr.size()) {
			mouseOnButton = -1;
		} else if (pMyTexture_arr[y / (h_button_size + margin.between)]->type() == OBJTYPE::BUTTON) {
			mouseOnButton = y / (h_button_size + margin.between);
		}
	}
	else {
		mouseOnButton = -1;
	}
}

std::string Menu::HandleInputEvents(SDL_Event& events) {
	std::string return_str = "";
	switch (events.type)
	{
	case SDL_MOUSEMOTION:
		if(!done)
			CheckMouse();
		break;
	case SDL_MOUSEBUTTONDOWN:
		CheckMouse();
		if (mouseOnButton != -1) {
			return_str = ((Button*)pMyTexture_arr[mouseOnButton])->GetID();
		}
		break;
	case SDL_KEYDOWN:
		if (events.key.keysym.sym == SDLK_DOWN) {
			
			if (mouseOnButton + 1 < pMyTexture_arr.size()) {
				mouseOnButton++;
			}
		}
		else if (events.key.keysym.sym == SDLK_UP) {
			if (mouseOnButton == -1)
				mouseOnButton = pMyTexture_arr.size() - 1;
			else if (mouseOnButton > 0) {
				mouseOnButton--;
			}
		}
		else if (events.key.keysym.sym == SDLK_RETURN) { //Press Enter
			return_str = ((Button*)pMyTexture_arr[mouseOnButton])->GetID();
		}
		
		break;
	default:
		
		break;
	}
	return return_str;
}

void Menu::Show(SDL_Rect* srcRect, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_SetRenderTarget(mRenderer, nullptr);
	if (mouseOnButton != -1) {
		SDL_Rect chose_rect = { GetComponentXPos(), GetComponentYPos() + ((Button*)pMyTexture_arr[mouseOnButton])->getRectPointer()->y,  GetComponentWSize(), h_button_size };
		SDL_SetRenderDrawColor(mRenderer, bg_text.r, bg_text.g, bg_text.b, bg_text.a);
		SDL_RenderFillRect(mRenderer, &chose_rect);
		SDL_SetRenderDrawColor(mRenderer,0, 0, 0, 255);
	}
	SDL_RenderCopyEx(gRenderer, pTexture->getTexture(), srcRect, pTexture->getRectPointer(), angle, center, flip);
}