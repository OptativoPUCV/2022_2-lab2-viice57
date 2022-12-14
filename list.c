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
    List * list = (List *) malloc(sizeof(List));

    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
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
  Node * newNode = createNode(data);

  if(list->head) {
    list->head->prev = newNode;
    newNode->next = list->head;
  } else {
    list->tail = newNode;
  }
  list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

void pushCurrent(List * list, void * data) {
  Node * new = createNode(data);
  Node * current = list->current;
  
  if(current == list->tail) {
    new->prev = current;
    list->tail = new;
  } else {
    new->prev = current;
    new->next = current->next;
  }
  current->next = new;
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
  void * data = list->current->data;  
  if(!list->current) return NULL;

  if(list->current == list->head) {
    list->current->next->prev = NULL;
    list->head = list->current->next;
  } else if(list->current == list->tail) {
    list->current->prev->next = NULL;
    list->tail = list->current->prev;
  } else {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
  }
  
  //current = current->next;
  free(list->current);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}