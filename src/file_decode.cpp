#include"HuffmanTree.h"
#include<bitset>
#define BYTE 8
using namespace std;
HuffmanTree hfm;
void codeDisplay(string code){
    static int code_num=0;
    static ofstream output("codeprint.txt");
    output<<code;
    cout<<code;
    code_num++;
    if(code_num%50==0){
        cout<<endl;
        output<<endl;
    }
}
void treeDisplay(){
    ofstream output("treeprint.txt");
    if(!output.is_open()){
        cerr<<"An error occured during writing treeprint.txt"<<endl;
        exit(10011);
    }
    cout<<"Printing Tree..."<<endl;
    queue<HuffmanNode*> q;
    q.push(hfm.hNode);
    string mid;
    hfm.midOrder(hfm.hNode,mid);
    int spacenum=2<<(hfm.height()-1);//最后一层空白字符个数
    while (!q.empty()){
        vector<HuffmanNode*> cache;
        while (!q.empty()){
            cache.push_back(q.front());
            q.pop();
        }
        string line,connect;
        line.insert(0,spacenum,' ');
        connect=line;
        for(HuffmanNode* p:cache)
            if (p){
                int index=mid.find((char)p->index);
                if(p->character=='\0')
                    //line.insert(index,to_string(p->weight));
                    line[index]='*';
                else
                    line[index]=p->character;
                if(p->left){
                    q.push(p->left);
                    connect[index-1]='/';
                }
                if(p->right){
                    q.push(p->right);
                    connect[index+1]='\\';
                }
            }
        output<<line<<endl;
        output<<connect<<endl;   
        cout<<line<<endl;
        cout<<connect<<endl;
    }
}
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
    input.seekg(-1,ios_base::end);
    uint8_t finalLen=0;
    int length=input.tellg();
    length++;
    input.read((char*)&finalLen,sizeof(finalLen));
    input.seekg(0,ios_base::beg);
    hfm.codemapGenerate();
    bool isfinal=false;
    uint32_t buffer=0;
    string code="";
    cout<<"Printing Code..."<<endl;
    while(input.read((char*)&buffer,sizeof(buffer))){
        bitset<sizeof(buffer)*BYTE> bit(buffer);
        string bytes=bit.to_string();
        int bytes_len=bytes.length(),p_bytes=0;
        if(length-input.tellg()<=1){
            isfinal=true;
            bytes_len=finalLen;
        }
        while(p_bytes<bytes_len){
            code.push_back(bytes[p_bytes++]);
            auto iter=hfm.codemap.find(code);
            if(iter!=hfm.codemap.end()){
                output.put(iter->second);
                codeDisplay(code);
                code.clear();
            }
        }
        if(isfinal)
            break;
    }
    input.close();
    output.close();
}
int main(){
    hfm.treeBuild();
    fileDecode();
    cout<<endl;
    treeDisplay();
    return 0;
}