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
int main(){
    /**ofstream s("data",ios::binary);
    uint8_t buffer;
    buffer=0b101;
    s.write((char*)&buffer,sizeof(buffer));
    s.close();**/
    read();
}