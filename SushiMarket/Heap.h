/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Heap.h
 * Author: chrisrk192
 *
 * Created on October 6, 2016, 11:48 AM
 */

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

template <class T>
class Heap
{
public:
  Heap(unsigned long n)
  {
    siz = n;
    elements = new T[siz];
    last = -1;
  }

  ~Heap()
  {
    delete []elements;
  }

  void add(T x)
  {
#   ifdef DEBUG
      cout << "adding " << x << " of priority " << x.priority() << endl;
#   endif
    int child, parent;
    child = ++last;
    for (;;) {
      parent = child == 0? -1 : (child - 1)/2;
      if (parent < 0 || elements[parent].priority() >= x.priority()) break;
      elements[child] = elements[parent];
      child = parent;
    }
    elements[child] = x;
  }

  T remove()
  {
    int parent, child;
    T the_top = elements[0];
    last--;
    parent = 0;
    for (;;) {
      child = 2*parent + 1;
      if (child < last &&
          elements[child + 1].priority() > elements[child].priority()) child++;
      if (child > last || elements[last+1].priority() > elements[child].priority())  break;
      elements[parent] = elements[child];
      parent = child;
    }
    elements[parent] = elements[last+1];
    return the_top;
  }

  int empty() { return last < 0; }

private:
  T *elements;
  int siz;
  int last;
};

#endif /* HEAP_H */

