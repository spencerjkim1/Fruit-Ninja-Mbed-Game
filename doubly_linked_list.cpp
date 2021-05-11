//=================================================================
// Implementation for DLL module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode -> data = data;
    newNode -> prev = NULL;
    newNode -> next = NULL;
    return newNode;
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int getSize(DLinkedList* dLinkedList){
    int length = 0;
    LLNode* newNode = dLinkedList->head;
        while (newNode)
        {
            length++;
            newNode = newNode->next;
        }
    return length;
}

LLNode* getHead(DLinkedList* dLinkedList){
   return (dLinkedList->head);
}

LLNode* getTail(DLinkedList* dLinkedList){
  return (dLinkedList->tail);
}

LLNode* getNext(LLNode* node){

  return (node->next);
}

LLNode* getPrev(LLNode* node){

  return (node->prev);
}

void* getData(LLNode* node){

  return (node->data);
}
////////////////////////////////////////////////////////////////////////////////////////////
void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }
  LLNode* temp = create_llnode(data);
  prev_node->next = temp;
  temp->prev = prev_node;
  
  if (dLinkedList->tail == prev_node)
      dLinkedList->tail = temp;
   
  return;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }
  LLNode* temp = create_llnode(data);
  next_node->prev = temp;
  temp->next = next_node;

  if (dLinkedList->head == next_node)
      dLinkedList->head = temp;
  return;
}
  

void insertHead(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertBefore(dLinkedList, dLinkedList->head, data);
  }
}
void insertTail(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->tail == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->tail = newNode;
    dLinkedList->head = newNode;
    dLinkedList->size++; 
  }else{
    insertAfter(dLinkedList, dLinkedList->tail, data);
  }
}

void deleteNode(DLinkedList* dLinkedList, LLNode* Node) {
  if (Node == getHead(dLinkedList) && Node == getTail(dLinkedList)) {
    dLinkedList->head = NULL;
    dLinkedList->tail = NULL;
  }
  else if (Node == getHead(dLinkedList)) {
    Node->next->prev = NULL;
    dLinkedList->head = Node->next;
  }
  else if (Node == getTail(dLinkedList)) {
    Node->prev->next = NULL;
    dLinkedList->tail = Node->prev;
  }
  else {
    getPrev(Node)->next = getNext(Node);
    getNext(Node)->prev = getPrev(Node);
  }
  free(Node->data);
  free(Node);
}

void destroyList(DLinkedList* dLinkedList) {
  LLNode* temp= dLinkedList->head;
  LLNode* x = dLinkedList->head;
  while (x) {
        temp = x;
        x = x->next;
        free(temp->data);
        free(temp);
    }
    free(dLinkedList);
}

void reverse(DLinkedList* dLinkedList) {
    LLNode* temp = NULL;
    LLNode* temp1 = dLinkedList->head;
    LLNode* temp2 = dLinkedList->head->next;

    dLinkedList->tail = temp1;
    while (temp1)
    {
        temp1->next = temp;
        temp1->prev = temp2;
        temp = temp1;
        temp1 = temp2;
        if (!temp1)
            break;
        temp2 = temp2->next;
    }
    dLinkedList->head = temp;
    return;
}