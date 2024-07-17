#include <vector>
using namespace std;

template <class type>
class minheap{
    vector<type> heap;
    int n=0;

    void up(int i){
        if(i==0) return;
        int p=(i-1)/2;
        if(heap[i]>=heap[p])
            return;
        auto tmp=heap[i];
        heap[i]=heap[p];
        heap[p]=tmp;
        up(p);
    }

    void down(int i){
        if(i*2>=n-1) return;
        int l=i*2+1,
            r=i*2+2,
            min=i;

        if(r==n) r=i;
        if(heap[min]>heap[l]) min=l;
        if(heap[min]>heap[r]) min=r;
        if(min==i) return;

        auto tmp=heap[min];
        heap[min]=heap[i];
        heap[i]=tmp;

        down(min);
    }

public:

    void clear(){
        while(heap.size()!=n)
            heap.pop_back();
    }

    void add(type k){
        clear();
        heap.push_back(k);
        up(n++);
    }

    type pop(){
        auto min=heap[0];
        heap[0]=heap[n-1];
        heap[n---1]=min;
        down(0);
        return min;
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

    type min(){
        return heap[0];
    }

    int size(){
        return n;
    }

};