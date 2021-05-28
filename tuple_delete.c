/*
 * tuple_delete.c
 *
 *  Created on: 28-May-2021
 *      Author: Debadarshana Parida
 */
#include <tuple.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static void FindAndDelete(Tuple *obj,TYPE type,void *data);
static void FreeTupleNode(TupleNode *item);
static boolean isEqual(void *data,void *p);
static boolean isEqual(void *data,void *p)
{
   return TRUE;
}

static void FreeTupleNode(TupleNode *item)
{
   if(NULL == item)
   {
      printf("Error in deleting node\n");
      exit(0);
   }
   free(item->p);
   free(item);
}

static void FindAndDelete(Tuple *obj,TYPE type,void *data)
{
   if(NULL == obj)
   {
      printf("List is empty");
      exit(0);
   }
   /* find the size of the data */
   int DataSize = 1;
   printf("type:%d\n",type);
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
         printf("Unsupported data types to delete.....\n");
         exit(0);
            break;
      }
   // Store head node
      TupleNode *temp = obj->Head, *prev;

      if (temp != NULL)
      {
         // If head node itself holds the key to be deleted
         if(0 == memcmp(temp->p,data,DataSize))
         {
            obj->Head = temp->next; // Changed head
            FreeTupleNode(temp); // free old head
            return;
         }
      }
      // Search for the key to be deleted, keep track of the
      // previous node as we need to change 'prev->next'
      while (temp != NULL && (0 != memcmp(temp->p,data,DataSize)))
      {
          prev = temp;
          temp = temp->next;
      }

      // If key was not present in linked list
      if (temp == NULL)
          return;

      // Unlink the node from linked list
      prev->next = temp->next;

      FreeTupleNode(temp);
}


void TupleRemove(Tuple *obj,TYPE type,...)
{
   va_list vaarg;
   va_start(vaarg, type);
   int item;
   switch(type)
   {
      case INT:
         item = va_arg(vaarg,int);
         FindAndDelete(obj,type,(void *)&item);
         break;
      case STR:
         FindAndDelete(obj,type,(void *)va_arg(vaarg, char *));
         break;
      default : printf("Unsupported Type\n");
         break;

   }

}
