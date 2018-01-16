/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Queue.h
 * Author: chrisrk192
 *
 * Created on October 5, 2016, 12:34 PM
 */
#include <iostream>
#ifndef QUEUE_H
#define QUEUE_H
template <class T>
class Queue{
public:
    Queue(unsigned long n){
        size = n;
        top = 0;
        bottom = 0;
        amount = 0;
        elements = new T[size]; 
        for(int i = 0; i < size; i++){
            T a;
            elements[i] = a;
        }
    }
    
    ~Queue(){
        delete []elements;
    }
    
    bool isEmpty(){
        return top == bottom && elements[top].GetType() == -1;
    }
    
    bool isFull(){
        return top == bottom && elements[top].GetType() != -1;
    }
    
    void push(T x){
        if(!isFull()){
            //Filter by priority
            amount++;
            int temp = top;
            elements[top] = x;
            while (temp != bottom){
                if(temp > 0){
                    if(elements[temp].priority() < elements[temp - 1].priority() && !elements[temp - 1].absPriority()){
                        switchEm(&elements[temp], &elements[temp -1]);
                        temp--;
                    } else break;
                } else {//temp == 0 and size-1 because array size = 2 means spots 0 and 1
                    if(elements[temp].priority() < elements[size -1].priority() && !elements[size - 1].absPriority()){
                        switchEm(&elements[temp], &elements[size -1]);
                        temp = size -1;
                    } else break;
                }
                    
            }
            top = (top + 1) % size;
        }
        return;
    }
    
    void switchEm(T *a, T *b){
        T temp = *a;
        *a = *b;
        *b = temp;
        return;
    }
   
    T pop(){
        T temp1;
        if(!isEmpty()){
            T temp;
            amount--;
            temp = elements[bottom];
            T blank;
            //"nullify the object"
            elements[bottom] = blank;
            bottom = (bottom + 1) % size;
            return temp;
           
        } else{
            T blank;
            return blank;
        }
        
        //return temp1;
    }
    
    T peek(){
        return elements[bottom];
    }
    
    int getAmt(){
        return amount;
    }
    
    void printEm(){
        std::cout << "Amount : " << amount << std::endl;
        for(int i = 0; i < size; i++){
            if(i == bottom && i == top)
                std::cout << i << " : " << elements[i].priority() << " has " << elements[i].GetItems() << " TB" << std::endl;
            else if(i == bottom)
                std::cout << i << " : " << elements[i].priority() << " has " << elements[i].GetItems() << "  B" << std::endl;
            else if(i == top)
                std::cout << i << " : " << elements[i].priority() << " has " << elements[i].GetItems() << " T" << std::endl;
            else
                std::cout << i << " : " << elements[i].priority() << " has " << elements[i].GetItems() << std::endl;
        }
        std::cout << std::endl;
        return ;
    }
    
private:
        int size;
        T *elements;
        int top;
        int bottom;
        int amount;
        
};


#endif /* QUEUE_H */

