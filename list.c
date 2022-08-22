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
  Node * current = list->current;
  
  if(!current) return NULL;

  if(!current->prev) {
    list->head = current->next;
    list->head->prev = NULL;
  } else if(!current->next) {
    list->tail = current->prev;
    list->tail->next = NULL;
  } else {
      current->prev->next = current->next;
      current->next->prev = current->prev;
  }
  
  current = current->next;
  free(current);
  return current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}