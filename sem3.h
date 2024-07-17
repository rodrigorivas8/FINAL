#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct node {
    int val;
    node* prev=nullptr;
    node* next=nullptr;
    node* child=nullptr;
    node(int v):val(v){}
    friend ostream& operator<<(ostream& os,node* n){
        os<<'[';
        while(n){
            os<<n->val;
            n=n->next;
            if(n) os<<',';
        }
        return os<<']';
    }
};

struct func{
    node* flat(node* n){
        if(!n) return n;
        if(!n->next && !n->child) return n;
        if(!n->child) return flat(n->next);
        auto tail=flat(n->child);
        tail->next=n->next;
        if(n->next) n->next->prev=tail;
        n->next=n->child;
        n->child->prev=n;
        n->child=nullptr;
        return flat(tail);
    }

    node* flatten(node* head) {
        if(head) flat(head);
        return head;
    }
};

class LRUCache {
    struct node{
        int key;
        int val;
        node* next=nullptr,
            * prev=nullptr;
        node(int k,int v):key(k),val(v){}
    };
    int cap;
    node* head=nullptr;
    vector<node*> map;

public:
    LRUCache(int capacity) {
        cap=capacity;
        map.resize(cap*2);
        fill(map.begin(),map.end(),nullptr);
    }
    int get(int key) {
        auto& item=map[key%map.size()];
        cout<<'('<<item->key<<')';
        if(!item || item->key!=key) return -1;
        item->next->prev=item->prev;
        item->prev->next=item->next;
        item->prev=head->prev;
        item->next=head;
        head->prev->next=item;
        head->prev=item;
        head=item;
        return head->val;
    }
    void put(int key, int value) {
        auto& item=map[key%map.size()];
        if(!head){
            head=new node(key,value);
            head->next=head;
            head->prev=head;
            item=head;
            cap--;
            return;
        }
        if(item && item->key==key){
            item->val=value;
            if(item->next==item) return;
            item->next->prev=item->prev;
            item->prev->next=item->next;
            item->prev=head->prev;
            item->next=head;
            head->prev->next=item;
            head->prev=item;
            head=item;
            return;
        }
        if(!cap){
            head=head->prev;
            head->key=key;
            head->val=value;
            item=head;
            return;
        }
        cap--;
        item=new node(key,value);
        head->prev->next=item;
        head->prev=item;
        head=item;
    }
};

class BrowserHistory {
    struct page{
        string url;
        page* next=nullptr,
                * prev=nullptr;
        page(string u):url(u){};
    };
    page* home=nullptr;
public:
    BrowserHistory(string homepage) {
        home=new page(homepage);
    }
    void visit(string url) {
        auto aux=home->next;
        while(aux){
            auto tmp=aux;
            aux=aux->next;
            delete tmp;
        }
        aux=new page(url);
        home->next=aux;
        aux->prev=home;
        home=aux;
    }
    string back(int steps) {
        while(steps-- && home->prev)
            home=home->prev;
        return home->url;
    }
    string forward(int steps) {
        while(steps-- && home->next)
            home=home->next;
        return home->url;
    }
};