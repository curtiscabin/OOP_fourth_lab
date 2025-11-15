#ifndef MYSTORAGE_H
#define MYSTORAGE_H

#endif // MYSTORAGE_H
#include"shapes.h"

class Node{

    Node *next;
    Shape *shape;

    Node():next(nullptr),shape(nullptr){}

    ~Node(){
        if (shape!=nullptr)delete shape;
    }

    friend class MyStorage;


};

class MyStorage {
    Node *head;
    Node *tail;
    Node *current;

public:
    MyStorage() : head(nullptr),tail(nullptr),current(nullptr) {}

    void clear(){
        while (head){
            current = head;
            head = current->next;
            delete current;

        }
        current = nullptr;
        tail = nullptr;
    }

    ~MyStorage(){
        this->clear();
    }

    void add(Shape *shap){

        Node* node = new Node;
        node->shape = shap;
        node->next = head;
        head = node;
        current = node;
        if (!tail) tail = node;

    }

    void first(){
        current = head;
    }

    void next(){
        if (current) current = current->next ;
    }

    bool eol(){
        return current == nullptr;
    }


    Shape *getObject(){
        return current ? current->shape : nullptr;
    }

    int get_size(){
        int count =0;
        for(this->first();!this->eol();this->next()) count++;
        return count;
    }

    void clearSelection (){
        for(this->first();!this->eol();this->next()){
            if(this->getObject()->isSelect_())this->getObject()->ClearSelect();
        }
    }



};
