#include "PickableBlock.h"

PickableBlock::PickableBlock(){
    loadImg("src/img_src/active_block_92x92.png");
    visible = true;
}

PickableBlock::~PickableBlock(){

}

int PickableBlock::type() const{
    return 1;
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

