#include "FixedBlock.h"

FixedBlock::FixedBlock(){
    row = 0;
    col = 0;
}

FixedBlock::~FixedBlock(){

}

int FixedBlock::type(){
    return 1;
}

const char* FixedBlock::name(){
    return "FixedBlock";
}

void FixedBlock::setSize(int row, int col){
    this->row = row;
    this->col = col;
    loadImg();
}

void FixedBlock::loadImg(){
    BaseObj::loadImg(path_imgs[row - 1][col - 1][rand() % path_imgs[row - 1][col - 1].size()]);
}