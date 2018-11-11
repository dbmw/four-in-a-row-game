#include "Node.h"
#include "Judge.h"
#include <vector>
#include <ctime>

bool isExtensible(Node *v,const int N){
	return v->a < N;
}

Node* Expand(Node* v,const int N,int* _top,const int noX,const int noY){//生成子节点，起构造函数作用；根节点的构造必须另外考虑；
	Node* son = new Node;
	v->son.push_back(son);
	son->father = v;
	son->route = v->route;
	son->route.push_back(v->a);
	int a = v->a;
	bool flag = true;
	for (int i = v->a + 1; i < N && flag; i++){
		if (_top[i]) flag = false,v->a = i;
	}
	if (flag) v->a = N;
	else flag = true;
	if (--_top[a] == (1 + noX) && a == noY) --_top[a];
	for (int i = 0; i < N && flag; i++){
		if (_top[i]) flag = false,son->a = i;
	}
	if (flag) son->a = N;
	son->Num = 0,son->Q = 0;
	return son;
}

Node* BestChild(Node* v,double c){
	Node* result = v->son[0];
	for (int i = 1; i < (int)v->son.size(); i++){
		double c1 = result->Q / (double) result->Num + c * sqrt(2 * log((double) v->Num) / result->Num);
		double c2 = v->son[i]->Q / (double) v->son[i]->Num + c * sqrt(2 * log((double) v->Num) / v->son[i]->Num);//信心上界；
		if (c1 < c2) result = v->son[i];
	}
	return result;
}

Node* TreePolicy(Node* v,const int M,const int N,int ** board,const int noX,const int noY,int* _top,double c){
	int x = 0,y = 0;
	int flag = 0;
	while(!((flag ? machineWin(x,y,M,N,board) : userWin(x,y,M,N,board)) || isTie(N,_top))){
		if (isExtensible(v,N)){
			Node* temp = Expand(v,N,_top,noX,noY);
			int a = temp->route[temp->route.size() - 1];
			x = _top[a],y = a;
			if (x == noX && y == noY) x++;
			flag++;
			flag &= 1;
			if (flag) board[x][y] = 2;
			else board[x][y] = 1;
			return temp;
		}
		else{
			v = BestChild(v,c);
			int a = v->route[v->route.size() - 1];
			if (--_top[a] == (1 + noX) && a == noY) --_top[a];
			x = _top[a],y = a;
			if (x == noX && y == noY) x++;
			flag++;
			flag &= 1;
			if (flag) board[x][y] = 2;
			else board[x][y] = 1;
		}
	}
	return v;
}

int DefaultPolicy(Node* v,const int M,const int N,int ** board,const int noX,const int noY,int* _top){
	int flag = v->route.size() % 2,a = v->route[v->route.size() - 1];
	int x = _top[a],y = a;
	if (x == noX && y == noY) x++;
	while(!((flag ? machineWin(x,y,M,N,board) : userWin(x,y,M,N,board)) || isTie(N,_top))){
		bool win_lose_flag = false;
		if (flag){
			for (int i = 0; i < N && !win_lose_flag; i++){
				if(_top[i]){
					board[_top[i] - 1][i] = 1;
					if (userWin(_top[i] - 1,i,M,N,board)) win_lose_flag = true,a = i;
					board[_top[i] - 1][i] = 0;
				}
			}
			for (int i = 0; i < N && !win_lose_flag; i++){
			if(_top[i]){
					board[_top[i] - 1][i] = 2;
					if (machineWin(_top[i] - 1,i,M,N,board)) win_lose_flag = true,a = i;
					board[_top[i] - 1][i] = 0;
				}
			}
		}
		else{
			for (int i = 0; i < N && !win_lose_flag; i++){
			if(_top[i]){
					board[_top[i] - 1][i] = 2;
					if (machineWin(_top[i] - 1,i,M,N,board)) win_lose_flag = true,a = i;
					board[_top[i] - 1][i] = 0;
				}
			}
			for (int i = 0; i < N && !win_lose_flag; i++){
				if(_top[i]){
					board[_top[i] - 1][i] = 1;
					if (userWin(_top[i] - 1,i,M,N,board)) win_lose_flag = true,a = i;
					board[_top[i] - 1][i] = 0;
				}
			}
		}	
		if(!win_lose_flag){
			srand((unsigned)time(nullptr));
			a = rand() % N;
		}
		while (!_top[a]) a = rand() % N;
		if (--_top[a] == (1 + noX) && a == noY) --_top[a];
		x = _top[a],y = a;
		if (x == noX && y == noY) x++;
		flag++;
		flag &= 1;
		if (flag) board[x][y] = 2;
		else board[x][y] = 1;
	}
	if (isTie(N,_top)) return 0;
	else if(flag == (v->route.size() % 2)) return 1;
	else return -1;
}

void Backup(Node* v,int delta){
	while (v != NULL){
		v->Num++;
		v->Q += delta;
		delta = -delta;
		v = v->father;
	}
}