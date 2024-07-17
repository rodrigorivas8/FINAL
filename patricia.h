#include <iostream>
#include <vector>
#include <bitset>
#include "stack.h"
using namespace std;

struct patricia{

    string text;
    vector<int> start,twin,height;

    string bin2txt(string bin){
        string txt;
        int w=128,ch=0;
        for(auto b:bin){
            ch+=w*(b=='1');
            if(w/=2) continue;
            txt+=char(ch);
            w=128; ch=0;
        }
        return txt;
    }
    string txt2bin(string txt){
        string bin,aux;
        for(auto ch:txt){
            bitset<8> bs(ch);
            aux=bs.to_string();
            bin.append(aux);
        }
        return bin;
    }

public:

    patricia(){
        start={0};
        twin={0};
        height={0};
    }

    int find_one(string key){
        int l=key.size();
        int t=1,h=0,c=0;

        while(true){
            c=twin[t];
            h=height[c];
            if(h>=l) return t;
            if(c%2==1) return t;
            char next=key[h];
            t=c+(next=='1');
        }
    }

    vector<int> find_all(string key){

        key=txt2bin(key);
        int t=find_one(key);
        int l=key.size();

        int c=twin[t];
        int s=start[c];
        int h=height[c];

        if(h<l) return {};
        auto in=text.substr(s,l);
        if(in!=key) return {};
        if(c%2) return {c};

        stack<int> stack;
        vector<int> chains;
        stack.push(c+1);
        while(true){
            c=twin[c];
            if(c%2==0){
                stack.push(c+1);
            }else{
                chains.push_back(c);
                if(stack.empty())
                    return chains;
                c=stack.pop();
            }
        }

    }

    int find_start(string phrase){
        int l=phrase.size();
        int n=start.size()/2;
        for(int i=0;i<n;i++){
            int c=2*i+1,
                s=start[c],
                h=height[c];
            if(h<=l) continue;
            s=s+h-l;
            auto in=text.substr(s,l);
            if(in==phrase) return s;
        }
        return -1;
    }

    bool add(string phrase){

        phrase=txt2bin(phrase);
        int s=find_start(phrase);
        int l=phrase.size();

        if(text.empty()){
            text.append(phrase);
            start.push_back(0);
            height.push_back(l);
            twin.push_back(1);
            return true;
        }

        if(s==-1){
            s=text.size();
            text.append(phrase);
        }

        start.push_back(s);
        start.push_back(s);

        int t=find_one(phrase);
        int c=twin[t];
        int h=height[c];
        s=start[c];

        string prefix;
        string end=text.substr(s,h);
        for(int i=0;i<l;i++)
            if(phrase[i]!=end[i]) break;
            else prefix+=end[i];

        h=prefix.size();
        if(h==l) return false;
        height.push_back(h);
        height.push_back(l);

        t=find_one(prefix);
        c=twin[t];

        int n=twin.size()-1;
        if(end[h]=='0'){
            twin.push_back(c);
            twin.push_back(n+2);
        }else{
            twin.push_back(n+2);
            twin.push_back(c);
        }
        twin[t]=n+1;

        return true;
    }

    vector<string> find(string key){
        auto chains=find_all(key);
        vector<string> ends;
        for(int c:chains){
            int s=start[c];
            int h=height[c];
            auto bin=text.substr(s,h);
            auto txt=bin2txt(bin);
            ends.push_back(txt);
        }
        return ends;
    }

    vector<int> sort(int t){
        int c=twin[t];
        if(c%2==1) return {t};
        vector<int> v=sort(c);
        v.push_back(t);
        for(auto i:sort(c+1))
            v.push_back(i);
        return v;
    }

    void display(){

        string aux;
        int c,s,h,fix,m=0;
        auto n=twin.size()-1;
        vector<string> col;
        auto twn=sort(1);
        bool null=false;

        for(int i=0;i<n;i++){
            int t=twn[i];
            if(t%2==0) fix=height[t];
            else fix=height[t-1];

            c=twin[t];
            s=start[c]+fix;
            h=height[c]-fix;
            if(h==0) null=true;

            aux=string(fix,' ');
            aux+=text.substr(s,h);
            m=max(m,int(aux.size()));
            col.push_back(aux);
        }

        if(null){
            for(auto c:col){
                if(c.empty()) cout<<"x ";
                else cout<<"  ";
            }
            cout<<endl;
        }

        for(int r=0;r<m;r++){
            if(r%8==0 && r) cout<<endl;
            for(int c=0;c<n;c++){
                cout<<' ';
                if(col[c].size()<=r){
                    cout<<' ';
                    continue;
                }
                cout<<col[c][r];
            }
            cout<<endl;
        }
    }

};