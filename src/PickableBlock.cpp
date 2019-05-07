#include "PickableBlock.h"

PickableBlock::PickableBlock(SDL_Renderer* renderer, SDL_Texture* dsTexture, bool answer): Block(renderer, dsTexture){
    this->answer = answer;
    visible = true;
	loadImg(IMGPATH::BLOCK::PICKABLE);
	setRect(0, 0, 92, 92);
	chosed = 0;
}

PickableBlock::~PickableBlock(){
    
}

OBJTYPE PickableBlock::type() const{
    return OBJTYPE::PICKABLEBLOCK;
}

const char* PickableBlock::name() const{
    return "PickableBlock";
}

void PickableBlock::setVisible(bool visible){
    this->visible = visible; 
}

void PickableBlock::Chosed() {
	chosed = 1;
	visible = false;
}

void PickableBlock::render(SDL_Renderer* renderer, const double& angle,const SDL_Point* center,const SDL_RendererFlip& flip){
    if(visible){
		MyTexture::Render(nullptr, renderer, angle, center, flip);
    } 
	else if(chosed == 0)
        visible = true;
}

bool PickableBlock::getAnswer(){
    return answer;
}