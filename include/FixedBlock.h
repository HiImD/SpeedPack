#ifndef FIXEDBLOCK
#define FIXEDBLOCK


#include "Block.h"
#include <vector>


class FixedBlock: public Block{
private:
    int row, col;
    
protected:

public:
    FixedBlock();
    ~FixedBlock();

    int type();
    const char* name();
    
    void setSize(int row, int col);
    void loadImg();

  

};

#endif