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
    List* lista = (List *)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    while(list->current->next != NULL){
        list->current = list->current->next;
    }
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* nuevo = createNode(data);
    if(list->head == NULL){
        list->head = nuevo;
        list->tail = nuevo;
    }
    else{
        list->current = list->head;
        nuevo->next = list->current;
        list->current->prev = nuevo;
        list->head = nuevo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* nuevo = createNode(data);
    if(list->current->next == NULL){
        list->current->next = nuevo;
        nuevo->prev = list->current;
        list->tail = nuevo;
    }
    else{
        Node* auxIzq = list->current;
        Node* auxDer = list->current->next;
        nuevo->prev = auxIzq;
        nuevo->next= auxDer;
        auxDer->prev = nuevo;
        auxIzq->next = nuevo;
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
    void* aux = list->current->data;
    if(list->current->next == NULL){
        free(list->current);
        list->current = NULL;
    }
    else{
        Node* auxIzq = list->current->prev;
        Node* auxDer = list->current->next;
        auxIzq->next = auxDer;
        auxDer->prev = auxIzq;
        free(list->current);
        list->current = auxDer;
    }
    return aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}