#include <iostream>
#include "queue.h"
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    int height1(TreeNode* aux){
        if(!aux) return 1;
        int hl=height1(aux->left),
            hr=height1(aux->right);
        if(!hl || !hr) return 0;
        if(abs(hl-hr)>1) return 0;
        return max(hl,hr)+1;
    }

    bool isBalanced(TreeNode* root) {
        if(height1(root)) return true;
        return false;
    }

    int height(TreeNode* aux){
        if(!aux) return 0;
        int hl=height1(aux->left),
            hr=height1(aux->right);
        return max(hl,hr)+1;
    }

    int factor(TreeNode* aux){
        if(!aux) return 0;
        int hl=height1(aux->left),
            hr=height1(aux->right);
        return hl-hr;
    }

    TreeNode* lturn(TreeNode* aux){
        auto tmp=aux->right;
        aux->right=tmp->left;
        tmp->left=aux;
        return tmp;
    }

    TreeNode* rturn(TreeNode* aux){
        auto tmp=aux->left;
        aux->left=tmp->right;
        tmp->right=aux;
        return tmp;
    }

    TreeNode* balance(TreeNode* aux){
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
        } return aux;
    }

    TreeNode* balanceBST(TreeNode* root) {
        if(!root) return root;
        root->left=balanceBST(root->left);
        root->right=balanceBST(root->right);
        return balance(root);
    }

    void bfs(TreeNode* root){
        queue<TreeNode*> q0;
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
            cout<<aux->val<<' ';
        }   cout<<endl;
    }

    void sort(vector<int>& arr){
        int n=arr.size();
        for(int i=0;i<n;i++)
            for(int j=1;j<n;j++)
                if(arr[j]<arr[j-1]){
                    auto tmp=arr[j];
                    arr[j]=arr[j-1];
                    arr[j-1]=tmp;
                }
    }

    TreeNode* build(vector<int> arr){
        if(arr.empty()) return nullptr;
        int n=arr.size();
        if(n==1) return new TreeNode(arr[0]);

        vector<int> right(n-n/2-1);
        for(int i=n-n/2-2;i>=0;i--){
            right[i]=arr.back();
            arr.pop_back();
        }
        int half=arr.back();
        arr.pop_back();

        auto aux=new TreeNode(half);
        aux->left=solve(arr);
        aux->right=solve(right);
        return aux;
    }

    TreeNode* solve(vector<int> arr){
        sort(arr);
        return build(arr);
    }

};