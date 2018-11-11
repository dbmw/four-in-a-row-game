#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void help(){
    cout << "欢迎游玩重力四子棋小游戏！\n"
        << "基本游戏规则：\n"
        << "1、双方轮流落子；\n"
        << "2、每次只能在列顶落子；\n"
        << "3、先完成四连子（或四连子以上）者胜，若直到棋盘满尚未决出胜负，则为平局。\n"
        << "拓展规则：\n"
        << "随机棋盘大小：宽高均为[9,12]范围内的随机数；\n"
        << "随机不可落子点：在生成棋盘时，随机生成一个不可落子点。\n"
        << "以上为规则的全部内容，请开始尽情的游玩吧！\n\n";
}

void setting(int &M, int &N, int &first_player, int &think_time){
    cout << "目前的游戏参数设置如下：\n";
    cout << "棋盘大小：";
    if (M) cout << M;
    else cout << "随机";
    cout << " * ";
    if (N) cout << N << ";\n";
    else cout << "随机;\n";
    cout << "先手玩家：";
    switch (first_player){
    case 0: cout << "随机；\n";break;
    case 1: cout << "玩家1（对战模式）/玩家（单机模式）；\n";break;
    case 2: cout << "玩家2（对战模式）/电脑（单机模式）；\n";break;
    }
    cout << "单机模式下电脑思考时间：" << think_time << "s。\n";
    int key;
    for(;;){
        cout << "需要设置哪项属性？\n"
            << "（输入\'0\'设置棋盘大小，\'1\'设置先手玩家，\'2\'设置电脑思考时间）\n"
            << "（输入\'-1\'以结束设置）\n>>";
        cin >> key;
        switch(key){
        case -1: cout << "设置结束。\n\n";return;
        case 0:
            do{
            cout << "请输入新的行数。（在[9,12]范围内）\n（输入\'0\'以随机生成行数）\n>>";
            cin >> M;
            if (M && (M < 9 || M > 12)) cout << "无效输入，请重新输入。\n";
            }while (M && (M < 9 || M > 12));
            do{
            cout << "请输入新的列数。（在[9,12]范围内）\n（输入\'0\'以随机生成列数）\n>>";
            cin >> N;
            if (N && (N < 9 || N > 12)) cout << "无效输入，请重新输入。\n";
            }while (N && (N < 9 || N > 12));
            break;
        case 1:
            do{
            cout << "请输入先手玩家。\n\'1\'对应玩家1（对战模式）/玩家（单机模式）；\n\'2\'对应玩家2（对战模式）/电脑（单机模式）；\n\'0\'对应随机决定。\n>>";
            cin >> first_player;
            if (first_player < 0 || first_player > 2) cout << "无效输入，请重新输入。\n";
            }while (first_player < 0 || first_player > 2);
            break;
        case 2:
            do{
                cout << "请输入电脑每回合的思考时间，以秒为单位。\n(您应该输入一个正整数；）\n（理论上，思考时间越久，AI越强。）\n>>";
                cin >> think_time;
                if (think_time <= 0) cout << "无效输入，请重新输入。\n";
            }while(think_time <= 0);
            break;
        }
        cout << "本项设置完成，还";
    }
}

void output(int *_board, int M, int N, int noX, int noY){
    for (int i = -1; i <= M; i++){
        for (int j = -1; j <= N; j++){
            if (i < 0 || i == M){
                if (j < 0 || j == N) cout << "   ";
                else cout << setw(3) << j;
            }
            else{
                if (j < 0 || j == N) cout << setw(3) << i;
                else{
                    if (i == noX  && j == noY) cout << "  X";
                    else{
                        switch(_board[i * N + j]){
                        case 0: cout << "  O";break;
                        case 1: cout << "  *";break;
                        case 2: cout << "  /";break;
                        }
                    }
                }
            }
        }
        cout << endl << endl;
    }
}

void output(int **board, int M, int N, int noX, int noY){
    for (int i = -1; i <= M; i++){
        for (int j = -1; j <= N; j++){
            if (i < 0 || i == M){
                if (j < 0 || j == N) cout << "   ";
                else cout << setw(3) << j;
            }
            else{
                if (j < 0 || j == N) cout << setw(3) << i;
                else{
                    if (i == noX  && j == noY) cout << "  X";
                    else{
                        switch(board[i][j]){
                        case 0: cout << "  O";break;
                        case 1: cout << "  *";break;
                        case 2: cout << "  /";break;
                        }
                    }
                }
            }
        }
        cout << endl << endl;
    }
}

void new_top(int *top, int noX, int noY, int lastY){
    if (--top[lastY] == (1 + noX) && lastY == noY) --top[lastY];
}

int valid_input(int *top, int N){
    bool not_valid = false;
    int output;
    do{
        cout << "您要下在那一列？请输入列号。\n>>";
        cin >> output;
        not_valid = (output < 0 || output >= N || !top[output]);
        if (not_valid) cout << "输入的列已满或不存在，请重新输入！\n";
    }while(not_valid);
    return output;
}

void output(int **board, int M, int N, int noX, int noY, ofstream &file){
    for (int i = -1; i <= M; i++){
        for (int j = -1; j <= N; j++){
            if (i < 0 || i == M){
                if (j < 0 || j == N) file << "     ";
                else if (j < 10) file << "   " << j;
                else file << " " << j;
            }
            else{
                if (j < 0 || j == N) {
                    if (i < 10) file << "   " << i;
                    else file << " " << i;
                }
                else{
                    if (i == noX  && j == noY) file << "  X";
                    else{
                        switch(board[i][j]){
                        case 0: file << "   0";break;
                        case 1: file << "   1";break;
                        case 2: file << "   2";break;
                        }
                    }
                }
            }
        }
        file << endl << endl;
    }
}