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
  Node * new = createNode(data);

  if(list->head) {
    list->head->prev = new;
    new->next = list->head;
    list->head = new;
  } else {
    list->head = new;
    list->tail = new;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * new = createNode(data);
  Node * current = list->current;

  if(current == list->tail) {
    new->prev = current;
    current->next = new;
    list->tail = new;
  } else {
    new->prev = current;
    new->next = current->next;
    current->next = new;
  }
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

  if(current == list->head) {
    list->head = current->next;
    current->next->prev = NULL;
    current = current->next;
  }
  
  if(current == list->tail) {
    list->tail = current->prev;
    current->prev->next = NULL;
    current = list->tail;
  }

  current->prev->next = current->next;
  current->next->prev = current->prev;
  current = current->next;

  free(current);
  return current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}