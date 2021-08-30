/* Copyright 2016 The MathWorks, Inc. */

#ifndef LISTUTIL_H
#define LISTUTIL_H

#include <stdlib.h>
#include <malloc.h>

struct ListNode_T{
   void  *ListItem;
   struct ListNode_T *Next;
};
typedef struct ListNode_T ListNode;

typedef struct {
   ListNode *Iterator;
   ListNode *Head;
}List;

#define  DEFINE_LIST(N)       static List  LinkedList ## N ;
#define  LIST(N)              &( LinkedList ## N )

static void* ITERATE_LIST(List* l)
{
   ListNode *current = l->Iterator;
   if(current!=NULL){
      current = l->Iterator = current->Next;
      if(current!=NULL){ 
         return current->ListItem;
      }
   }    
   return NULL;
}

static void* BEGIN_LIST(List* l){
   List *current = l;
   l->Iterator = l->Head;
   return l->Head->ListItem;
}

static void ADD_LISTITEM(List* l, void* item)
{
  ListNode *tmp  = l->Head;     
  ListNode *prev = NULL;
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->ListItem = (void*)item;
  node->Next     = NULL;
  while(tmp!=NULL) {
     prev=tmp;
     tmp=tmp->Next;
  }
  if(prev==NULL)   {
     l->Head = node;
  }
  else{
     prev->Next = node;
  }
}

static int DELETE_LISTITEM(List* l, void* item)
{
   ListNode *tmp  = l->Head;
   ListNode *prev = NULL; 
   while(tmp!=NULL) {
      if(tmp->ListItem == item) {
         break;
      }
      else {
         prev=tmp;tmp=tmp->Next;
      }
   }
   if(tmp!=NULL){
      if(prev!=NULL){
         prev->Next=tmp->Next;
      }
      else{
         l->Head = tmp->Next;
      }
      free(tmp);
      return 1;
   }else{
      return 0;
   }
}

typedef int (*ListItemCompareFcn)(void*,void*);

static void* FIND_LISTITEM(List* l, ListItemCompareFcn fcn, void* param)
{
   ListNode *tmp  = l->Head;
   ListNode *prev = NULL; 
   while(tmp!=NULL) {
      if(fcn(tmp->ListItem,param)) {
         return tmp->ListItem;
      }
      tmp = tmp->Next;
   }
   return NULL;
}

#endif 