#include "Stack.h"
#include <iostream>
Stack::Stack(){

    this->buffer = new int[1];
    this->cNoe = 0;
}
Stack::~Stack(){
    delete[] this->buffer;
}
Stack::Stack(const Stack &s){
    this->cNoe = s.cNoe;
    this->buffer = new int(s.cNoe);

    for(int i = 0; i < this->cNoe; i++){

        this->buffer[i] = s.buffer[i];
    }
}
void Stack::push(int value){

    this->buffer[this->cNoe] = value;
    this->addElement();
}
int Stack::pop(){
    if(this->isEmpty()) return -1;

    int retVal = this->buffer[this->cNoe - 1];

    this->removeElement();
    return retVal;
}
int Stack::peek() const{
    if(this->isEmpty()) return -1;
    return this->buffer[this->cNoe - 1];
}

bool Stack::isEmpty() const{
    return (this->cNoe < 1);
}

int Stack::getSize() const{
    return this->cNoe;
}


void Stack::addElement(){
    this->cNoe += 1;
    int* temp = new int[this->cNoe];

    for(int i = 0; i < this->cNoe; i++){

        temp[i] = this->buffer[i];
    }


    this->buffer = new int[this->cNoe + 1];

    for(int i = 0; i < this->cNoe; i++){

        this->buffer[i] = temp[i];
    }

    delete[] temp;
}
void Stack::removeElement(){

    this->cNoe -= 1;

    int* temp = new int[this->cNoe];

    for(int i = 0; i < this->cNoe; i++){

        temp[i] = this->buffer[i];
    }

    this->buffer = new int[this->cNoe + 1];

    for(int i = 0; i < this->cNoe; i++){

        this->buffer[i] = temp[i];
    }

    delete[] temp;
}
