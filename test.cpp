#include<iostream>
#include<fstream>
using namespace std;
void read(){
    ifstream s("data",ios::binary);
    uint8_t buffer;
    s.read((char*)&buffer,sizeof(buffer));
    s.close();
    cout<<buffer<<endl;
}
int main(){
    ofstream s("data",ios::binary);
    uint8_t buffer;
    buffer=0b101;
    s.write((char*)&buffer,sizeof(buffer));
    s.close();
    read();
}