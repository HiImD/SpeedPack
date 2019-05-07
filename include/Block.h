/*
	Block la cac doi tuong nam tren Pack
	Bao gom:
		+ PickableBlock: Block co kha nang tuong tac
		+ FixedBlock: Block khong co kha nang tuong tac
		+ TheCamera: Tuong trung cho cau tra loi nguoi choi lua chon
*/

#pragma once

#include "MyObj.h"
#include "MyTexture.h"

class Block: public MyTexture{
private:

protected:
public:
    Block(SDL_Renderer* renderer, SDL_Texture* dsTexture);
	virtual ~Block();
	virtual OBJTYPE type() const;
    virtual const char* name() const;

	void setPos(int x, int y);
    virtual void render(SDL_Renderer* renderer = nullptr, const double& angle = 0, const SDL_Point* center = nullptr, const SDL_RendererFlip& flip = SDL_FLIP_NONE) = 0;
};
