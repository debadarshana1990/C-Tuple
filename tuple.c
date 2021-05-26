/*
 * tuple.c
 *
 *  Created on: 26-May-2021
 *      Author: pde5cob
 */

#include <tuple.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void Create_Entry(Tuple *obj,TYPE type,void *data)
{
   /* Traverse to the end */
   TupleNode *temp = (TupleNode *)(malloc(sizeof(TupleNode)));
   if(NULL == temp)
   {
      perror("Not able to add element");
      exit(0);
   }
   temp->next = NULL;
   temp->type = type;
   temp->p = malloc(sizeof(getsize(type,0,data)));
   memcpy(temp->p,data,getsize(type,0,data));
   if(TRUE != obj->IsinitialAlloc)
   {
      obj->Head = temp;
      obj->Tail = obj->Head;
      obj->IsinitialAlloc = TRUE;
   }
   else
   {
      obj->Tail->next = temp;
      obj->Tail = temp;
   }
}
int getsize(TYPE type,int len,void *data)
{
   int ret = 0;
  // printf("getsize::length:%d\n",strlen((char *)data));
   switch(type)
   {
      case INT: ret = 4;
         break;
      case STR:ret = strlen((char *)data);
        // printf("getsize::ret:%d\n",len);
         break;
      default : ret =1;
         break;
   }
   return ret;
}
int AddMember2Tuple(Tuple *obj,TYPE types,...)
{
   va_list valist;
   int i;
   int var;
   va_start(valist, types);
   int count = 0;
   while (types != END)
   {
       switch (types)
       {
           case STR:
               //fprintf(stdout, "arg[%d]: %s\n", count, va_arg(valist, char *));
               Create_Entry(obj,types,(void *)va_arg(valist, char *));
              //printf("va_arg(valist, char *):%d\n",strlen(va_arg(valist, char *)));
               break;
           case INT:
              var = va_arg(valist, int);
               //fprintf(stdout, "arg[%d]: %d\n", count, var);
                Create_Entry(obj,types,(void *)&var);
               break;
           case FLOAT:
              // fprintf(stdout, "arg[%d]: %f\n", count, va_arg(valist, double));
               break;
           default:
               fprintf(stderr, "unknown type specifier\n");
               break;
       }
       types = va_arg(valist, TYPE);
       count += 1;
   }
   va_end(valist);
   obj->len += count;
}
int len(Tuple *obj)
{
   return obj->len;
}
void show(Tuple *obj)
{
   int i;
   TupleNode *temp;
   if(0 == obj->len)
   {
      printf("Entry Tuple");
      return;
   }
   else
   {
      temp = obj->Head;
      for( i= 0;i < obj->len;i++)
      {

         if(STR == temp->type)
         {
            printf("%s ",(char *)temp->p);
         }
         else if(INT == temp->type)
         {
            int val = *((int *)temp->p);
            printf("%d ",val);
          }
         if(NULL != temp->next)
         temp = temp->next;
      }
   }
   printf("\n");
}
int main()
{
   Tuple obj;
   memset(&obj,0,sizeof(obj));
   //AddMember2Tuple(&obj,INT,5,INT,10,END);
   AddMember2Tuple(&obj,STR,"Deba",INT,5,INT,10,END);
   AddMember2Tuple(&obj,STR,"Done",INT,1,INT,5,END);
   //printf("length:%d\n",len(obj));
   show(&obj);
   printf("length :%d",len(&obj));
   return 0;
}


