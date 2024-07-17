#include <algorithm>
#include <vector>
#include "graph.h"
using namespace std;

class Solution {
public:
    int problem1(int n,vector<vector<int>>& trust) {
        int sum[n];
        for(int i=0;i<n;i++) sum[i]=0;
        for(auto t:trust){
            sum[t[0]-1]--;
            sum[t[1]-1]++;
        }
        int judge=-1;
        for(int i=0;i<n;i++){
            if(sum[i]==n-1){
                if(judge!=-1) break;
                else judge=i+1;
            }
        }
        return judge;
    }

    bool search(graph* g,int u,int v){
        if(u==v) return true;
        for(auto i:g->list[u]){
            g->list.erase(g->list.begin());
            if(search(g,i.vertex,v))
                return true;
        }
        return false;
    }

    bool problem2(int n,vector<vector<int>>& edges,int source,int destination){
        if(source==destination) return true;
        if(edges.empty()) return false;
        graph g0(n);
        for(auto edge:edges){
            int u=edge[0],v=edge[1];
            g0.list[u].emplace_back(v);
            g0.list[v].emplace_back(u);
        }
        return search(&g0,source,destination);
    }
};