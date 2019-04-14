#include "Pack.h"

Pack::Pack(){

}

Pack::~Pack(){
    
}

OBJTYPE Pack::type() const{
    return OBJTYPE::PACK;
}

const char* Pack::name() const{
    return "Pack";
}


