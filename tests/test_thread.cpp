#include<thread>
#include<vector>
#include<iostream>
using namespace std;

void add(vector<string> str){
    cout << str.at(0) << endl;
}

int main(int argc, char const *argv[])
{
    vector<string> vec;
    vector<thread> thrds;

    vec.push_back("h");
    vec.push_back("e");
    vec.push_back("l");
    vec.push_back("l");
    vec.push_back("0");

    for (int i = 0; i < 10; i++)
    {
        thrds.emplace_back(add, vec);
    }

    for (int idx = 0; idx < thrds.size(); idx++)
    {
        thrds.at(idx).join();
    }
    
    
    return 0;
}
