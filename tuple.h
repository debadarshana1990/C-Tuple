/*
 * tuple.h
 *
 *  Created on: 26-May-2021
 *      Author: Debadarshana Parida
 */

#ifndef TUPLE_H_
#define TUPLE_H_
typedef enum TYPE
{
   INT = 0,
   STR,
   FLOAT,
   TUPLE,
   END
}TYPE;

#define TRUE   1
#define FALSE  0
typedef char   boolean;
typedef struct TupleNode
{
   TYPE type;
   void *p;
   struct TupleNode *next;
}TupleNode;
/* creating a class for tuple */
typedef struct Tuple
{
   int len;
   boolean IsinitialAlloc;
   TupleNode *Head;
   TupleNode *Tail;
}Tuple;
int AddMember2Tuple(Tuple *obj,TYPE types,...);
int getsize(TYPE type,int len,void *data);
void Create_Entry(Tuple *obj,TYPE type,void *data);
int len(Tuple *obj);
void show(Tuple *obj);

#endif /* TUPLE_H_ */
