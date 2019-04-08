#include "Pack2x4.h"

Pack2x4::Pack2x4(){
    blocks = NULL;
    activeBlock = 0;
}

Pack2x4::~Pack2x4(){
    if(blocks != NULL){
        delete [] blocks;
        blocks = NULL;
    }    
}

void Pack2x4::init(){
    Func::Vector* init_arr = Func::randUnion(2, 4);
    
    int len = init_arr[0].x;
    pickableBlock = new PickableBlock[init_arr[0].y];
    activeBlock = init_arr[0].y;
    blocks = new FixedBlock[(8 - activeBlock) / 2];

    int activeBlock_id = 0;
    int fixedBlock_id = 0;
    for(int i = 1; i < len; i+= 2){
        Func::Vector tmp = init_arr[i] - init_arr[i + 1];
        if(tmp.x == 0 && tmp.y == 0){
            pickableBlock[activeBlock_id].setRect(getX() + 14 + 93*init_arr[i].y, getY() + 274 + 93*init_arr[i].x, 92, 92);
            activeBlock_id++;
        } else {
            if(abs(tmp.x) == 1 && !tmp.y){
                blocks[fixedBlock_id].setSize(2, 1);
                blocks[fixedBlock_id].setRect(getX() + 14 + 93*init_arr[i].y, getY() + 274 + 93*init_arr[i].x, 92, 92*2 + 1);           
            } else if (abs(tmp.y) == 1 && !tmp.x){
                blocks[fixedBlock_id].setSize(1, 2);
                blocks[fixedBlock_id].setRect(getX() + 14 + 93*init_arr[i].y, getY() + 274 + 93*init_arr[i].x, 92*2 + 1, 92);
                fixedBlock_id++;
            }
        }
    }
    
    
    //Log init_arr
    std::cout << activeBlock << std::endl; 
    for(int i = 0; i < len; i+= 1){
        std::cout << init_arr[i].toString() << std::endl;        
    }

    
}

void Pack2x4::Show(){
    BaseObj::Show();
    for(int i = 0; i < (8 - activeBlock) / 2; i++){
        blocks[i].Show(); 
    }

    for(int i = 0; i < activeBlock  ; i++){
        pickableBlock[i].Show(); 
    }
    
}



