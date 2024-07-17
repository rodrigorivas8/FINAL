#include "queue.h"
#include "stack.h"
class MyStack {
    queue<int> q0;
public:
    MyStack() {
    }
    void push(int x) {
        q0.enqueue(x);
    }
    int pop() {
        queue<int> aux;
        int k=q0.dequeue();
        while(!empty()){
            aux.enqueue(k);
            k=q0.dequeue();
        }
        q0=aux;
        return k;
    }
    int top() {
        queue<int> aux;
        int k;
        while(!empty()){
            k=q0.dequeue();
            aux.enqueue(k);
        }
        q0=aux;
        return k;
    }
    bool empty() {
        return q0.empty();
    }
};

class MyCircularDeque {
    vector<int> list;
    int cap;
public:
    MyCircularDeque(int k) {
        cap=k;
    }
    bool insertFront(int value) {
        if(isFull()) return false;
        list.insert(list.begin(),value);
        return true;
    }
    bool insertLast(int value) {
        if(isFull()) return false;
        list.push_back(value);
        return true;
    }
    bool deleteFront() {
        if(isEmpty()) return false;
        list.erase(list.begin());
        return true;
    }
    bool deleteLast() {
        if(isEmpty()) return false;
        list.pop_back();
        return true;
    }
    int getFront() {
        if(isEmpty()) return -1;
        return list[0];
    }
    int getRear() {
        if(isEmpty()) return -1;
        return list.back();
    }
    bool isEmpty() {
        return list.empty();
    }
    bool isFull() {
        return list.size()==cap;
    }
};

class MinStack {
    struct node{
        int min;
        int val;
        node(int m,int v)
        {min=m;val=v;}
    };
    vector<node> list;
public:
    void push(int val) {
        node n(getMin(),val);
        if(val<n.min) n.min=val;
        list.push_back(n);
    }
    void pop() {
        if(list.empty()) return;
        list.pop_back();
    }
    int top() {
        if(list.empty()) return -1;
        return list.back().val;
    }
    int getMin() {
        if(list.empty()) return -1;
        return list.back().min;
    }
};

template <class type>
class MyQueue{
    stack<type> s0;
public:
    void enqueue(type k){
        s0.push(k);
    }
    type dequeue(){
        if(empty()) return {};
        stack<type> aux;
        type k=s0.pop();
        while(!empty()){
            aux.push(k);
            k=s0.pop();
        }
        while(!aux.empty())
            s0.push(aux.pop());
        return k;
    }
    type front(){
        if(empty()) return {};
        stack<type> aux;
        type k;
        while(!empty()){
            k=s0.pop();
            aux.push(k);
        }
        while(!aux.empty())
            s0.push(aux.pop());
        return k;
    }
    bool empty(){
        return s0.empty();
    }
};

struct func{
    int depth(string s){
        int d=0,i=0;
        for(char c:s){
            if(c=='(') i++;
            if(c==')') i--;
            d=max(d,i);
        }   return d;
    }
};