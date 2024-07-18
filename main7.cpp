#include <cstdio>
#include <map>
#include <new>
#include<variant>
#include "mycommon.h"

struct movemsg{
  int a;
  int b;
};

struct jumpmsg{
  int a;
};

struct msgbase{
  virtual void fun()=0;
  virtual ~msgbase(){}
};

template <typename... Ts> 
struct msgImpl:msgbase{
  
  msgImpl(Ts... args):data(args...){}
  void fun() override{
    printf("magImpl\n");
  }
};

int main()
{


}
