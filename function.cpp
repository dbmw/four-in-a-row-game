#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void help(){
    cout << "��ӭ��������������С��Ϸ��\n"
        << "������Ϸ����\n"
        << "1��˫���������ӣ�\n"
        << "2��ÿ��ֻ�����ж����ӣ�\n"
        << "3������������ӣ������������ϣ���ʤ����ֱ����������δ����ʤ������Ϊƽ�֡�\n"
        << "��չ����\n"
        << "������̴�С����߾�Ϊ[9,12]��Χ�ڵ��������\n"
        << "����������ӵ㣺����������ʱ���������һ���������ӵ㡣\n"
        << "����Ϊ�����ȫ�����ݣ��뿪ʼ���������ɣ�\n\n";
}

void setting(int &M, int &N, int &first_player, int &think_time){
    cout << "Ŀǰ����Ϸ�����������£�\n";
    cout << "���̴�С��";
    if (M) cout << M;
    else cout << "���";
    cout << " * ";
    if (N) cout << N << ";\n";
    else cout << "���;\n";
    cout << "������ң�";
    switch (first_player){
    case 0: cout << "�����\n";break;
    case 1: cout << "���1����սģʽ��/��ң�����ģʽ����\n";break;
    case 2: cout << "���2����սģʽ��/���ԣ�����ģʽ����\n";break;
    }
    cout << "����ģʽ�µ���˼��ʱ�䣺" << think_time << "s��\n";
    int key;
    for(;;){
        cout << "��Ҫ�����������ԣ�\n"
            << "������\'0\'�������̴�С��\'1\'����������ң�\'2\'���õ���˼��ʱ�䣩\n"
            << "������\'-1\'�Խ������ã�\n>>";
        cin >> key;
        switch(key){
        case -1: cout << "���ý�����\n\n";return;
        case 0:
            do{
            cout << "�������µ�����������[9,12]��Χ�ڣ�\n������\'0\'���������������\n>>";
            cin >> M;
            if (M && (M < 9 || M > 12)) cout << "��Ч���룬���������롣\n";
            }while (M && (M < 9 || M > 12));
            do{
            cout << "�������µ�����������[9,12]��Χ�ڣ�\n������\'0\'���������������\n>>";
            cin >> N;
            if (N && (N < 9 || N > 12)) cout << "��Ч���룬���������롣\n";
            }while (N && (N < 9 || N > 12));
            break;
        case 1:
            do{
            cout << "������������ҡ�\n\'1\'��Ӧ���1����սģʽ��/��ң�����ģʽ����\n\'2\'��Ӧ���2����սģʽ��/���ԣ�����ģʽ����\n\'0\'��Ӧ���������\n>>";
            cin >> first_player;
            if (first_player < 0 || first_player > 2) cout << "��Ч���룬���������롣\n";
            }while (first_player < 0 || first_player > 2);
            break;
        case 2:
            do{
                cout << "���������ÿ�غϵ�˼��ʱ�䣬����Ϊ��λ��\n(��Ӧ������һ������������\n�������ϣ�˼��ʱ��Խ�ã�AIԽǿ����\n>>";
                cin >> think_time;
                if (think_time <= 0) cout << "��Ч���룬���������롣\n";
            }while(think_time <= 0);
            break;
        }
        cout << "����������ɣ���";
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
        cout << "��Ҫ������һ�У��������кš�\n>>";
        cin >> output;
        not_valid = (output < 0 || output >= N || !top[output]);
        if (not_valid) cout << "������������򲻴��ڣ����������룡\n";
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