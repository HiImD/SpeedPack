#ifndef BLOCK_H_
#define BLOCK_H_

#ifndef PACK_H_
#include "Pack.h"
#endif

#include "BaseObj.h"


class Block: public BaseObj{
private:
public:
    Block();
    virtual OBJTYPE type() const;
    virtual const char* name() const;
    virtual ~Block() = 0;
    virtual void Show() = 0;
};


#endif