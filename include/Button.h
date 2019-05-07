/*
	Về Class Button:
		- Kế thừa MyTexture
		- Cơ bản chỉ là các Text Texture
*/
#pragma once
#ifndef BUTTON_H_
#define BUTTON_H_
#include "MyTexture.h"

class Button : public MyTexture {
private:
	const std::string my_id;
protected:
public:
	Button(std::string id, SDL_Renderer* renderer, SDL_Texture* default_render_tezture = nullptr);
	~Button();

	//Overide MyObj.h
	virtual OBJTYPE type() const;
	virtual const char* toString() const;

	std::string GetID();
};


#endif // !BUTTON_H_

