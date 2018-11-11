#include <iostream>
#include <ctime>
#include <conio.h>
#include <atlstr.h>
#include "Strategy.h"
#include "Node.h"
#include "Judge.h"

using namespace std;

/*
	���Ժ����ӿ�,�ú������Կ�ƽ̨����,ÿ�δ��뵱ǰ״̬,Ҫ�����������ӵ�,�����ӵ������һ��������Ϸ��������ӵ�,��Ȼ�Կ�ƽ̨��ֱ����Ϊ��ĳ�������
		Ϊ�˷�ֹ�ԶԿ�ƽ̨ά����������ɸ��ģ����д���Ĳ�����Ϊconst����
		M, N : ���̴�С M - ���� N - ���� ����0��ʼ�ƣ� ���Ͻ�Ϊ����ԭ�㣬����x��ǣ�����y���
		top : ��ǰ����ÿһ���ж���ʵ��λ��. e.g. ��i��Ϊ��,��_top[i] == M, ��i������,��_top[i] == 0
		_board : ���̵�һά�����ʾ, Ϊ�˷���ʹ�ã��ڸú����տ�ʼ���������Ѿ�����ת��Ϊ�˶�ά����board
				��ֻ��ֱ��ʹ��board���ɣ����Ͻ�Ϊ����ԭ�㣬�����[0][0]��ʼ��(����[1][1])
				board[x][y]��ʾ��x�С���y�еĵ�(��0��ʼ��)
				board[x][y] == 0/1/2 �ֱ��Ӧ(x,y)�� ������/���û�����/�г������,�������ӵ㴦��ֵҲΪ0
		lastX, lastY : �Է���һ�����ӵ�λ��, ����ܲ���Ҫ�ò�����Ҳ������Ҫ�Ĳ������ǶԷ�һ����
				����λ�ã���ʱ��������Լ��ĳ����м�¼�Է������ಽ������λ�ã�����ȫȡ�������Լ��Ĳ���
		noX, noY : �����ϵĲ������ӵ�(ע:��ʵ���������top�Ѿ����㴦���˲������ӵ㣬Ҳ����˵���ĳһ��
				������ӵ�����ǡ�ǲ������ӵ㣬��ôUI�����еĴ�����Ѿ������е�topֵ�ֽ�����һ�μ�һ������
				��������Ĵ�����Ҳ���Ը�����ʹ��noX��noY��������������ȫ��Ϊtop������ǵ�ǰÿ�еĶ�������,
				��Ȼ�������ʹ��lastX,lastY�������п��ܾ�Ҫͬʱ����noX��noY��)
		���ϲ���ʵ���ϰ����˵�ǰ״̬(M N _top _board)�Լ���ʷ��Ϣ(lastX lastY),��Ҫ���ľ�������Щ��Ϣ�¸������������ǵ����ӵ�
*/
int getPoint(const int M, const int N, const int* top, const int* _board,
             const int lastX, const int lastY, const int noX, const int noY, const int think_time){
	/*
		��Ҫ������δ���
	*/
	int x = -1, y = -1;//���ս�������ӵ�浽x,y��
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
		for(int j = 0; j < N; j++){
			board[i][j] = _board[i * N + j];
		}
	}
	
	/*
		�������Լ��Ĳ������������ӵ�,Ҳ���Ǹ�����Ĳ�����ɶ�x,y�ĸ�ֵ
		�ò��ֶԲ���ʹ��û�����ƣ�Ϊ�˷���ʵ�֣�����Զ����Լ��µ��ࡢ.h�ļ���.cpp�ļ�
	*/
	bool win_lose_flag = false;
	int* _top = new int[N];
	for (int i = 0; i < N; i++) _top[i] = top[i];
	for (int i = 0; i < N && !win_lose_flag; i++){
		if(_top[i]){
			board[_top[i] - 1][i] = 2;
			if (machineWin(_top[i] - 1,i,M,N,board)) win_lose_flag = true,x = _top[i] - 1,y = i;
			board[_top[i] - 1][i] = 0;
		}
	}
	for (int i = 0; i < N && !win_lose_flag; i++){
		if(_top[i]){
			board[_top[i] - 1][i] = 1;
			if (userWin(_top[i] - 1,i,M,N,board)) win_lose_flag = true,x = _top[i] - 1,y = i;
			board[_top[i] - 1][i] = 0;
		}
	}
	if (!win_lose_flag){
		Node *v0 = new Node;
		v0->father = NULL, v0->Num = v0->Q = 0;
		bool v0_flag = true;
		for (int i = 0; i < N && v0_flag; i++){
			if (_top[i]) v0_flag = false,v0->a = i;
		}
		if (v0_flag) v0->a = N;
		std::time_t Start = time(nullptr);
		int count = 0;
		while (time(nullptr) - Start < think_time){
			Node* vl = TreePolicy(v0,M,N,board,noX,noY,_top,0.9);
			int delta = DefaultPolicy(vl,M,N,board,noX,noY,_top);
			Backup(vl,delta);
			for(int i = 0; i < M; i++){
				for(int j = 0; j < N; j++){
					board[i][j] = _board[i * N + j];
				}
			}
			for (int i = 0; i < N; i++) _top[i] = top[i];
			count++;
		}
		Node* Result = BestChild(v0,0);
		y = Result->route[0];
		x = top[y] - 1;
		delete[] _top;
		delete v0;
	}
	/*
		��Ҫ������δ���
	*/
	clearArray(M, N, board);
	return y;
}

/*
	���top��board����
*/
void clearArray(int M, int N, int** board){
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}
