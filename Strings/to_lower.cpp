#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

void to_lower(string filename){
    fstream file(filename, fstream::in);
    if(file.is_open()){
        vector<string> handle;
        string temp;
        while(file.good()){
            file >> temp;
            handle.push_back(temp);
        }
        for(auto& str: handle){
            for(auto& c: str){
                if(isalpha(c))
                    c = tolower(c);
            }
        }
        file.close();
        file.open(filename, fstream::out);
        if(file.is_open()){
            for(auto str: handle)
                file << str << endl;
            file.close();
        }
        else abort();
    }
    else abort();
}

int main(void){
    to_lower("./sc-dict.txt");
    return 0;
}