#include <vector>
using namespace std;

template <class type>
class maxheap{
    vector<type> heap;
    int n=0;

    void up(int i){
        if(i==0) return;
        int p=(i-1)/2;

        if(heap[i]<=heap[p]) return;
        auto tmp=heap[i];
        heap[i]=heap[p];
        heap[p]=tmp;

        up(p);
    }

    void down(int i){
        if(i*2>=n-1) return;
        int l=i*2+1,
            r=i*2+2,
            max=i;

        if(r==n) r=i;
        if(heap[max]<heap[l]) max=l;
        if(heap[max]<heap[r]) max=r;
        if(max==i) return;

        auto tmp=heap[i];
        heap[i]=heap[max];
        heap[max]=tmp;

        down(max);
    }

public:
    void clear(){
        while(n!=heap.size())
            heap.pop_back();
    }

    void add(type k){
        clear();
        heap.push_back(k);
        up(n++);
    }

    type pop(){
        auto tmp=heap[0];
        heap[0]=heap[n-1];
        heap[n---1]=tmp;
        down(0);
        return tmp;
    }

    auto sort(){
        int aux=n;
        while(n) pop();
        n=aux;
        return heap;
    }

    void fix(){
        for(int i=n/2;i>=0;i--)
            down(i);
    }

    type max(){
        return heap[0];
    }

    int size(){
        return n;
    }

};