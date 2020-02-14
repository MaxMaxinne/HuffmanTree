#include<iostream>
#include<fstream>
#include<unordered_map>
using namespace std;
void read(){
    ifstream s("codefile",ios::binary);
    uint32_t buffer;
    s.read((char*)&buffer,sizeof(buffer));
    s.close();
    cout<<buffer<<endl;
}
void readMap(){
    ifstream s("charmap",ios::binary);
    
}
int main(int argc,char** argv){
    /**ofstream s("data",ios::binary);
    uint8_t buffer;
    buffer=0b101;
    s.write((char*)&buffer,sizeof(buffer));
    s.close();**/
    for(int i=0;i<argc;i++)
        cout<<argv[i]<<endl;
    string cmd(argv[2]);
    if(cmd=="--F")
        cout<<1<<endl;
}