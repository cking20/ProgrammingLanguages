/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Box.h
 * Author: chrisrk192
 *
 * Created on October 6, 2016, 11:13 AM
 */
#include <string.h>
#ifndef BOX_H
#define BOX_H
class Box{
public:  
    Box(){
        type = -1;
        items = -1;
        isOpen = false;
        priorityNum = 0;
        strcpy(date, "N/A");
        
    } 
    Box(int newType, int numItems, char dat[]){
        SetType(type);// newType = type;
        SetItems(items);
        isOpen = false;
        SetDate(dat);
        
        
    }
    Box(const Box &p){
        if(this != &p){
            priorityNum = p.priorityNum;
            type = p.type;
            items = p.items;
            isOpen = p.isOpen;
            strcpy(date, p.date);
            
        }
    }
    ~Box(){
        
    }
int priority(){
    return priorityNum;// DATE in int form
}   
bool absPriority(){
    return isOpen;
}
void SetItems(int items) {
    this->items = items;
}
void SetDate(char d[]) {
    strcpy(date, d);
    priorityNum = 0;
    priorityNum = d[4] -'0';//original 1
    priorityNum = priorityNum + (d[3] -'0') * 10;//original 0
    priorityNum = priorityNum + (d[1] -'0') * 100;//orig 4
    priorityNum = priorityNum + (d[0] -'0') * 1000;//orig 3
    priorityNum = priorityNum + (d[9] -'0') * 10000;
    priorityNum = priorityNum + (d[8] -'0') * 100000;
    priorityNum = priorityNum + (d[7] -'0') * 1000000;
    priorityNum = priorityNum + (d[6] -'0') * 10000000;
    
    
    
}

int GetItems() const {
    return items;
}

char * GetDate(){
    return date;
    
}

void SetType(int type) {
    this->type = type;
}

int GetType() const {
    return type;
}
int DecInv(){
    if(!isOpen)
        isOpen = true;
    items--;
        
}
bool isEmpty(){
    return items <= 0;
}
private:
    int priorityNum;
    int type;
    int items;
    bool isOpen;
    char date[11];
   
    
    
};


#endif /* BOX_H */

