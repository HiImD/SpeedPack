#ifndef PACK2X4_H_
#define PACK2X4_H_

#include "Pack.h"
#include "Block.h"
#include "PickableBlock.h"
#include "FixedBlock.h"

class Pack2x4: public Pack{
private:
    Func::Vector mouseOnBlock;
    SDL_Texture* origin;
    PickableBlock* pick_table[2][4];
    FixedBlock* fixed_table[2][4];
    int close;
    int theta;
    Func::Vector upTopPos;
    Func::Vector upTopPosAfterSlide;
protected:
    
public:
    Pack2x4();
    ~Pack2x4();

    OBJTYPE type() const;
    const char* name() const;


    int caculNewW(int theta);
    int caculNewH(int theta);
    void checkMouse();
    void checkMouseOver();
    void init();
    void deleteTable();
    
    void SlideIn();
    void Show();
    void Close();
    bool wasClose();
    void parse(int id, Block*, bool invert = false);
    void HandleInputEvents(SDL_Event &events);



};
#endif