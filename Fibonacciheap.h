//
// Created by dania on 11.11.2023.
//

#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H


#include <iostream>
#include <vector>
#include <string>

struct Node {
private:
    Node* prev;
    Node* next;
    Node* child;
    Node* parent;
    long value;
    long degree;
    bool marked;
protected:
    friend class FibonacciHeap;
};



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



class FibonacciHeap {
protected:
    Node* heap;
public:
    //Constructors
    FibonacciHeap();
    FibonacciHeap(FibonacciHeap& heap);
    FibonacciHeap(FibonacciHeap& heap1,FibonacciHeap& heap2);
    //Destructors
    ~FibonacciHeap();
    //insert element to heap, O(1)
    Node* insert(long value);
    //merge two Fibonacci Heap, O(1)
    void merge(FibonacciHeap& other);
    //check for empty of heap
    bool isEmpty();
    //get top of heap without delete
    long getMinimum();
    //extract top, O(1)
    std::string removeMinimum();
    //decreaseKey of Node, O(1)
    void decreaseKey(Node* n,long value);
    //find element with that value, O(n)
    Node* find(long value);
    //copy element of another_heap
    Node* copy(FibonacciHeap& original_heap);
private:
    Node* _empty();
    Node* _singleton(long value);
    Node* _merge(Node* a,Node* b);
    void _deleteAll(Node* n);
    void _addChild(Node* parent,Node* child);
    void _unMarkAndUnParentAll(Node* n);
    Node* _extractMin(Node* n);
    Node* _cut(Node* heap,Node* n);
    Node* _decreaseKey(Node* heap,Node* n,long value);
    Node* _find(Node* heap,long value);
    Node* _copy(FibonacciHeap& original_heap);
    Node* _copy_child(Node* parent, Node* original_child);
    void _copy_next(Node* original_start_of_layer, Node* original_next_of_layer,Node* copy_start_of_layer, Node* copy_next_prev);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//Constructors and Destructors
FibonacciHeap::FibonacciHeap(){
    heap=_empty();
}
FibonacciHeap::FibonacciHeap(FibonacciHeap& original) {
    this->heap= _copy(original);
}
FibonacciHeap::FibonacciHeap(FibonacciHeap& heap1,FibonacciHeap& heap2){
    Node* first=_copy( heap1);
    Node* second= _copy(heap2);
    this->heap= _merge(first,second);
}
FibonacciHeap::~FibonacciHeap(){
    if(heap) {
        _deleteAll(heap);
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//Method
Node* FibonacciHeap::insert(long value) {
    Node* ret=_singleton(value);
    heap=_merge(heap,ret);
    return ret;
}
void FibonacciHeap::merge(FibonacciHeap &other)  {
    heap=_merge(heap,other.heap);
    other.heap=_empty();
}
bool FibonacciHeap::isEmpty() {
    return heap==NULL;
}
long FibonacciHeap::getMinimum() {
    return heap->value;
}
std::string FibonacciHeap::removeMinimum() {
    if(heap){
        Node* old=heap;
        heap=_extractMin(heap);
        long ret=old->value;
        delete old;
        return std::to_string(ret);
    }
    else return "*";
}
void FibonacciHeap::decreaseKey(Node *n, long value){
    if(n!= nullptr)
        heap=_decreaseKey(heap,n,value);
}
Node* FibonacciHeap::find(long value) {
    return _find(heap,value);
}
Node* FibonacciHeap::copy(FibonacciHeap &original_heap) {

}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




//Private Method
Node *FibonacciHeap::_empty(){
    return NULL;
}
Node *FibonacciHeap::_singleton(long value){
    Node* n=new Node;
    n->value=value;
    n->prev=n->next=n;
    n->degree=0;
    n->marked=false;
    n->child=NULL;
    n->parent=NULL;
    return n;
}
Node *FibonacciHeap::_merge(Node *a, Node *b){
    if(a==NULL)return b;
    if(b==NULL)return a;
    if(a->value>b->value) {
        Node* temp=a;
        a=b;
        b=temp;
    }
    Node* an=a->next;
    Node* bp=b->prev;
    a->next=b;
    b->prev=a;
    an->prev=bp;
    bp->next=an;
    return a;
}
void FibonacciHeap::_deleteAll(Node *n) {
    if(n!=NULL) {
        Node* c=n;
        do {
            Node* d=c;
            c=c->next;
            _deleteAll(d->child);
            delete d;
        } while(c!=n);
    }
}
void FibonacciHeap::_addChild(Node *parent, Node *child){
    child->prev=child->next=child;
    child->parent=parent;
    parent->degree++;
    parent->child=_merge(parent->child,child);
}
void FibonacciHeap::_unMarkAndUnParentAll(Node *n){
    if(n==NULL)return;
    Node* c=n;
    do {
        c->marked=false;
        c->parent=NULL;
        c=c->next;
    }while(c!=n);
}
Node *FibonacciHeap::_extractMin(Node *n) {
    _unMarkAndUnParentAll(n->child);
    if(n->next==n) {
        n=n->child;
    } else {
        n->next->prev=n->prev;
        n->prev->next=n->next;
        n=_merge(n->next,n->child);
    }
    if(n==NULL)return n;
    Node* trees[64]={NULL};

    while(true) {
        if(trees[n->degree]!=NULL) {
            Node* t=trees[n->degree];
            if(t==n)break;
            trees[n->degree]=NULL;
            if(n->value<t->value) {
                t->prev->next=t->next;
                t->next->prev=t->prev;
                _addChild(n,t);
            } else {
                t->prev->next=t->next;
                t->next->prev=t->prev;
                if(n->next==n) {
                    t->next=t->prev=t;
                    _addChild(t,n);
                    n=t;
                } else {
                    n->prev->next=t;
                    n->next->prev=t;
                    t->next=n->next;
                    t->prev=n->prev;
                    _addChild(t,n);
                    n=t;
                }
            }
            continue;
        } else {
            trees[n->degree]=n;
        }
        n=n->next;
    }
    Node* min=n;
    Node* start=n;
    do {
        if(n->value<min->value)min=n;
        n=n->next;
    } while(n!=start);
    return min;
}
Node *FibonacciHeap::_cut(Node *heap, Node *n){
    if(n->next==n) {
        n->parent->child=NULL;
    } else {
        n->next->prev=n->prev;
        n->prev->next=n->next;
        n->parent->child=n->next;
    }
    n->next=n->prev=n;
    n->marked=false;
    return _merge(heap,n);
}
Node *FibonacciHeap::_decreaseKey(Node *heap, Node *n, long value){
    if(n->value<value)return heap;
    n->value=value;
    if(n->parent) {
        if(n->value<n->parent->value) {
            heap=_cut(heap,n);
            Node* parent=n->parent;
            n->parent=NULL;
            while(parent!=NULL && parent->marked) {
                heap=_cut(heap,parent);
                n=parent;
                parent=n->parent;
                n->parent=NULL;
            }
            if(parent!=NULL && parent->parent!=NULL)parent->marked=true;
        }
    } else {
        if(n->value < heap->value) {
            heap = n;
        }
    }
    return heap;
}
Node *FibonacciHeap::_find(Node *heap, long value){
    Node* n=heap;
    if(n==NULL)return NULL;
    do {
        if(n->value==value)return n;
        Node* ret=_find(n->child,value);
        if(ret)return ret;
        n=n->next;
    }while(n!=heap);
    return NULL;
}
Node* FibonacciHeap::_copy(FibonacciHeap& original_heap){
    Node* copy_of_heap = nullptr;
    if (original_heap.heap) {
        copy_of_heap=new Node;
        //копируем начало кучи
        copy_of_heap->value = original_heap.heap->value;
        copy_of_heap->degree = original_heap.heap->degree;
        copy_of_heap->marked = original_heap.heap->marked;
        //Из понимания
        copy_of_heap->parent = NULL;
        //Рекурсия в ход
        copy_of_heap->child = _copy_child(copy_of_heap, original_heap.heap->child);
        _copy_next(original_heap.heap, original_heap.heap->next,copy_of_heap,copy_of_heap);

    }
    return copy_of_heap;
}
Node *FibonacciHeap::_copy_child(Node *parent, Node *original_child){
    if (original_child== nullptr)
        return nullptr;

    Node* new_child = new Node; // Создаем новый узел
    new_child->value = original_child->value;
    new_child->degree = original_child->degree;
    new_child->marked = original_child->marked;
    new_child->parent = parent; // Устанавливаем родителя нового узла
    // Копируем первого ребенка
    new_child->child = _copy_child(new_child, original_child->child);
    // Копируем следующие узлы на этом же уровне
    _copy_next(original_child,original_child->next,new_child,new_child);

    return new_child;
}
void FibonacciHeap::_copy_next(Node *original_start_of_layer, Node *original_next_of_layer, Node *copy_start_of_layer,Node *copy_next_prev){
    if(original_start_of_layer==original_next_of_layer){
        copy_next_prev->next=copy_start_of_layer;
        copy_start_of_layer->prev=copy_next_prev;
        return;
    }
    Node* new_next=new Node;
    //копируем данные
    new_next->value=original_next_of_layer->value;
    new_next->marked=original_next_of_layer->marked;
    new_next->degree=original_next_of_layer->degree;
    //остовляем того же предка
    new_next->parent=copy_next_prev->parent;
    //связываем две Node
    new_next->prev=copy_next_prev;
    copy_next_prev->next=new_next;
    //рекурсия
    new_next->child= _copy_child(new_next, original_next_of_layer->child);
    _copy_next(original_start_of_layer,original_next_of_layer->next,copy_start_of_layer,new_next);
}





#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
