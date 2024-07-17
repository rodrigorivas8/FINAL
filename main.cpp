#include <vector>
using namespace std;

const int qap=1e5;
template <class type>
class queue{
    vector<type> list;
public:
    bool empty(){
        return list.empty();
    }
    bool full(){
        return list.size()==qap;
    }
    bool enqueue(type k){
        if(full()) return false;
        list.push_back(k);
        return true;
    }
    type dequeue(){
        if(empty()) return {};
        type k=list[0];
        list.erase(list.begin());
        return k;
    }
    type front(){
        if(empty()) return {};
        return list[0];
    }

};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
};

class Solution {
public:
    vector<int> leafs(TreeNode* aux){
        queue<TreeNode*> q0;
        q0.enqueue(aux);
        vector<int> l;
        while(!q0.empty()){
            aux=q0.dequeue();
            if(!aux) continue;
            q0.enqueue(aux->left);
            q0.enqueue(aux->right);
            l.push_back(aux->val);
        }
        return l;
    }

    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        auto v1=leafs(root1),
                v2=leafs(root2);
        for(int i=0;i<min(v1.size(),v2.size());i++)
            if(v1[i]!=v2[i]) return false;
        return true;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        graph g0(edges.size());
        for(auto i:edges){
            g0.insert(i[0],i[1]);
            g0.insert(i[1],i[0]);
        }

        vector<int> pos={};
        int u=0;
        queue<int> queue;
        queue.enqueue(u);
        while(!queue.empty()){
            u=queue.dequeue();
            for(auto edge:g0.list[u]){
                int v=edge.vertex;
                if(g0.mark[v]){
                    pos={u,v};
                    continue;
                }
                queue.enqueue(v);
                g0.mark[v]=true;
            }
        }
        return pos;
    }

};













