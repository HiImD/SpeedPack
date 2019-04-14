#ifndef FIXEDBLOCK_H_
#define FIXEDBLOCK_H_


#include "Block.h"
#include <vector>


class FixedBlock: public Block{
private:
    int row, col;
    
protected:

public:
    FixedBlock(int row, int col);
    FixedBlock(int id);
    ~FixedBlock();

    OBJTYPE type() const;
    const char* name() const;
    
    void setSize(int row, int col);
    int getRow();
    int getCol();
    void loadImg();
    void Show();
  

};

#endif