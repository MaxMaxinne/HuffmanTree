#include<iostream>
#include<fstream>
#include<unordered_map>
#include"HuffmanTree.h"
using namespace std;
class FileEncoder{
unordered_map<int,int> charmap;
public:
    void FileInput(){
        ifstream input("test.txt");
        char buffer=' ';
        while(input.get(buffer)){
            auto iter=charmap.find(buffer);
            if (iter!=charmap.end())
                iter->second++;
            else
                charmap[buffer]=1;
        }
    }
};
int main(){
    FileEncoder f;
    f.FileInput();
    
}