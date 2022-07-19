/*
 * @Author GIUSEPPE MUSCHETTA
 */

/* How the amazing MINIMAX-DECISION algorithm actually work,
 * please note that in this version we implemented the
 * ALPHA-BETA pruning technique to reduce the number of recursive calls
 */

#include "TicTacToe.h"

int main() {
    TicTacToe game;
    game.blank_cells = N_CELLS;
    game.winner = DRAW;
    game.grid = malloc(sizeof(int) * N_CELLS);
    for (int i = 0; i < N_CELLS; ++i)
        game.grid[i] = 0;
    printf("Welcome to Tic-Tac-Toe!\n");
    game.current_CPU = coin_toss();
    game.current_CPU == CPU1 ? printf("CPU1 starts!\n") : printf("CPU2 starts!\n");
    while (game.blank_cells > 0 && game.winner == DRAW) {
        print_grid(game);
        make_a_move(&game);
        game.winner = check_winner(game);
        game.current_CPU *= -1;
    }
    print_grid(game);
    if (game.winner == CPU1)
        printf("CPU1 wins!\n");
    else if (game.winner == CPU2)
        printf("CPU2 wins!\n");
    else printf("Draw!\n");
    return EXIT_SUCCESS;
}

int MASSIMO(int a, int b){
    return (a > b ? a : b);
}

int MINIMO(int a, int b){
    return (a < b ? a : b);
}

void make_a_move(TicTacToe* game) {
    if (game->current_CPU == CPU1) {
        int best_action = MINIMAX_decision1(*game);
        game->grid[best_action] = CPU1;
    } else {
        int best_action = MINIMAX_decision2(*game);
        game->grid[best_action] = CPU2;
    }
    game->blank_cells--;
}

int MINIMAX_decision1(TicTacToe game) {
    int best_action = -1;
    int best_value = -2;    // -Inf
    for (int i = 0; i < N_CELLS; ++i) {
        if (game.grid[i] == 0) {
            int value = MIN_value(result(game, i),-2,2);
            if (value > best_value) {
                best_value = value;
                best_action = i;
            }
        }
    }
    return best_action;
}

int MINIMAX_decision2(TicTacToe game) {
    int best_action = -1;
    int best_value = 2;    // Inf
    for (int i = 0; i < N_CELLS; ++i) {
        if (game.grid[i] == 0) {
            int value = MAX_value(result(game, i),-2,2);
            if (value < best_value) {
                best_value = value;
                best_action = i;
            }
        }
    }
    return best_action;
}

int MIN_value(TicTacToe game, int alpha, int beta) {
    if (terminal_test(game))
        return check_winner(game);
    int value = 2;     // +Inf
    for (int i = 0; i < N_CELLS; ++i) {
        if (game.grid[i] == 0)
            value = MINIMO(value, MAX_value(result(game, i),alpha,beta));
        if(value <= alpha)
            return value;
        beta = MINIMO(beta,value);
    }
    return value;
}

int MAX_value(TicTacToe game, int alpha, int beta) {
    if (terminal_test(game))
        return check_winner(game);
    int value = -2;    // -Inf
    for (int i = 0; i < N_CELLS; ++i) {
        if (game.grid[i] == 0) {
            value = MASSIMO(value,MIN_value(result(game, i),alpha,beta));
        }
        if (value >= beta)
            return value;
        alpha = MASSIMO(alpha,value);
    }
    return value;
}

// Transition model
TicTacToe result(TicTacToe game, int action) {
    TicTacToe simulated_game;
    simulated_game.winner = DRAW;
    simulated_game.blank_cells = game.blank_cells;
    simulated_game.current_CPU = game.current_CPU;
    simulated_game.grid = malloc(sizeof(int) * N_CELLS);
    for (int i = 0; i < N_CELLS; ++i)
        simulated_game.grid[i] = game.grid[i];
    simulated_game.grid[action] = simulated_game.current_CPU;
    simulated_game.blank_cells--;
    simulated_game.current_CPU *= -1;
    return simulated_game;
}

int coin_toss() {
    srand(time(NULL));
    printf("Coin toss: ");
    int first_player = (rand() % 2);
    if (first_player == CPU1)
        return CPU1;
    return CPU2;
}

void print_grid(TicTacToe game) {
    printf("Current configuration:\n");
    for (int i = 0; i < N_CELLS; ++i) {
        switch (game.grid[i]) {
            case CPU1:
                printf(" O ");
                break;
            case 0:
                printf(" . ");
                break;
            case CPU2:
                printf(" X ");
                break;
            default:
                fprintf(stderr, "Internal error");
                exit(1);
        }
        if (i == 2 || i == 5)
            printf("\n");
    }
    printf("\n\n");
}

// Utility function
int check_winner(TicTacToe game) {
    int wins[8][3] = {{0, 1, 2},
                      {3, 4, 5},
                      {6, 7, 8},
                      {0, 3, 6},
                      {1, 4, 7},
                      {2, 5, 8},
                      {0, 4, 8},
                      {2, 4, 6}};
    for (int i = 0; i < 8; ++i) {
        if (game.grid[wins[i][0]] != 0 &&
            game.grid[wins[i][0]] == game.grid[wins[i][1]] &&
            game.grid[wins[i][0]] == game.grid[wins[i][2]])
            return game.grid[wins[i][0]];
    }
    return DRAW;
}

// Terminal test
bool terminal_test(TicTacToe game) {
    return check_winner(game) != DRAW || game.blank_cells == 0;
}
