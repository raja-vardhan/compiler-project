#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
    string s = "23.0";
    cout << to_string(stoi(s)) << endl;
}