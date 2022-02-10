#include <cstdio>
#include "smart_pointer.h"

class shape {
public:
  virtual ~shape() {}
};

class circle : public shape {
public:
  ~circle() { puts("~circle()"); }
};

int main()
{
  tiny::smart_shared_pointer<circle> ptr1(new circle());
  printf("use count of ptr1 is %ld\n", ptr1.use_count());

  tiny::smart_shared_pointer<shape> ptr2;
  printf("use count of ptr2 was %ld\n", ptr2.use_count());

  ptr2 = ptr1;

  printf("use count of ptr2 is now %ld\n", ptr2.use_count());

  if (ptr1) {
    puts("ptr1 is not empty");
  }

  tiny::smart_shared_pointer<circle> ptr3 = tiny::dynamic_pointer_cast<circle>(ptr2);
  printf("use count of ptr3 is %ld\n", ptr3.use_count());

}