#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int get_total_available_moves(char game_state[9]){
    int total_empty = 0;
    for (int i=0; i<9;i++){
        if (game_state[i]==' '){
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
    char empty_str = ' ';

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

int decide_game(char game_state[], char player)
{
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

    // Decide if current player win the game.
    for (int i = 0; i < 8; i++)
    {
        total_count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (game_state[win_rules[i][j]] == player)
            {
                total_count+=1;
            }
        }
        if (total_count == 3)
        {
            return 1;
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
    if (total_moves == 9)
    {
        return 0;
    }
    // Continue Program
    return -1;
}

int make_random_move(int available_moves[], int total_available_moves){
    srand(time(0));
    int random_index = (rand() % total_available_moves);
    return available_moves[random_index];
}

int check_input_valid(int available_moves[], int total_available_move, int move_id_){
    // Input type : Int, input value in available_moves
    // 0 - invalid input
    // 1 - valid input
    int valid = 0;
    // TODO : Check for string input.
    for (int i=0; i<total_available_move; i++){
        if (available_moves[i] == move_id_){
            valid = 1;
        }
    }
    return valid;
}

int make_move(int available_moves[], int total_available_moves){
    int move_id_;

    do {
        printf("Enter your next move:  ");
        scanf("%d", &move_id_);
        printf("Your next move is : %d", move_id_);
    }while(check_input_valid(available_moves, total_available_moves, move_id_) == 0);
    return move_id_;
}


int main(void)
{
    int *available_moves;
    printf("Starting Tic Tac Toe Game.\n");
    // Initialize Game
    char game_state[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    // Initialize Players
    char player1 = 'o';
    char player2 = 'x';
    char current_player = player1;
    char players[2] = {player1, player2};

    int total_moves = 0;
    int move_id;
    // printf("%d", decide_game(game_state, current_player));

    while(decide_game(game_state, current_player)==-1){
        // Display current game status
        print_game_state(game_state);

        // Get available moves for players
        available_moves = get_available_moves(game_state);
        // Display available moves for players
        int total_available_moves = get_total_available_moves(game_state);
        print_available_moves(available_moves, total_available_moves);

        // Player decide move based on available moves
        move_id = make_move(available_moves, total_available_moves);
        total_moves++;
        // Display player move
        printf("\nMake Move : %d, %c, %d\n", total_moves, current_player, move_id);

        // Update game state
        update_game(game_state, move_id, current_player);


        // If current player win
        if(decide_game(game_state, current_player)==1){
            printf("Win : %c", current_player);
            return 0;
        }
        // If draw
        else if (decide_game(game_state, current_player)==0){
            printf("Draw");
            return 0;
        }

        current_player = players[total_moves%2];
    }
}