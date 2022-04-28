#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct tokenAttr{
    string str;
    string TYPE;
    int VAL;

    tokenAttr(string s, string t, int val){
        str = s;
        TYPE = t;
        VAL = val;
    }
};

int main(){
    tokenAttr t = tokenAttr("a", "b", 32);
    cout << t.str << endl;
    cout << t.TYPE << endl;
    cout << t.VAL << endl;
}