#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * l = (List *) malloc(sizeof(List));

    l->head = NULL;
    l->tail = NULL;
    l->current = NULL;

    return l;
}

void * firstList(List * list) {
  if(!list->head) return NULL;
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if(!list->current || !list->current->next) return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(!list->current || !list->tail) return NULL;
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if(!list->current || !list->current->prev) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * nuevo = createNode(data);

  if(list->head) {
    list->head->prev = nuevo;
    nuevo->next = list->head;
    list->head = nuevo;
  } else {
    list->head = nuevo;
    list->tail = nuevo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node * current = list->current;
  Node * head = list->head;
  
  if(!current || !head) return NULL;

  if(head == current) {
    current->next->prev = NULL;
    head = current->next;
  }
  
  current->prev->next = list->current->next;
  current->next->prev = list->current->prev;

  return current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}