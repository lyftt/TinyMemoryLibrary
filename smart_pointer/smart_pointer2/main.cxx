#include "smart_pointer.h"
#include <iostream>

class Obj
{
public:
    Obj(){ std::cout<<"Obj con"<<std::endl; }
    ~Obj(){ std::cout<<"Obj decon"<<std::endl; }
};

class ObjS: public Obj
{
public:
    ObjS(){ std::cout<<"ObjS con"<<std::endl; }
    ~ObjS(){ std::cout<<"ObjS decon"<<std::endl; }
};

int main()
{
    tiny::smart_unique_pointer<Obj> up(new Obj);
    tiny::smart_unique_pointer<Obj> up2;
    tiny::smart_unique_pointer<Obj> up3;

    tiny::smart_unique_pointer<ObjS> up4(new ObjS);
    up3 = std::move(up4);

    return 0;
}