//
// Created by GIUSEPPE MUSCHETTA
//

#ifndef TRIS_TICTACTOE_H
#define TRIS_TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define CPU1 1
#define CPU2 (-1)
#define DRAW 0
#define N_CELLS 9

//this type defines the game state
typedef struct tic_tac_toe {
    int *grid;
    int blank_cells;
    int current_CPU;
    int winner;
} TicTacToe;


int coin_toss();
int MASSIMO(int, int);
int MINIMO(int, int);
void make_a_move(TicTacToe *game);
int MINIMAX_decision1(TicTacToe game);
int MINIMAX_decision2(TicTacToe game);
int MIN_value(TicTacToe game, int, int);
int MAX_value(TicTacToe game, int, int);
TicTacToe result(TicTacToe game, int action);
void print_grid(TicTacToe game);
int check_winner(TicTacToe game);
bool terminal_test(TicTacToe game);


#endif //TRIS_TICTACTOE_H
