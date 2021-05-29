#include <tuple.h>
#include <stdio.h>
#include <string.h>

int main()
{
   Tuple obj;
   Tuple obj1;
   memset(&obj,0,sizeof(obj));
   memset(&obj1,0,sizeof(obj1));
   TupleAdd(&obj1,INT,7,INT,8,FLOAT,3.5,STR,"obj1",END);
//    AddMember2Tuple(&obj,STR,"Deba",INT,5,INT,10,END);
//    TupleAdd(&obj,STR,"obj",INT,1,INT,5,FLOAT,3.2,DOUBLE,8.4,END);
//   AddMember2Tuple(&obj,FLOAT,3.2,DOUBLE,8.0,END);
//    printf("length:%d\n",len(obj));
//    TupleAdd(&obj,TUPLE,obj1,END);
//    TupleAdd(&obj,STR,"obj",INT,1,INT,5,FLOAT,3.2,DOUBLE,8.4,END);
//    TupleShow(&obj);
//    printf("length :%d\n",TupleLen(&obj));
//    TupleRemove(&obj,STR,"obj");
//    TupleRemove(&obj,INT,5);
//    TupleShow(&obj);
      TupleAdd(&obj,STR,"obj",INT,1,INT,5,FLOAT,3.2,DOUBLE,8.4,TUPLE,obj1,END);
      TupleShow(&obj);
      printf("length :%d\n",TupleLen(&obj));
      TupleClear(&obj);
      printf("length :%d\n",TupleLen(&obj));
      TupleShow(&obj);
      printf("length :%d\n",TupleLen(&obj));

   return 0;
}