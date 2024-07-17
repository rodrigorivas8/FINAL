#include <iostream>
using namespace std;

template <class type>
class forward_list{
    struct node{
        type key;
        node* next=nullptr;

        node()=default;
        explicit node(type k):key(k){}
        node(type k,node* n):key(k),next(n){}

        void push_back(type k){
            if(!next) next=new node(k);
            else next->push_back(k);
        }

        type sort(node* n){
            if(this==n) return key;
            auto k=next->sort(n);
            if(k<key){
                next->key=key;
                key=k;
            } return key;
        }
    };
    node* head=nullptr;
    type null;

public:

    void sort(){
        if(!head) return;
        auto aux=head->next;
        while(aux){
            head->sort(aux);
            aux=aux->next;
        }
    }

    void insert(type k,int i){
        if(i==0) push_front(k);
        if(!i) return;

        auto aux=head;
        while(aux && --i)
            aux=aux->next;
        if(!aux || i) return;

        auto item=new node(k);
        item->next=aux->next;
        aux->next=item;
    }

    void remove(int i){
        if(!head || i<0) return;
        if(i==0){
            auto aux=head;
            head=head->next;
            delete aux;
            return;
        }

        auto aux=head;
        while(aux && --i)
            aux=aux->next;
        if(!aux || !aux->next || i) return;

        auto tmp=aux->next;
        aux->next=tmp->next;
        delete tmp;
    }

    type operator[](int i){
        auto aux=head;
        while(aux && i--)
            aux=aux->next;
        if(!aux || i>=0) return null;
        return aux->key;
    }

    void push_front(type k){
        auto aux=new node(k,head);
        head=aux;
    }

    void push_back(type k){
        if(!head) head=new node(k);
        else head->push_back(k);
    }

    type pop_front(){
        if(!head) return null;
        auto tmp=head;
        auto k=tmp->key;
        head=head->next;
        delete tmp;
        return k;
    }

    type pop_back(){
        if(!head) return null;
        if(!head->next){
            auto k=head->key;
            delete head;
            head=nullptr;
            return k;
        }
        auto aux=head;
        while(aux->next->next)
            aux=aux->next;
        auto tmp=aux->next;
        auto k=tmp->key;
        aux->next=tmp->next;
        delete tmp;
        return k;
    }

    bool empty(){
        return !head;
    }

    int size(){
        int i=0;
        auto aux=head;
        while(aux && ++i)
            aux=aux->next;
        return i;
    }

    void clear(){
        while(head){
            auto tmp=head;
            head=head->next;
            delete tmp;
        }
    }

    node*& reverse(node* n){
        if(!n->next) head=n;
        else reverse(n->next)=n;
        return n->next;
    }

    void reverse(){
        reverse(head)=nullptr;
    }

    friend ostream& operator<<(ostream& os,forward_list l){
        auto aux=l.head;
        os<<'[';
        while(aux){
            os<<aux->key;
            aux=aux->next;
            if(aux) os<<',';
        }
        return os<<']';
    }

};