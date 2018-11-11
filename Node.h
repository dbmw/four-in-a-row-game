//Node.h:�����������㷨�еĽڵ���

#ifndef NODE_H_
#define NODE_H_
#include <vector>

class Node{
public:
	~Node(){
		for (int i = 0; i < (int)son.size(); i++) delete son[i];
	}
	int a;//�ýڵ���һ�����������ӽڵ���е�������
	std::vector<Node*> son;//�ӽڵ��ַ����
	Node* father;//���ڵ�
	std::vector<int> route;//�������У�ֻ��¼ÿ�����ӵ�����
	unsigned int Num;//�ýڵ㱻ģ��Ĵ���
	int Q;//�ýڵ������
};

//ÿ�ε���ǰӦȷ��board����_board��ת�����ɵ�״̬,_top��Ȼ��
Node* TreePolicy(Node* v,const int M,const int N,int ** board,const int noX,const int noY,int* _top,double c);

//�����ӽڵ㣬���캯�����ã����ڵ�Ĺ���������⿼�ǣ�
Node* Expand(Node* v,const int N,int* _top,const int noX,const int noY);

//���ĳ���ڵ��Ƿ�ɱ���չ��
bool isExtensible(Node *v,const int N);

//����ĳ�����ɱ���չ�Ľڵ�������ӽڵ㣻
Node* BestChild(Node* v,double c);

int DefaultPolicy(Node* v,const int M,const int N,int ** board,const int noX,const int noY,int* _top);

void Backup(Node* v,int delta);

#endif