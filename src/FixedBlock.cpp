#include "FixedBlock.h"

FixedBlock::FixedBlock(int row, int col){
    setSize(row, col);
}

FixedBlock::FixedBlock(int id){
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

void FixedBlock::setSize(int row, int col){
    this->row = row;
    this->col = col;
    if(row == 1 && col == 1){
        setRect(SIZE::BLOCK::BLOCK1X1);
        BaseObj::loadImg(IMGPATH::BLOCK::BLOCK1X1[rand() % IMGPATH::BLOCK::BLOCK1X1.size()]);
    } else if (row == 2 && col == 1){
        setRect(SIZE::BLOCK::BLOCK2X1);
        BaseObj::loadImg(IMGPATH::BLOCK::BLOCK2X1[rand() % IMGPATH::BLOCK::BLOCK2X1.size()]);
    } else if (row == 1 && col == 2){
        setRect(SIZE::BLOCK::BLOCK1X2);
        BaseObj::loadImg(IMGPATH::BLOCK::BLOCK1X2[rand() % IMGPATH::BLOCK::BLOCK1X2.size()]);
    } else {
        Func::log(std::string("Unsupported block with size %dx%d yet ", row, col));
    }
}

int FixedBlock::getRow(){
    return row;
}


int FixedBlock::getCol(){
    return col;
}

void FixedBlock::loadImg(){
    
}

void FixedBlock::Show(){
    BaseObj::Show(0);
}