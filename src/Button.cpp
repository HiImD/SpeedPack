#include "Button.h"

Button::Button(std::string id, SDL_Renderer* renderer, SDL_Texture* default_render_tezture):MyTexture(renderer, default_render_tezture), my_id(id){
	
}

Button::~Button() {
	
}

OBJTYPE Button::type() const {
	return OBJTYPE::BUTTON;
}

const char* Button::toString() const {
	return "Button";
}

std::string Button::GetID() {
	return my_id;
}

