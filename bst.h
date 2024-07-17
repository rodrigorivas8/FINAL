#include "queue.h"
#include "stack.h"
#include <iostream>
using namespace std;

template <class type>
class bst{
    struct node{
        type key;
        node* left=nullptr,
            * right=nullptr;
        node()=default;
        node(type k):key(k){}
        node(type k,node* l,node *r)
        {key=k;left=l;right=r;}
    };
    node* root=nullptr;
    node* null=nullptr;

    node*& find(type k,node*& aux){
        if(!aux) return null;
        if(aux->key==k) return aux;
        if(k<aux->key) return find(k,aux->left);
        return find(k,aux->right);
    }
    node* insert(type k,node* aux){
        if(!aux) return new node(k);
        if(k<aux->key) aux->left=insert(k,aux->left);
        else aux->right=insert(k,aux->right);
        return aux;
    }

    void remove(node*& aux){
        if(!aux) return;
        auto& sub=substitute(aux);
        if(!sub){
            auto tmp=aux;
            aux=nullptr;
            delete tmp;
            return;
        }
        aux->key=sub->key;
        remove(sub);
    }

    node*& substitute(node* aux){
        auto& pred=predecessor(aux);
        if(pred) return pred;
        return successor(aux);
    }

    node*& predecessor(node* aux){
        if(!aux->left) return null;
        return max(aux->left);
    }

    node*& successor(node* aux){
        if(!aux->right) return null;
        return min(aux->right);
    }

    node*& max(node*& aux){
        if(!aux->right) return aux;
        return max(aux->right);
    }
    node*& min(node*& aux){
        if(!aux->left) return aux;
        return min(aux->left);
    }
    void inorder(node* aux){
        if(!aux) return;
        inorder(aux->left);
        cout<<aux->key<<' ';
        inorder(aux->right);
    }

public:
    bool find(type k){
        return find(k,root);
    }
    void insert(type k){
        root=insert(k,root);
    }
    void remove(type k){
        remove(find(k,root));
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
    void inorder(){
        inorder(root);
        cout<<endl;
    }
};