#include <iostream>
using namespace std;

template <class type>
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

    friend ostream& operator<<(ostream& os,node* aux){
        os<<'[';
        while(aux){
            os<<aux->key;
            aux=aux->next;
            if(aux) os<<',';
        }
        return os<<']';
    }
};

template <class type>
struct forward_list{

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

    type front(){
        if(!head) return null;
        return head->key;
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

    node* middle(){
        if(!head) return {};
        auto one=head,
             two=head;
        bool mod=true;
        while(one){
            mod=!mod;
            one=one->next;
            if(mod)
                two=two->next;
        }
        return two;
    }

    node* merge(node* h2){
        if(!h2) return head;
        auto h1=head;
        if(h2->key<h1->key){
            head=h2;
            h2=h2->next;
            head->next=h1;
            h1=head;
        }
        while(h2){
            if(!h1->next){
                h1->next=h2;
                break;
            }
            if(h2->key<h1->next->key){
                auto tmp=h2->next;
                h2->next=h1->next;
                h1->next=h2;
                h2=tmp;
            }else h1=h1->next;
        }
        return head;
    }

};

struct func{
    static int bin(forward_list<int> l){
        double s=0,r=64;
        while(!l.empty()){
            r/=2;
            s+=l.pop_front()*r;
        } return int(s/r);
    }

    int middle(forward_list<int> l){
        return l.middle()->key;
    }

    node<int>* merge(node<int>* h1,node<int>* h2){
        if(!h1) return h2;
        if(!h2) return h1;
        if(h1->key<h2->key){
            h1->next=merge(h1->next,h2);
            return h1;
        }
        h2->next=merge(h1,h2->next);
        return h2;
    }

    bool cicle(node<int>* head){
        if(!head) return false;
        auto one=head,
             two=head;
        bool mod=true;
        while(one){
            mod=!mod;
            one=one->next;
            if(mod) two=two->next;
            if(one==two) return true;
        }
        return false;
    };

    node<int>* erase(node<int>* n,int x){
        if(!n) return n;
        if(n->key==x){
            auto tmp=n;
            n=n->next;
            delete tmp;
            return erase(n,x);
        }
        n->next=erase(n->next,x);
        return n;
    }

    int mcd(int a,int b){
        for(int i=min(a,b);i>=1;i--)
            if(!(a%i || b%i))
                return i;
        return 1;
    }

    node<int>* expand(node<int>* n){
        if(!n) return n;
        if(!n->next) return n;
        int k=mcd(n->key,n->next->key);
        n->next=new node(k,expand(n->next));
        return n;
    }

    node<int>* flip2(node<int>* n){
        if(!n || !n->next) return n;
        auto tmp=n->next;
        n->next=flip2(tmp->next);
        tmp->next=n;
        return tmp;
    }
};