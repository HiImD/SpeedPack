#include "FixedBlock.h"

FixedBlock::FixedBlock(SDL_Renderer* renderer, SDL_Texture* dsTexture, int id):Block(renderer,dsTexture){
    switch (id)
    {  
        case 1:
            setSize(1, 1);
            break;
        case 2:
            setSize(1, 2);
            break;
        case -2:
            setSize(2, 1);
            break;
        default:
            break;
    }
}

FixedBlock::~FixedBlock(){

}

OBJTYPE FixedBlock::type() const{
    return OBJTYPE::FIXEDBLOCK;
}

const char* FixedBlock::name() const{
    return "FixedBlock";
}

void FixedBlock::setSize(const int& row, const int& col){
    this->row = row;
    this->col = col;
    if(row == 1 && col == 1){
		MyTexture::setRect(0,0, SIZE::BLOCK::UNIT_SIZE, SIZE::BLOCK::UNIT_SIZE);
        MyTexture::loadImg(IMGPATH::BLOCK::BLOCK1X1[rand() % IMGPATH::BLOCK::BLOCK1X1.size()]);
    } else if (row == 2 && col == 1){
		MyTexture::setRect(0, 0, SIZE::BLOCK::UNIT_SIZE, 2 * SIZE::BLOCK::UNIT_SIZE + 2);
		MyTexture::loadImg(IMGPATH::BLOCK::BLOCK2X1[rand() % IMGPATH::BLOCK::BLOCK2X1.size()]);
    } else if (row == 1 && col == 2){
		MyTexture::setRect(0, 0, 2 * SIZE::BLOCK::UNIT_SIZE + 2, SIZE::BLOCK::UNIT_SIZE);
		
		MyTexture::loadImg(IMGPATH::BLOCK::BLOCK1X2[rand() % IMGPATH::BLOCK::BLOCK1X2.size()]);
    } else {
        SDL_Log(std::string("Unsupported block with size %dx%d yet ", row, col).c_str());
    }
}

int FixedBlock::getRow(){
    return row;
}


int FixedBlock::getCol(){
    return col;
}


void FixedBlock::render(SDL_Renderer* renderer, const double& angle, const SDL_Point* center, const SDL_RendererFlip& flip){
}