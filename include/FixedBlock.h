/*
	FixedBlock la cac Block khong co kha nang tuong tac, dong vai tro nhu vat can
*/

#ifndef FIXEDBLOCK_H_
#define FIXEDBLOCK_H_


#include "Block.h"
#include <vector>


class FixedBlock: public Block{
private:
    int row, col; //Kick thuoc cua Block
protected:

public:
	int onPart = 0; //id cua part ma Block nam tren do

	FixedBlock(SDL_Renderer* renderer, SDL_Texture* dsTexture, int id);
    ~FixedBlock();

    OBJTYPE type() const; 
    const char* name() const;
  
    void setSize(const int& row, const int& col);
    int getRow();
    int getCol();
    void render(SDL_Renderer* renderer = nullptr, const double& angle = 0, const SDL_Point* center = nullptr, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
};

#endif