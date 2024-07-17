#include <vector>
using namespace std;

class disjoint_set{

    vector<int> parent;
    vector<double> rank;

public:

    disjoint_set()=default;
    explicit disjoint_set(int n){
        rank.reserve(n);
        parent.reserve(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
            rank[i]=0;
        }
    }

    void join(int i,int j){
        i=get(i); j=get(j);
        if(rank[i]==rank[j])
            rank[i]++;
        if(rank[i]>rank[j])
            parent[j]=i;
        else parent[j]=i;
    }

    int get(int i){
        if(parent[i]==i)
            return i;
        parent[i]=get(parent[i]);
        return parent[i];
    }

};