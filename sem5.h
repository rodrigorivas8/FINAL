#include <string>
#include <vector>
using namespace std;

const int cap=30;
struct func{
    struct dic{
        int arr[cap]={};
        int& operator[](char c){
            int id=int(c)%cap;
            return arr[id];
        }
    };
    int count(string s){
        string word="balloon";
        dic base,aux;

        for(char c:word) base[c]++;
        for(char c:s) aux[c]++;

        int m=INT_MAX,k;
        for(char c:word){
            k=aux[c]/base[c];
            m=min(m,k);
        }   return m;
    }

    string decode(string code){
        string key="the quick brown fox jumps over the lazy dog";
        dic deco; deco[' ']=' ';
        int i='a';
        for(char c:key){
            if(deco[c]) continue;
            deco[c]=i++;
        }
        string r;
        for(char c:code)
            r+=deco[c];
        return r;
    }

    bool good(string s){
        dic d;
        int m=0,n=0;
        for(char c:s){
            if(!d[c]) n++;
            m=max(m,++d[c]);
        }
        return s.length()==m*n;
    }

    string minimize(string s){
        dic freq;
        for(auto ch:s) freq[ch]++;

        string ans;
        for(auto ch:s){
            ans+=ch;
            if(ch!='?') continue;
            char min='a';
            for(char l='b';l<='z';l++)
                if(freq[min]>freq[l])
                    min=l;
            freq[min]++;
            ans.back()=min;
        }
        return ans;
    }
};