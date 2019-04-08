#ifndef PICKABLEBLOCK
#define PICKABLEBLOCK


#include "Block.h"



class PickableBlock: public Block{
private:
    bool visible;
public:
    PickableBlock();
    ~PickableBlock();
    
    int type() const ;
    const char* name() const;
    void setVisible(bool visible);
    void Show();
};


#endif