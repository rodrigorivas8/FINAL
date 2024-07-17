#include <vector>
using namespace std;

const int cap=1e5;
template <class type>
class stack{
    vector<type> list;

public:
    bool empty(){
        return list.empty();
    }
    bool full(){
        return list.size()==cap;
    }
    bool push(type k){
        if(full()) return false;
        list.push_back(k);
        return true;
    };
    type pop(){
        if(empty()) return {};
        type k=list.back();
        list.pop_back();
        return k;
    };
    type top(){
        if(empty()) return {};
        return list.back();
    };
};