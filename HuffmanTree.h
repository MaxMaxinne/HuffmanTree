#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
using namespace std;
class HuffmanNode{
public:
    int weight;
    HuffmanNode* left
                ,*right;
    char character;
    HuffmanNode(int w,char c):weight(w),left(nullptr),right(nullptr),character(c){}
    HuffmanNode(int w,char c,HuffmanNode* l,HuffmanNode* r):weight(w),left(l),right(r),character(c){}
};
bool cmp(const HuffmanNode& n1,const HuffmanNode& n2){
    return n1.weight<n2.weight;
}  
class HuffmanTree{
private:
    HuffmanNode* hNode;
    int size;
    void initialize(vector<HuffmanNode*>& v){
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
    }
public:
    HuffmanTree(unordered_map<char,int>& map){
        hNode=nullptr;
        int p=0;
        vector<HuffmanNode*> v;//TODO 处理map为空
        for(auto iter=map.begin();iter!=map.end();iter++)
            v.push_back(new HuffmanNode(iter->second,iter->first));
    }
};