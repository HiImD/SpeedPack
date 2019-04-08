#ifndef PACK2X4
#define PACK2X4

#include "Pack.h"
#include "Block.h"
#include "PickableBlock.h"
#include "FixedBlock.h"

class Pack2x4: public Pack{
private:
    Block* table[2][4];
    Func::Vector mouseOnBlock;
protected:
    
public:
    Pack2x4();
    ~Pack2x4();

    int type() const;
    const char* name() const;

    void checkMouse();
    void checkMouseOver();
    void init();
    
    void Show();

    void HandleInputEvents(SDL_Event &events);


};
#endif