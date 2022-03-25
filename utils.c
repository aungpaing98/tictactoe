#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min(int a, int b)
{
    if (a <= b)
    {
        return a;
    }
    return b;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int argmax(int a[], int len_a)
{
    int ret = 0;
    for (int i = 1; i < len_a; i++)
    {
        if (a[i] > a[ret])
        {
            ret = i;
        }
    }
    return ret;
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
    static int available_moves[9];
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
    static char new_game[9];
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

int check_input_valid(int available_moves[], int total_available_move, int move_id_)
{
    // Input type : Int, input value in available_moves
    // 0 - invalid input
    // 1 - valid input
    int valid = 0;
    // TODO : Check for string input.
    for (int i = 0; i < total_available_move; i++)
    {
        if (available_moves[i] == move_id_)
        {
            valid = 1;
        }
    }
    return valid;
}

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
        // printf("\nWin : %c, %d\n", pre_player, scores[!(maximize)]);
        // print_game_state(game_state);
        return scores[!(maximize)];
    }
    else if (win_loss_draw == 0)
    {
        // printf("\nDraw.");
        // print_game_state(game_state);
        return 0;
    }
    if (maximize == 1)
    {
        int value = -100;
        int *available_moves = get_available_moves(game_state);
        int total_available_moves = get_total_available_moves(game_state);
        // print_game_state(game_state);
        // print_available_moves(available_moves, total_available_moves);
        for (int i = 0; i < total_available_moves; i++)
        {
            char *tmp_game_state = copy_board(game_state);
            update_game(tmp_game_state, available_moves[i], current_player);
            // printf("\n\nUpdated Game State:\n");
            // print_game_state(tmp_game_state);
            value = max(value, minmax(tmp_game_state, 0));
            // printf("\nValues : \t%d", value);
        }
        return value;
    }
    else
    {
        int value = 100;
        int *available_moves = get_available_moves(game_state);
        int total_available_moves = get_total_available_moves(game_state);
        // print_game_state(game_state);
        // print_available_moves(available_moves, total_available_moves);
        for (int i = 0; i < total_available_moves; i++)
        {
            char *tmp_game_state = copy_board(game_state);
            update_game(tmp_game_state, available_moves[i], current_player);
            // printf("\n\nUpdated Game State:\n");
            // print_game_state(tmp_game_state);
            value = min(value, minmax(tmp_game_state, 1));
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
    printf("Scores : ");

    for (int i = 0; i < total_available_moves; i++)
    {
        char *tmp_game_state = copy_board(game_state);
        update_game(tmp_game_state, available_moves[i], player);

        scores[i] = minmax(tmp_game_state, 0);
        printf("%d ", scores[i]);
    }
    moveId = available_moves[argmax(scores, total_available_moves)];
    return moveId;
}

int make_move(char game_state[9], int available_moves[9], int total_available_moves)
{
    // int moveId = user_move(available_moves, total_available_moves);
    // int moveId = random_move(available_moves, total_available_moves);
    int moveId = minmax_move(game_state, 'x');
    return moveId;
}
