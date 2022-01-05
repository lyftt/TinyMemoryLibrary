#include "smart_pointer.h"
#include <iostream>

class Obj
{
public:
    Obj(){ std::cout<<"Obj con"<<std::endl; }
    ~Obj(){ std::cout<<"Obj decon"<<std::endl; }
};

int main()
{
    tiny::smart_unique_pointer<Obj> up(new Obj);
    tiny::smart_unique_pointer<Obj> up2;
    tiny::smart_unique_pointer<Obj> up3;

    up2 = std::move(up);
    up3 = std::move(up2);

    return 0;
}