#include <stdio.h>
#include "utils.h"


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
    int win_loss_draw = -1;
    // printf("%d", decide_game(game_state, current_player));

    while(win_loss_draw==-1){
        // Display current game status
        print_game_state(game_state);

        // Get available moves for players
        available_moves = get_available_moves(game_state);
        // Display available moves for players
        int total_available_moves = get_total_available_moves(game_state);
        print_available_moves(available_moves, total_available_moves);

        // Player decide move based on available moves
        if (current_player == 'x'){
            move_id = make_move(game_state, available_moves, total_available_moves);
        }
        else{
            move_id = user_move(available_moves, total_available_moves);
        }
        total_moves++;
        // Display player move
        printf("Move : %d, %c, %d\n\n", total_moves, current_player, move_id);

        // Update game state
        update_game(game_state, move_id, current_player);
        
        win_loss_draw = decide_game(game_state, current_player);

        // If current player win
        if(win_loss_draw==1){
            printf("Win : %c", current_player);
            return 0;
        }
        // If draw
        else if (win_loss_draw==0){
            printf("Draw");
            return 0;
        }

        current_player = players[total_moves%2];
    }
}
