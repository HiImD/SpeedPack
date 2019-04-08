#ifndef PACK
#define PACK


#include "BaseObj.h"


class Pack: public BaseObj{
private:
    int row, col;

protected:

public:
    Pack();
    virtual ~Pack();

    virtual int type() const = 0;
    virtual const char* name() const = 0;
    virtual void init();
    virtual void HandleInputEvents(SDL_Event &events) = 0;
    


};

#endif