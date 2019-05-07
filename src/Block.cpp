#include "Block.h"

Block::Block(SDL_Renderer* renderer, SDL_Texture* dsTexture):MyTexture(renderer, dsTexture){
	
}

Block::~Block(){

}

OBJTYPE Block::type() const {
    return OBJTYPE::BLOCK;
}

const char* Block::name() const {
    return "Block";
}

void Block::setPos(int x, int y) {
	getRectPointer()->x = x;
	getRectPointer()->y = y;
}

