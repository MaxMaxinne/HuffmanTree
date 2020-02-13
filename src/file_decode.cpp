#include"HuffmanTree.h"
#include<bitset>
#define BYTE 8
using namespace std;
HuffmanTree hfm;
void fileDecode(){
    ifstream input("codefile",ios::binary);
    if(!input.is_open()){
        cerr<<"An error occured during opening codefile";
        exit(10008);
    }
    ofstream output("textfile.txt");
    if(!output.is_open()){
        cerr<<"An error occured during writing textfile.txt";
        exit(10009);
    }
    hfm.codemapGenerate();
    uint32_t buffer=0;
    string code="";
    while(input.read((char*)&buffer,sizeof(buffer))){
        bitset<sizeof(buffer)*BYTE> bit(buffer);
        string bytes=bit.to_string();
        int bytes_len=bytes.length(),p_bytes=0;
        while(p_bytes<bytes_len){
            code.push_back(bytes[p_bytes++]);
            auto iter=hfm.codemap.find(code);
            if(iter!=hfm.codemap.end()){
                output.put(iter->second);
                code.clear();
            }
        }
    }
    input.close();
    output.close();
}
int main(){
    hfm.treeBuild();
    fileDecode();
    return 0;
}