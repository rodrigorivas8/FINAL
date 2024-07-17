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