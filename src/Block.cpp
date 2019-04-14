#include "Block.h"

Block::Block(){
    //BaseObj();
    //loadImg("src/img_src/empty_block_92x92.png");
}

Block::~Block(){

}

OBJTYPE Block::type() const {
    return OBJTYPE::BLOCK;
}

const char* Block::name() const {
    return "Block";
}

