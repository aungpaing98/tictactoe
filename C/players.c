#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "board.h"

// 0: Random move
// 1: User Input Move
// 2: MinMax Move

int random_move(int available_moves[], int total_available_moves)
{
    srand(time(0));
    int random_index = (rand() % total_available_moves);
    return available_moves[random_index];
}

int user_move(int available_moves[], int total_available_moves)
{
    int move_id_;
    do
    {
        printf("Enter your next move:  ");
        scanf("%d", &move_id_);
    } while (check_input_valid(available_moves, total_available_moves, move_id_) == 0);
    return move_id_;
}

int minmax(char game_state[9], int maximize)
{
    // 'o' : Human, 'x' : AI
    char players[2] = {'o', 'x'};
    int scores[2] = {-1, 1};
    char pre_player = players[!(maximize)];
    char current_player = players[maximize];
    int win_loss_draw = decide_game(game_state, pre_player);
    if (win_loss_draw == 1)
    {
        return scores[!(maximize)];
    }
    else if (win_loss_draw == 0)
    {
        return 0;
    }
    if (maximize == 1)
    {
        int value = -1000;
        int *available_moves = get_available_moves(game_state);
        int total_available_moves = get_total_available_moves(game_state);
        for (int i = 0; i < total_available_moves; i++)
        {
            update_game(game_state, available_moves[i], current_player);
            value = max(value, minmax(game_state, 0));
            update_game(game_state, available_moves[i], ' ');
        }
        return value;
    }
    else
    {
        int value = 1000;
        int *available_moves = get_available_moves(game_state);
        int total_available_moves = get_total_available_moves(game_state);
        for (int i = 0; i < total_available_moves; i++)
        {
            update_game(game_state, available_moves[i], current_player);
            value = min(value, minmax(game_state, 1));
            update_game(game_state, available_moves[i], ' ');
        }
        return value;
    }
}

int minmax_move(char game_state[9], char player)
{
    int *available_moves = get_available_moves(game_state);
    int total_available_moves = get_total_available_moves(game_state);
    int scores[9];
    int moveId;
    printf("\nScores :");
    for (int i = 0; i < total_available_moves; i++)
    {
        update_game(game_state, available_moves[i], player);
        scores[i] = minmax(game_state, 0);
        update_game(game_state, available_moves[i], ' ');
        printf(" %d ", scores[i]);
    }
    printf("\n");
    moveId = available_moves[argmax(scores, total_available_moves)];
    return moveId;
}

int make_move(char game_state[9], int available_moves[9], int total_available_moves, char player, int mode)
{
    int moveId;
    switch (mode)
    {
    case 0:
        moveId = random_move(available_moves, total_available_moves);
        break;
    case 1:
        moveId = user_move(available_moves, total_available_moves);
        break;
    case 2:
        moveId = minmax_move(game_state, player);
        break;
    
    default:
        moveId = random_move(available_moves, total_available_moves);
        break;
    }
    return moveId;
}
