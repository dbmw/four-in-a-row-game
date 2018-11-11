#ifndef FUNCTION_H
#define FUNCTION_H

#include<fstream>

void help();

void setting(int &M, int &N, int &first_player, int &think_time);

void output(int *_board, int M, int N, int noX, int noY);

void output(int **board, int M, int N, int noX, int noY);

void output(int **board, int M, int N, int noX, int noY, std::ofstream& file);

void new_top(int *top, int noX, int noY, int lastY);

int valid_input(int *top, int N);
#endif