#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "board.h"

// 0: Random move
// 1: User Input Move
// 2: MinMax Move
// 3: MinMax Alpha Beta

// Prototypes
int *get_minmax_score(char game_state[9], char player, int alpha_beta);
// End of prototypes

int random_move(char game_state[9], char player)
{
    int *available_moves = get_available_moves(game_state);
    int total_available_moves = get_total_available_moves(game_state);
    srand(time(0));
    int random_index = (rand() % total_available_moves);
    return available_moves[random_index];
}

int user_move(char game_state[9], char player)
{

    int *available_moves = get_available_moves(game_state);
    int total_available_moves = get_total_available_moves(game_state);
    int move_id_;

    int *scores = get_minmax_score(game_state, player, 1);
    // Print Scores
    printf("Would you like to get suggesstion from minmax algo?");
    printf("\nScores \t\t: ");
    for (int i = 0; i < total_available_moves; i++)
    {
        printf("%d ", -1 * scores[i]);
    }
    printf("\n");

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
        int score_ = scores[!(maximize)] * (get_total_available_moves(game_state) + 1);
        return score_;
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

int minmax_alpha_beta(char game_state[9], int maximize, int alpha, int beta)
{
    // 'o' : Human, 'x' : AI
    char players[2] = {'o', 'x'};
    int scores[2] = {-1, 1};
    char pre_player = players[!(maximize)];
    char current_player = players[maximize];
    int win_loss_draw = decide_game(game_state, pre_player);
    if (win_loss_draw == 1)
    {
        int score_ = scores[!(maximize)] * (get_total_available_moves(game_state) + 1);
        return score_;
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
            value = max(value, minmax_alpha_beta(game_state, 0, alpha, beta));
            update_game(game_state, available_moves[i], ' ');
            alpha = max(alpha, value);
            if (beta <= alpha){
                break;
            }
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
            value = min(value, minmax_alpha_beta(game_state, 1, alpha, beta));
            update_game(game_state, available_moves[i], ' ');
            beta = min(beta, value);
            if (beta <= alpha){
                break;
            }
        }
        return value;
    }
}

int *get_minmax_score(char game_state[9], char player, int alpha_beta)
{
    int *available_moves = get_available_moves(game_state);
    int total_available_moves = get_total_available_moves(game_state);
    int *scores = malloc(sizeof(int) * 9);
    for (int i = 0; i < total_available_moves; i++)
    {
        update_game(game_state, available_moves[i], player);
        if (alpha_beta){
            scores[i] = minmax_alpha_beta(game_state, player == 'o', -1000, 1000);
        }
        else{
            scores[i] = minmax(game_state, player == 'o');
        }
        update_game(game_state, available_moves[i], ' ');
    }
    return scores;
}

int minmax_move(char game_state[9], char player, int alpha_beta)
{
    int moveId;
    int *available_moves = get_available_moves(game_state);
    int total_available_moves = get_total_available_moves(game_state);

    int *scores = get_minmax_score(game_state, player, alpha_beta);
    // Print Scores
    printf("\nScores : ");
    for (int i = 0; i < total_available_moves; i++)
    {
        printf("%d ", scores[i]);
    }
    printf("\n");


    moveId = available_moves[argmax(scores, total_available_moves)];
    return moveId;
}

int make_move(char game_state[9], char player, int mode)
{
    int moveId;
    switch (mode)
    {
    case 0:
        moveId = random_move(game_state, player);
        break;
    case 1:
        moveId = user_move(game_state, player);
        break;
    case 2:
        moveId = minmax_move(game_state, player, 0);
        break;
    case 3:
        moveId = minmax_move(game_state, player, 1);
        break;

    default:
        moveId = random_move(game_state, player);
        break;
    }
    return moveId;
}
