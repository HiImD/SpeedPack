#ifndef PACK_H_
#define PACK_H_


#include "BaseObj.h"


class Pack: public BaseObj{
private:

protected:

public:
    Pack();
    virtual ~Pack();
    virtual OBJTYPE type() const;
    virtual const char* name() const;
    virtual void init() = 0;
    virtual void HandleInputEvents(SDL_Event &events) = 0;
    


};

#endif