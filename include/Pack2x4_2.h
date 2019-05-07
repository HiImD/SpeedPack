#pragma once
#include "Pack.h"
#include "PickableBlock.h"

class Pack2x4_2: public Pack {
private:
	bool update;
	SDL_Texture* backup_texture;
protected:
public:
	Pack2x4_2();
	~Pack2x4_2();

	virtual OBJTYPE type() const;
	virtual const char* toString() const;
	void init();
	void Close();
	void HandleInputEvents(SDL_Event &event);
	void render();
	int getPoint() const;
	bool DoneWithPack() const;
};