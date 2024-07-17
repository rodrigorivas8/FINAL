#include <vector>
#include "minheap.h"
#include "maxheap.h"
using namespace std;

class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        minheap<pair<int,int>> heap;
        for(int i=0;i<mat.size();i++){
            int s=0;
            for(auto j:mat[i])
                s+=j;
            heap.add({s,i});
        }
        vector<int> ans;
        while(k--) ans.push_back(heap.pop().second);
        return ans;
    }

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        maxheap<int> heap;
        for(auto& row:matrix)
            for(auto i:row)
                if(heap.size()!=k)
                    heap.add(i);
                else if(i<heap.max()){
                    heap.pop();
                    heap.add(i);
                }
        return heap.max();
    }
};

class KthLargest {
    maxheap<int> low;
    minheap<int> big;
public:

    KthLargest(int k, vector<int>& nums) {
        for(auto i:nums) low.add(i);
        while(--k) big.add(low.pop());
    }

    int add(int val) {
        big.add(val);
        low.add(big.pop());
        return low.max();
    }
};