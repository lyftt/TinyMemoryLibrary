#include <iostream>
#include <functional>
#include <memory>
#include "smart_pointer.h"

class Obj
{
public:
    Obj(){ std::cout<<"Obj con"<<std::endl; }
    ~Obj(){ std::cout<<"Obj decon"<<std::endl; }
};

int main()
{
    tiny::smart_unique_ptr<Obj> up(new Obj);
    tiny::smart_unique_ptr<Obj> up2(up);

    up = up2;
    return 0;
}