#include "PickableBlock.h"

PickableBlock::PickableBlock(bool answer){
    rightAnswer = answer;
    loadImg(IMGPATH::BLOCK::PICKABLE);
    setRect(SIZE::BLOCK::PICKABLEBLOCK);
    visible = true;
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

void PickableBlock::Show(){
    if(visible){
        BaseObj::Show();
    } else 
        visible = true;
}

bool PickableBlock::getAnswer(){
    return rightAnswer;
}