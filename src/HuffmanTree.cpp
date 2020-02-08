#include"HuffmanTree.h"
using namespace std;

static bool cmp(const HuffmanNode* n1,const HuffmanNode* n2){
    return n1->weight>n2->weight;//小根堆比较函数
}
void HuffmanTree::initialize(vector<HuffmanNode*>& v){
    make_heap(v.begin(),v.end(),cmp);
    while(v.size()!=1){
        HuffmanNode* n1=v[0];
        pop_heap(v.begin(),v.end(),cmp);
        v.pop_back();
        HuffmanNode* n2=v[0];
        pop_heap(v.begin(),v.end(),cmp);
        v.pop_back();
        HuffmanNode* node_new=new HuffmanNode(n1->weight+n2->weight,' ',n1,n2);
        v.push_back(node_new);
        push_heap(v.begin(),v.end(),cmp);
    }
    if(!v.empty())
        hNode=v[0];
    else{
        cerr<<"Container empty"<<endl;
        exit(10001);
    }
}
void HuffmanTree::initialize(vector<HuffmanNode_serialize>& v){
    if(v.empty()){
        cerr<<"file hfmtree empty"<<endl;
        exit(10007);
    }
    HuffmanNode* array=new HuffmanNode[v.size()];
    for(auto iter=v.begin();iter!=v.end();iter++){
        array[iter->index].character=iter->character;
        array[iter->index].index=iter->index;
        array[iter->index].weight=iter->weight;
        if(iter->right!=-1)
            array[iter->index].right=array+iter->right;
        else
            array[iter->index].right=nullptr;
        if(iter->left!=-1)
            array[iter->index].left=array+iter->left;
        else
            array[iter->index].left=nullptr;
    }
    hNode=array;
    array=nullptr;
}
void HuffmanTree::mapGenerate_helpfunc(string n,HuffmanNode* node){
    if(!node)
        return;
    if(node->character!=' '){
        charmap[node->character]=n;
        return;
    }
    if(node->left)
        mapGenerate_helpfunc(n+"0",node->left);
    if(node->right)
        mapGenerate_helpfunc(n+"1",node->right);
}
int HuffmanTree::setIndex(){
    if(!hNode){
        cerr<<"Tree empty"<<endl;
        exit(10004);
    }
    int p=0;
    queue<HuffmanNode*> q;
    q.push(hNode);
    while(!q.empty()){
        HuffmanNode* node=q.front();
        q.pop();
        node->index=p++;
        if(node->left)
            q.push(node->left);
        if(node->right)
            q.push(node->right);
    }
    return p;
}
void HuffmanTree::saveTree(){
    if(!hNode){
        cerr<<"Tree empty"<<endl;
        exit(10004);
    }
    ofstream writer("hfmtree",ios::out|ios::binary);
    if(!writer.is_open()){
        cerr<<"An error occured during writing file hfmtree"<<endl;
        exit(10005);
    }
    int numberOfNode=setIndex();
    HuffmanNode_serialize* array=new HuffmanNode_serialize[numberOfNode];
    queue<HuffmanNode*> q;
    q.push(hNode);
    while(!q.empty()){
        HuffmanNode* node=q.front();
        q.pop();
        array[node->index].character=node->character;
        array[node->index].weight=node->weight;
        array[node->index].index=node->index;
        if(node->left){
            array[node->index].left=node->left->index;
            q.push(node->left);
        }else
            array[node->index].left=-1;
        if(node->right){
            array[node->index].right=node->right->index;
            q.push(node->right);
        }else
            array[node->index].right=-1;
    }
    writer.write((char*)array,sizeof(HuffmanNode_serialize)*numberOfNode);
    writer.close();
    delete []array;
}
void HuffmanTree::treeBuild(unordered_map<char,int>& map){
    hNode=nullptr;
    int p=0;
    vector<HuffmanNode*> v;
    for(auto iter=map.begin();iter!=map.end();iter++)
        v.push_back(new HuffmanNode(iter->second,iter->first));
    if(v.empty()){
        cerr<<"file empty"<<endl;
        exit(10003);
    }
    initialize(v);
}
void HuffmanTree::treeBuild(){
    hNode=nullptr;
    ifstream input("hfmtree",ios::binary|ios::in);
    if(!input.is_open()){
        cerr<<"An error occured during opening file hfmtree"<<endl;
        exit(10007);
    }
    vector<HuffmanNode_serialize> v;
    HuffmanNode_serialize buffer;
    while(!input.read((char*)&buffer,sizeof(buffer)))
        v.push_back(buffer);
    initialize(v);
    input.close();
}