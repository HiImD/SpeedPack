#ifndef PICKABLEBLOCK_H_   
#define PICKABLEBLOCK_H_


#include "Block.h"



class PickableBlock: public Block{
private:
    bool visible;
    bool rightAnswer;
public:
    PickableBlock(bool answer);
    ~PickableBlock();
    
    OBJTYPE type() const ;
    const char* name() const;
    void setVisible(bool visible);
    void Show();
    bool getAnswer();
};


#endif