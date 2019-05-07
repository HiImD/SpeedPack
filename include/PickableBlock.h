/*
	PickableBlock la block co kha nang tuong tac, dong vai tro nhu 1 trong cac dap an cua cau hoi
*/

#pragma once

#include "Block.h"

class PickableBlock: public Block{
private:
    bool visible;
    bool answer;
	char chosed;
public:
    PickableBlock(SDL_Renderer* renderer, SDL_Texture* dsTexture, bool answer);
    ~PickableBlock();
    
    OBJTYPE type() const ;
    const char* name() const;
    void setVisible(bool visible);
	void Chosed();
    void render(SDL_Renderer* renderer = nullptr, const double& angle = 0,const SDL_Point* center = nullptr,const SDL_RendererFlip& flip = SDL_FLIP_NONE);
    bool getAnswer();

};

