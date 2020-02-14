#include"HuffmanTree.h"
using namespace std;

unordered_map<char,int> charmap;
HuffmanTree hfm;
void weightCount(string filename){
    ifstream input;
    input.open(filename);
    if(!input.is_open()){
        cerr<<"An error occured during opening file "<<filename<<endl;
        exit(10000);
    }
    char buffer='\0';
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
    char buffer='\0';
    uint32_t bytes=0;
    string binary;
    string bi_remain;
    int length=0,remain_len=0,bi_len=0,p_remain=0,p_bi=0;
    uint8_t finalLen=0;
    while(input.get(buffer)){//可能出现buffer被顶替
        auto iter=hfm.charmap.find(buffer);
        if(iter==hfm.charmap.end()){
            cerr<<"weight of character \""<<buffer<<"\" not found!"<<endl;
            exit(10013);
        }
        binary=iter->second;
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
    finalLen=length;
    output.write((char*)&finalLen,sizeof(finalLen));
    output.close();
}
void getWeight(){
    cout<<"please enter the weights in the format \"character:weight\"."<<endl;
    cout<<"different pairs of characters and weights must be on different lines."<<endl;
    cout<<"enter \"0\" to stop"<<endl;
    string buffer;
    while(cin>>buffer){
        if(buffer.length()>=3&&buffer[1]==':'){
            charmap[buffer[0]]=stoi(buffer.substr(2));
        }else{
            if(buffer.length()==1&&buffer[0]=='0')
                break;
            else{
                cerr<<"illegal characters"<<endl;
                exit(10011);
            }
        }
    }
}
int main(int argv,char** argc){
    string filename;
    if(argv==2){
        filename=argc[1];
        getWeight();
    }
    else{
        if(argv==3&&string(argc[2])=="--autocount"){
            filename=argc[1];
            weightCount(filename);
        }else{
            cerr<<"illegel command.Read ReadMe.md for more information"<<endl;
            exit(10012);
        }
    }
    hfm.treeBuild(charmap);
    hfm.saveTree();
    fileEncode(filename);
    return 0;
}