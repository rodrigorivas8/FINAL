#include <vector>
#include "queue.h"
using namespace std;

struct graph{

    struct edge{
        int vertex;
        double weight;
        edge()=default;
        explicit edge(int v):vertex(v){};
        edge(int v,double w)
        :vertex(v),weight(w){}
    };

    int n=0;
    vector<bool> mark;
    vector<vector<edge>> list;

    graph()=default;
    explicit graph(int n):n(n){
        list.resize(n);
        mark.resize(n);
    }

    void insert(int u,int v,double w=1){
        list[u].emplace_back(v,w);
    }

    void dfs(int u){
        mark[u]=true;
        //
        cout<<u;
        for(auto edge:list[u]){
            int v=edge.vertex;
            if(!mark[v]) dfs(v);
        }
    }

    void dfs(){
        for(int i=0;i<n;i++)
            mark[i]=false;
        for(int i=0;i<n;i++)
            if(!mark[i]) dfs(i);
    }

    void bfs(int u){
        queue<int> queue;
        queue.enqueue(u);
        while(!queue.empty()){
            u=queue.dequeue();
            //
            for(auto edge:list[u]){
                int v=edge.vertex;
                if(mark[v]) continue;
                queue.enqueue(v);
                mark[v]=true;
            }
        }
    }

    void bfs(){
        for(int i=0;i<n;i++)
            mark[i]=false;
        for(int i=0;i<n;i++)
            if(!mark[i]) bfs(i);
    }

    void relax(int u,edge e,vector<double>& w){
        int v=e.vertex;
        double w0=w[u]+e.weight;
        if(w0<w[v]) w[v]=w0;
    }

    vector<double> dijkstra(int u){

        vector<int> min(n);
        vector<double> weight(n,INT_MAX);
        for(int i=0;i<n;i++){
            mark[i]=false;
            min[i]=i;
        }

        weight[u]=0;
        while(!min.empty()){

            u=min[0];
            for(auto i:min)
                if(weight[i]<weight[u])
                    u=i;
            min.erase(min.begin()+u);

            for(auto edge:list[u]){
                int v=edge.vertex;
                if(mark[v]) continue;
                relax(u,edge,weight);
            }
            mark[u]=true;

        }
        return weight;
    };

    vector<vector<double>> floyd_warshall(){

        vector<double> inf(n,INT_MAX);
        vector<vector<double>> w(n,inf);
        for(int u=0;u<n;u++){
            w[u][u]=0;
            for(auto edge:list[u]){
                int v=edge.vertex;
                w[u][v]=edge.weight;
            }
        }

        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    if(w[i][k]+w[k][j]<w[i][j])
                        w[i][j]=w[i][k]+w[k][j];

        return w;
    };

    vector<double> bellman_ford(int u){
        vector<double> weight(n,INT_MAX);
        weight[u]=0;
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n;j++)
                for(auto edge:list[j])
                    relax(j,edge,weight);
        }
        return weight;
    }



};