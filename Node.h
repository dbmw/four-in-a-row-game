//Node.h:信心上限树算法中的节点类

#ifndef NODE_H_
#define NODE_H_
#include <vector>

class Node{
public:
	~Node(){
		for (int i = 0; i < (int)son.size(); i++) delete son[i];
	}
	int a;//该节点下一个可以生成子节点的列的列数；
	std::vector<Node*> son;//子节点地址集；
	Node* father;//父节点
	std::vector<int> route;//落子序列；只记录每次落子的列数
	unsigned int Num;//该节点被模拟的次数
	int Q;//该节点的收益
};

//每次调用前应确保board是由_board刚转化而成的状态,_top亦然；
Node* TreePolicy(Node* v,const int M,const int N,int ** board,const int noX,const int noY,int* _top,double c);

//生成子节点，起构造函数作用；根节点的构造必须另外考虑；
Node* Expand(Node* v,const int N,int* _top,const int noX,const int noY);

//检查某个节点是否可被拓展；
bool isExtensible(Node *v,const int N);

//返回某个不可被拓展的节点的最优子节点；
Node* BestChild(Node* v,double c);

int DefaultPolicy(Node* v,const int M,const int N,int ** board,const int noX,const int noY,int* _top);

void Backup(Node* v,int delta);

#endif