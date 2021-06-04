/*
 * tuple.c
 *
 *  Created on: 26-May-2021
 *      Author: Debadarshana Parida
 */

#include <tuple.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void Create_Entry(Tuple *obj,TYPE type,void *data)
{
   int DataSize = 1;
   /* Traverse to the end */
   TupleNode *temp = (TupleNode *)(malloc(sizeof(TupleNode)));
   if(NULL == temp)
   {
      perror("Not able to add element");
      exit(0);
   }
   temp->next = NULL;
   temp->type = type;
   /* Find the size of data to allocate memory */
   switch(type)
   {
      case INT: DataSize = 4;
         break;
      case STR:DataSize = strlen((char *)data);
         break;
      case FLOAT:DataSize = 4;
         break;
      case DOUBLE:DataSize = 8;
         break;
      case TUPLE:DataSize = sizeof(Tuple);
         break;
      default : DataSize =1;
         printf("Unsupported data types.....\n");
         exit(0);
            break;
      }
   temp->p = malloc(DataSize);
   memcpy(temp->p,data,DataSize);
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
int TupleAdd(Tuple *obj,TYPE types,...)
{
   va_list valist;
   int i;
   int var;
   float fdata;
   double ddata;
   Tuple nest;
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
               fdata = va_arg(valist, double);
//               fprintf(stdout, "arg[%d]: %f\n", count, fdata);
              Create_Entry(obj,types,(void *)&fdata);
               break;
           case DOUBLE:
               ddata = va_arg(valist, double);
//               fprintf(stdout, "arg[%d]: %f\n", count, ddata);
              Create_Entry(obj,types,(void *)&ddata);
               break;
           case TUPLE:
               nest = va_arg(valist, Tuple);
//               fprintf(stdout, "arg[%d]: %f\n", count, ddata);
              Create_Entry(obj,types,(void *)&nest);
               break;
           default:
               fprintf(stderr, "unknown type specifier\n");
               break;
       }
       types = va_arg(valist, TYPE);
//       printf("types :%d\n",types);
       count += 1;
   }
   va_end(valist);
   obj->len += count;
}
int TupleLen(Tuple *obj)
{
   return obj->len;
}
void TupleShow(Tuple *obj)
{
   int i;
   TupleNode *temp;
   if(0 == obj->len)
   {
      printf("Empty Tuple");
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
         else if(FLOAT == temp->type)
         {
            float val = *((float *)temp->p);
            printf("%f ",val);
          }
         else if(DOUBLE == temp->type)
         {
            double val = *((double *)temp->p);
            printf("%lf ",val);
         }
         else if(TUPLE == temp->type)
         {
            TupleShow((Tuple *)temp->p);
         }
         else
         {
            printf("I do not understand the data type\n");
         }
         if(NULL != temp->next)
         temp = temp->next;
      }
   }
   printf("\n");
}

