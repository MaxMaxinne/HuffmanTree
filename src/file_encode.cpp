#include"HuffmanTree.h"
using namespace std;

unordered_map<char,int> charmap;
HuffmanTree hfm;
void fileInput(string filename){
    ifstream input;
    input.open(filename);
    if(!input.is_open()){
        cerr<<"An error occured during opening file "<<filename<<endl;
        exit(10000);
    }
    char buffer=' ';
    while(input.get(buffer)){
        auto iter=charmap.find(buffer);
        if (iter!=charmap.end())
            iter->second++;
        else
            charmap.insert(pair<char,int>(buffer,1));
    }
    input.close();
}
void fileEncode(string filename){
    const int BYTES_LENGTH=32;
    ifstream input;
    ofstream output("codefile",ios::binary);
    input.open(filename);
    if(!input.is_open()){
        cerr<<"An error occured during opening file "<<filename<<endl;
        exit(10006);
    }
    hfm.mapGenerate();
    char buffer=' ';
    uint32_t bytes=0;
    string binary;
    string bi_remain;
    int length=0,remain_len=0,bi_len=0,p_remain=0,p_bi=0;
    while(input.get(buffer)){//可能出现buffer被顶替
        binary=hfm.charmap[buffer];
        bi_len=binary.length();
        remain_len=bi_remain.length();
        length=0;
        p_bi=0;
        while(length<BYTES_LENGTH){
            if(p_remain<remain_len){
                bytes<<=1;
                bytes|=bi_remain[p_remain++]-'0';
                length++;
                continue;
            }
            if(p_bi<bi_len){
                bytes<<=1;
                bytes|=binary[p_bi++]-'0';
                length++;
                continue;
            }
            if(p_bi>=bi_len){
                if(!input.get(buffer)){
                    bytes<<=(BYTES_LENGTH-length);
                    break;//将二进制移至高位
                }
                else{
                    binary=hfm.charmap[buffer];
                    p_bi=0;
                    bi_len=binary.length();
                }
            }
        }
        output.write((char*)&bytes,sizeof(bytes));
        bi_remain=binary;
        p_remain=p_bi;
        bytes=0;
    }
    output.close();
}
int main(){
    string filename;
    cin>>filename;
    fileInput(filename);
    hfm.treeBuild(charmap);
    hfm.saveTree();
    fileEncode(filename);
    return 0;
}