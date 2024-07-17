#include <iostream>
using namespace std;

const int MAX=1e8;
template<class key_type,class val_type>
class hash_table{

    struct node{
        key_type key;
        val_type val;
        node* next=nullptr;

        node()=default;
        explicit node(key_type k):key(k){}
        node(key_type k,val_type v):key(k),val(v){}
        node(key_type k,val_type v,node* n):key(k),val(v),next(n){}
    };

    int rows=100;
    int cols=5;
    int filled=0;
    double maxFF=0.75;
    node** arr=nullptr;
    bool fix=false;

public:

    hash_table(){
        arr=new node*[rows]();
    }

    explicit hash_table(int c){
        rows=c;
        arr=new node*[rows]();
        fix=true;
    }

    template<class type>
    int hash(type k){
        int id=0;
        auto obj=reinterpret_cast<byte*>(&k);
        for(int i=0;i<sizeof(k);i++)
            id+=(i+1)*to_integer<int>(obj[i]);
        return id % rows;
    }

    int hash(string k){
        int id=0;
        for(int i=0;i<k.length();i++)
            id+=(i+1)*k[i];
        return id % rows;
    }

    auto add(key_type k){
        filled++;
        return new node(k);
    }

    double factor(){
        return double(filled)/(rows*cols);
    }

    val_type& access(key_type k){
        int id=hash(k);
        auto &aux=arr[id];
        if(!aux) aux=add(k);
        auto item=aux;
        while(true){
            if(item->key==k) return item->val;
            if(!item->next) item->next=add(k);
            item=item->next;
        }
    }

    void rehash(){
        rows*=2;
        filled=0;
        auto temp=arr;
        arr=new node*[rows]();
        for(int i=0;i<rows/2;i++){
            auto item=temp[i];
            while(item){
                auto aux=item;
                access(aux->key)=aux->val;
                item=item->next;
                delete aux;
            }
        }
        delete temp;
        if(rows>MAX) fix=true;
    }

    val_type& operator[](key_type k){
        if(!fix && factor()>maxFF) rehash();
        return access(k);
    }

    void remove(key_type k){
        int id=hash(k);
        auto aux=arr[id];
        if(!aux) return;
        filled--;
        if(aux->key==k){
            arr[id]=aux->next;
            delete aux;
            return;
        }
        while(aux->next->key!=k)
            aux=aux->next;
        auto temp=aux->next;
        aux->next=temp->next;
        delete temp;
    }

};