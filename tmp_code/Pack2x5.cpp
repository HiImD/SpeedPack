#include "Pack2x4.h"

// origin chua duoc giai phong

Pack2x4::Pack2x4(){
    close = 0;
    theta = 0;

    setRect(SIZE::PACK::PACK2X4::UP);
    setPos(300,265);
    loadImg(IMGPATH::PACK::PACK2X4::UP);
    // addMyTexture();
    // setRect(SIZE::PACK::PACK2X4::BOTTOM, 1);
    // setPos(300,520, 1);
    // loadImg(IMGPATH::PACK::PACK2X4::DOWN, 1);
    // addMyTexture();
    // loadImg(IMGPATH::PACK::PACK2X4::CLOSE, 2);
    // setRect(0,0,400,255, 2);
    // addMyTexture();
    // loadImg(IMGPATH::PACK::PACK2X4::CLOSE, 3);
    // setRect(0,0,400,255, 3);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            pick_table[i][j] = NULL;
            fixed_table[i][j] = NULL;
        }
    }
    // mouseOnBlock.set(-1,-1);
    // checkMouse();
}

Pack2x4::~Pack2x4(){
    SDL_Delay(500);
    deleteTable(); 
    SDL_DestroyTexture(origin);
}

OBJTYPE Pack2x4::type() const{
    return OBJTYPE::PACK2x4;
}

const char* Pack2x4::name() const{
    return "Pack2x4";
}

int Pack2x4::caculNewW(int theta){
    double h1 = pow(pow(13, 2) - 120*sin(theta*PI*1.0/180), 0.5)*100;
    h1 = round(h1);
    return round((SIZE::PACK::PACK2X4::UP.w*1.0 /5)*6500/h1);
}

int Pack2x4::caculNewH(int theta){
    int h = 5;
    double newH = 100*(12*h*abs(cos(theta*PI/180)))/(12 - h*sin(theta*PI/180));
    return round(SIZE::PACK::PACK2X4::UP.h*newH*1.0 / 500);
}



void Pack2x4::checkMouse(){
    mouseOnBlock.set(-1,-1);
    int x, y;
    SDL_GetMouseState(&x, &y);
    x -= (getX(1) + 14);
    y -= (getY(1) + 18);
    if(Func::inRange(x, 0, 371) && Func::inRange(y, 0, 185)){      
        if((x == (x/92)*(93)) || (y == (y/92)*(93)))
            return;
        int j = x / 93, i = y/93; //93 = 92 (Blocksize) + 1 (gap between 2 blocks)
        if(pick_table[i][j] != NULL){
            mouseOnBlock.set(i,j);
        }
    }
}

void Pack2x4::checkMouseOver(){
    if(mouseOnBlock.x != -1 && mouseOnBlock.y != -1){
        if(pick_table[mouseOnBlock.x][mouseOnBlock.y] != NULL){
            pick_table[mouseOnBlock.x][mouseOnBlock.y]->setVisible(false);
        }
    }
}

void Pack2x4::init(){
    std::vector< std::vector<int>> init_table = Func::randUnion(2, 4);
    int n_fixed = init_table[2][0];

    //Sinh ngau nhien vi tri cac FixedBlock de parse vao UP
    int i0;
    int j0;
    
    for(int i = 0; i < n_fixed/2; i++){
        i0 = rand() % 2;
        j0 = rand() % 4;
        if(init_table[i0][j0] != 0 && init_table[i0][j0] != -1 && init_table[i0][j0] != -3){           
            init_table[i0][j0] = -3;
            fixed_table[i0][j0] = new FixedBlock(init_table[i0][j0]);
            fixed_table[i0][j0]->setPos(getX(1) + 14 + j0*93,getY(1) + 18 + i0*93);
            //parse(0, (FixedBlock* ) fixed_table[i0][j0], true);
        } else {
            i--;
        }
    }
    
    
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(init_table[i][j] == 0){
                pick_table[i][j] = new PickableBlock(true);
                pick_table[i][j]->setPos(getX(1) + 14 + j*93,getY(1) + 18 + i*93);
            } else if(init_table[i][j] == -3){
                pick_table[i][j] = new PickableBlock(false);
                pick_table[i][j]->setPos(getX(1) + 14 + j*93,getY(1) + 18 + i*93);
            } else if(init_table[i][j] != -1){
                fixed_table[i][j] = new FixedBlock(init_table[i][j]);
                fixed_table[i][j]->setPos(getX(1) + 14 + j*93,getY(1) + 18 + i*93);
                //parse(0, (FixedBlock* ) fixed_table[i][j], false);
            }
        }
    }
       
}

void Pack2x4::Close(){
    static int delay = 3;
    int newW = caculNewW(theta);
    int newH = caculNewH(theta);
    if(theta < 90){
        setTexture(Func::resizeTextureWithTrapeZoidShape(origin, newW,  1, -1));
        setRect(300 - (newW - 400)/ 2, 265 + (255 - newH), newW, newH);
        theta++;
        SDL_Delay(delay);
    } else if(theta == 90){
        SDL_DestroyTexture(origin);
        origin = getTexture(2);
        setTexture(origin);
        theta++;
    } else if(theta <= 180){
        setTexture(Func::resizeTextureWithTrapeZoidShape(origin, newW,  1, 1));
        setRect(300 - (newW - 400)/ 2, 521, newW, newH);
        theta+=2;
        SDL_Delay(delay);
    } else{
        setTexture(getTexture(3), 0, true);
        SDL_DestroyTexture(origin);
        origin = NULL;
        deleteTable();
        close = 2;
        
        //Func::log("Closed", this);
    }
}

bool Pack2x4::wasClose(){
    return (close == 2);
}

void Pack2x4::deleteTable(){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(pick_table[i][j] != NULL){
                delete pick_table[i][j];
                pick_table[i][j] = NULL;
            }
            if(fixed_table[i][j] != NULL){
                delete fixed_table[i][j];
                fixed_table[i][j] = NULL;
            }
        }
    } 
}

void Pack2x4::Show(){
    // if(close)
    //     Close();
    // else 
    //     checkMouseOver();
    // BaseObj::Show(1);
    // for(int i = 0; i < 2; i++){
    //     for(int j = 0; j < 4; j++){
    //         if(pick_table[i][j] != NULL){
    //             pick_table[i][j]->Show();
    //         }
    //     }
    // }
    // BaseObj::Show(0); 

    BaseObj::ShowAll();
}

void Pack2x4::HandleInputEvents(SDL_Event &events){
    switch (events.type)
    {
        case SDL_MOUSEMOTION:
            if(!close)
                checkMouse();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(events.button.button == SDL_BUTTON_LEFT){
                if(mouseOnBlock.x != -1 && mouseOnBlock.y != -1 && !close){
                    if(pick_table[mouseOnBlock.x][mouseOnBlock.y] != NULL){
                        if(pick_table[mouseOnBlock.x][mouseOnBlock.y]->getAnswer()){
                            Func::log("Right");
                        } else {
                            Func::log("Wrong");
                        }
                        close = true;
                        
                    }
                }
            }
            break;
    
        default:
            break;
    }
    
}

