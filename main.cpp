#include <iostream>
#include <fstream>
#include <ctime>
#include <stack>
#include "Strategy.h"
#include "function.h"
#include "Judge.h"
using namespace std;

int main(){
    cout << "欢迎游玩重力四子棋！\n";
    srand((unsigned)time(nullptr));
    int M = 0, N = 0, current_player = 0, think_time = 3;
    int not_to_start;
    do{
        cout << "输入\'0\'以从当前设置开始游戏；\n输入\'1\'以修改设置；\n输入\'2\'以查看帮助。\n>>";
        cin >> not_to_start;
        switch(not_to_start){
        case 1: setting(M,N,current_player,think_time);break;
        case 2: help();break;
        case 0: cout << endl;
        }
    }while(not_to_start);

    //棋盘随机初始化
    if (!current_player) current_player = rand() % 2 + 1;
    if (!M) M = rand() % 4 + 9;
    if (!N) N = rand() % 4 + 9;
    int noX = rand() % M, noY = rand() % N;
    int *top = new int[N];
    for (int i = 0; i < N; i++){
        top[i] = M;
        if (noX == M - 1 && noY == i) top[i] = M - 1;
    }
    int *_board = new int[M * N](),step_num = 0;
    stack<int> lastX,lastY;

    int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N]();
	}
    bool is_pve;
    cout << "输入\'1\'进入单机对战，\'0\'进入双人对战。\n>>";
    cin >> is_pve;
    bool can_continue = true;
    current_player = !(current_player - 1) + 1;
    do{
        current_player = !(current_player - 1) + 1;
        if (current_player == 2){
            if (is_pve) lastY.push(getPoint(M,N,top,_board,0,0,noX,noY,think_time));
            else{
                cout << endl << endl;
                output(board,M,N,noX,noY);
                cout << endl;
                lastY.push(valid_input(top,N));
            }
            lastX.push(top[lastY.top()] - 1);
            new_top(top,noX,noY,lastY.top());
            _board[lastX.top() * N + lastY.top()] = 2;
            board[lastX.top()][lastY.top()] = 2;
            can_continue = !machineWin(lastX.top(),lastY.top(),M,N,board);
            if (can_continue) can_continue = !isTie(N,top);
        }
        else{
            cout << endl << endl;
            output(board,M,N,noX,noY);
            cout << endl;
            lastY.push(valid_input(top,N));
            lastX.push(top[lastY.top()] - 1);
            new_top(top,noX,noY,lastY.top());
            _board[lastX.top() * N + lastY.top()] = 1;
            board[lastX.top()][lastY.top()] = 1;
            can_continue = !userWin(lastX.top(),lastY.top(),M,N,board);
            if (can_continue) can_continue = !isTie(N,top);
        }
    }while(can_continue);
    cout << endl << endl;
    output(_board,M,N,noX,noY);
    if (isTie(N,top)) cout << "平局！\n";
    else cout << "玩家" << current_player << "获胜！\n";
    ofstream FILE("result_output.txt",ios_base::out|ios_base::app);
    output(board,M,N,noX,noY,FILE);
    FILE.close();
    cout << "输入任意数字结束游戏。\n>>";
    cin >> not_to_start;
    return 0;
}
