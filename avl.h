#include <iostream>
#include "queue.h"
#include "stack.h"
using namespace std;

template <class type>
class avl{
    struct node{
        type key;
        node* left=nullptr,
            * right=nullptr;
        int height=1;
        node()=default;
        node(type k):key(k){}
        node(type k,int h):key(k),height(h){}
    };
    node* root=nullptr;

    int height(node* aux){
        if(!aux) return 0;
        return aux->height;
    }

    int factor(node* aux){
        if(!aux) return 0;
        int lh=height(aux->left),
            rh=height(aux->right);
        return lh-rh;
    }

    node* update(node* aux){
        if(!aux) return aux;
        int lh=height(aux->left),
            rh=height(aux->right);
        aux->height=std::max(lh,rh)+1;
        return aux;
    }

    node* lturn(node* aux){
        auto tmp=aux->right;
        aux->right=tmp->left;
        tmp->left=update(aux);
        return update(tmp);
    }

    node* rturn(node* aux){
        auto tmp=aux->left;
        aux->left=tmp->right;
        tmp->right=update(aux);
        return update(tmp);
    }

    node* balance(node* aux){
        if(!aux) return aux;
        int f=factor(aux);
        if(f>1){
            auto& l=aux->left;
            if(factor(l)==-1)
                l=lturn(l);
            return rturn(aux);
        }else if(f<-1){
            auto& r=aux->right;
            if(factor(r)==1)
                r=rturn(r);
            return lturn(aux);
        }return update(aux);
    }

    node*& max(node*& aux){
        if(!aux) return aux;
        if(!aux->right) return aux;
        return max(aux->right);
    }

    node*& min(node*& aux){
        if(!aux) return aux;
        if(!aux->left) return aux;
        return max(aux->left);
    }

    node*& substitute(node*& aux){
        if(!aux) return aux;
        if(aux->left)
            return max(aux->left);  // predecessor
        return min(aux->right);     // successor
    }

    node*& find(type k,node*& aux){
        if(!aux || k==aux->key) return aux;
        if(k<aux->key) return find(k,aux->left);
        return find(k,aux->right);
    }

    node* insert(type k,node* aux){
        if(!aux) return new node(k);
        if(k<aux->key) aux->left=insert(k,aux->left);
        else aux->right=insert(k,aux->right);
        return balance(aux);
    }

    void remove(type k,node*& aux){
        if(!aux) return;
        if(k<aux->key) remove(k,aux->left);
        else if(k>aux->key) remove(k,aux->right);
        if(k!=aux->key){update(aux);return;}
        auto sub=substitute(aux);
        if(sub){
            k=sub->key;
            remove(k,aux);
            aux->key=k;
        }else{
            auto tmp=aux;
            aux=nullptr;
            delete tmp;
        }
    }

public:

    bool find(type k){
        return find(k,root);
    }

    void insert(type k){
        root=insert(k,root);
    }

    void remove(type k){
        remove(k,root);
    }

    void bfs(){
        queue<node*> q0;
        q0.enqueue(root);
        int p=1,i=-1;
        while(!q0.empty()){
            if(p==++i){
                p*=2;
                i=0;
                cout<<endl;
            }
            auto aux=q0.dequeue();
            if(!aux){
                cout<<"x ";
                continue;
            }
            q0.enqueue(aux->left);
            q0.enqueue(aux->right);
            cout<<aux->key<<' ';
        }   cout<<endl;
    }
    void dfs(){
        stack<node*> s0;
        s0.push(root);
        while(!s0.empty()){
            auto aux=s0.pop();
            if(!aux) continue;
            s0.push(aux->right);
            s0.push(aux->left);
            cout<<aux->key<<' ';
        }   cout<<endl;
    }

};