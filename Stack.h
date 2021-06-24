#pragma once

class Stack{

public:
    Stack();
    ~Stack();
    Stack(const Stack &s);

    void push(int value);
    int pop();
    int peek() const;

    bool isEmpty() const;

    int getSize() const;
private:
    int* buffer;
    int cNoe;

    void addElement();
    void removeElement();
};
