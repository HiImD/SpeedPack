#pragma once
#include "Pack.h"

class Pack3_3x2 : public Pack {
private:
	SDL_Texture* backup_texture;
	bool update;
protected:
public:
	Pack3_3x2();
	~Pack3_3x2();

	virtual OBJTYPE type() const;
	virtual const char* toString() const;
	void init();
	void Close();
	void HandleInputEvents(SDL_Event& event);

	void render();

	int getPoint() const;
	bool DoneWithPack() const;
};