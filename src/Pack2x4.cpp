#include "Pack2x4.h"

Pack2x4::Pack2x4(){
    setPos(300,265);
    setWH(400,513);
    loadImg("src/img_src/pack2x4/pack2x4_3_split_625x802.png");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            table[i][j] = NULL;
        }
    }  
    mouseOnBlock.set(-1,-1);
    checkMouse();
}

Pack2x4::~Pack2x4(){
   for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != NULL){
                delete table[i][j];
                table[i][j] = NULL;
            }
        }
    }  
}

int Pack2x4::type() const{
    return 0;
}

const char* Pack2x4::name() const{
    return "Pack2x4";
}

void Pack2x4::checkMouse(){
    mouseOnBlock.set(-1,-1);

    int x, y;
    SDL_GetMouseState(&x, &y);
    x -= (getX() + 14);
    y -= (getY() + 274);
    if(Func::inRange(x, 0, 371) && Func::inRange(y, 0, 185)){      
        if((x == (x/92)*(93)) || (y == (y/92)*(93)))
            return;
        
        int j = x / 93, i = y/93; //93 = 92 (Blocksize) + 1 (gap between 2 blocks)
        
        if(table[i][j] != NULL){
            if(table[i][j]->type() == 1){
                mouseOnBlock.set(i,j);
                ((PickableBlock*) table[i][j])->setVisible(false);
            }
        }
    }
}

void Pack2x4::checkMouseOver(){
    if(mouseOnBlock.x != -1 && mouseOnBlock.y != -1){
        if(table[mouseOnBlock.x][mouseOnBlock.y] != NULL){
            ((PickableBlock*) table[mouseOnBlock.x][mouseOnBlock.y])->setVisible(false);
        }
    }
}

void Pack2x4::init(){
    //Func::Vector* init_arr = Func::randUnion(2, 4);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            table[i][j] = new PickableBlock();
            table[i][j]->setRect(getX() + 14 + 93*j , getY() + 274 + 93*i, 92, 92);
        }
    }     
}

void Pack2x4::Show(){
    BaseObj::Show();
    checkMouseOver();
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != NULL){
                table[i][j]->Show();
            }
        }
    } 
}

void Pack2x4::HandleInputEvents(SDL_Event &events){
    switch (events.type)
    {
        case SDL_MOUSEMOTION:
            checkMouse();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(events.button.button == SDL_BUTTON_LEFT){
                if(mouseOnBlock.x != -1 && mouseOnBlock.y != -1){
                    if(table[mouseOnBlock.x][mouseOnBlock.y] != NULL){
                        delete table[mouseOnBlock.x][mouseOnBlock.y];
                        table[mouseOnBlock.x][mouseOnBlock.y] = NULL;
                    }
                }
            }
            break;
    
        default:
            break;
    }
    
}

