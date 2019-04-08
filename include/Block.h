#ifndef BLOCK
#define BLOCK

#ifndef PACK
#include "Pack.h"
#endif

#include "BaseObj.h"


class Block: public BaseObj{
private:
public:
    Block();
    virtual ~Block() = 0;

    virtual int type() const = 0;
    virtual const char* name() const = 0;
    virtual void Show() = 0;
};


#endif