#ifndef HFM
#define HFM
#include<algorithm>
#include<unordered_map>
#include<iostream>
#include<stdlib.h>
#include<queue>
#include<vector>
#include<fstream>
using namespace std;
//errorcode:10014

class HuffmanNode{
public:
    int weight,
        index;//
    HuffmanNode* left
                ,*right;
    char character;
    HuffmanNode():left(nullptr),right(nullptr){}
    HuffmanNode(int w,char c):weight(w),left(nullptr),right(nullptr),character(c){}
    HuffmanNode(int w,char c,HuffmanNode* l,HuffmanNode* r):weight(w),left(l),right(r),character(c){}
};
class HuffmanNode_serialize{
public:
    int weight,
        left,
        right,
        index;
    char character;
};
class HuffmanTree{
private:
    HuffmanNode* hNode;
    unordered_map<string,char> codemap;
    unordered_map<char,string> charmap;
    int size;
    void initialize(vector<HuffmanNode*>&);
    void mapGenerate_helpfunc(string,HuffmanNode*);
    void initialize(vector<HuffmanNode_serialize>&);
    int setIndex();
    int getHeight(HuffmanNode*);
    void codemapGenerate_helpfunc(HuffmanNode*,string);
public:
    friend void fileEncode(string);
    friend void fileDecode();
    friend void treeDisplay();
    ~HuffmanTree(){
        queue<HuffmanNode*> q;
        q.push(hNode);
        while(!q.empty()){
            HuffmanNode* node=q.front();
            q.pop();
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
            delete node;
        }
    }
    void midOrder(HuffmanNode*,string&);
    int height(){return getHeight(hNode);}
    void treeBuild();
    void codemapGenerate();
    void mapGenerate(){
        if(!hNode)
            return;
        mapGenerate_helpfunc("",hNode);
    }
    void saveTree();
    void treeBuild(unordered_map<char,int>&);
};
#endif