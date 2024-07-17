#include <iostream>
#include <vector>
using namespace std;

struct node{
    int key;
    node* left=nullptr,
            * right=nullptr;
    node()=default;
    node(int k):key(k){}
    node(int k,node* l,node *r)
    {key=k;left=l;right=r;}
    static node* null;
};

struct func{
    node*& find(node*& aux,int key){
        if(!aux) return node::null;
        if(aux->key==key) return aux;
        auto& l=find(aux->left,key),
            & r=find(aux->right,key);
        if(l) return l; return r;
    }

    bool check(node* u,node* v){
        if(!u && !v) return true;
        if(!u || !v) return false;
        auto l=check(u->left,v->left),
             r=check(u->right,v->right);
        return l&&r;
    }

    bool sub(node* r1,node* r2){
        auto r3=find(r1,r2->key);
        return check(r2,r3);
    }

    pair<int,node*> deepest(pair<int,node*> p0,node* bad){
        auto aux=p0.second;
        if(!aux || aux==bad) return {0,nullptr};
        if(!aux->right && !aux->left) return p0;

        int d=p0.first+1;
        auto l=deepest({d,aux->left},bad),
             r=deepest({d,aux->right},bad);
        return max(l,r);
    }

    node* common(node* aux,node* u,node* v){
        if(!aux) return aux;
        if(aux==u) return u;
        if(aux==v) return v;
        auto l=common(aux->left,u,v),
             r=common(aux->right,u,v);
        if(l==u && r==v) return aux;
        if(l==v && r==u) return aux;
        if(l) return l; return r;
    }

    node* ancestor(node* aux){
        if(!aux) return nullptr;
        auto p1=deepest({0,aux},nullptr);
        auto n1=p1.second;
        auto p2=deepest({0,aux},n1);
        auto n2=p2.second;
        return common(aux,n1,n2);
    }

    // la de 9
    node* build(vector<node*> roots){
        for(auto r:roots){
            auto aux=r;
            auto copy=roots;
            while(aux){
                aux=copy.back();
                copy.pop_back();
                if(aux==r) continue;

            }
        }
    }
};