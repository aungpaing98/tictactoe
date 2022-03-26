#include <stdio.h>
#include <stdlib.h>

char *init_board(){
    char *game_state = malloc(sizeof(char) * 9);
    for (int i=0; i<9; i++){
        game_state[i] = ' ';
    }
    return game_state;
}

void print_game_state(char game_state[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf("\n- - -\n");
        }
        printf("%c ", game_state[i]);
    }
    printf("\n");
}

void update_game(char game_state[9], int move_id, char player)
{
    game_state[move_id] = player;
}

int get_total_available_moves(char game_state[9])
{
    int total_empty = 0;
    for (int i = 0; i < 9; i++)
    {
        if (game_state[i] == ' ')
        {
            total_empty++;
        }
    }
    return total_empty;
}

int *get_available_moves(char game_state[9])
{
    // Get available moves from current game state
    int *available_moves = malloc(sizeof(int) * 9);
    int total_available_moves = 0;
    // iterate to find the available move
    for (int i = 0; i < 9; i++)
    {
        if (game_state[i] == ' ')
        {
            available_moves[total_available_moves] = i;
            total_available_moves++;
        }
    }
    return available_moves;
}

void print_available_moves(int available_moves[], int total_available_moves)
{
    printf("Available Moves : ");
    for (int i = 0; i < total_available_moves; i++)
    {
        printf("%d ", available_moves[i]);
    }
    printf("\n");
}

char *copy_board(char game_state[9])
{
    // Copy game board
    char *new_game = malloc(sizeof(char) * 9);
    for (int i = 0; i < 9; i++)
    {
        new_game[i] = game_state[i];
    }
    return new_game;
}

int decide_game(char game_state[], char player)
{
    // 1 : current player win,
    // 0 : Draw,
    // -1 : Continue game
    int win_rules[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};
    int total_count;
    int total_moves = 0;
    int ret = -1;
    // Decide if current player win the game.
    for (int i = 0; i < 8; i++)
    {
        total_count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (game_state[win_rules[i][j]] == player)
            {
                total_count += 1;
            }
        }
        if (total_count == 3)
        {
            ret = 1;
            break;
        }
    }
    // Decide for Draw
    for (int i = 0; i < 9; i++)
    {
        if (game_state[i] != ' ')
        {
            total_moves++;
        }
    }
    if (total_moves == 9 && ret != 1)
    {
        ret = 0;
    }
    // Continue Program
    return ret;
}

