#include <stdio.h>

#include "utils.h"
#include "players.h"
#include "board.h"


int main(void)
{
    int *available_moves;
    printf("\nStarting Tic Tac Toe Game.\n");
    // Initialize Game
    char *game_state = init_board();
    // Initialize Players
    char player1 = 'o';
    char player2 = 'x';
    char players[2] = {player1, player2};

    int start_player = 0;

    printf("\nO : Human\nX: AI\n");
    printf("\nHow would you like to play?\nSelect one of the option below.\nHuman First\t: 0\nAI First\t: 1\n:");
    scanf("%d", &start_player);

    char current_player = players[start_player];

    int total_moves = 0;
    int move_id;
    int win_loss_draw = -1;
    int mode;
    while(win_loss_draw==-1){
        // Display current game status
        print_game_state(game_state);

        // Get available moves for players
        available_moves = get_available_moves(game_state);
        // Display available moves for players
        int total_available_moves = get_total_available_moves(game_state);
        print_available_moves(available_moves, total_available_moves);

        // Player decide move based on available moves
        // 0: Random move, 1: User Input, 2: MinMax
        if (current_player == 'x') mode = 2;
        else mode = 1;

        move_id = make_move(game_state, current_player, mode);
        total_moves++;
        start_player++;
        // Display player move
        printf("Move : %d, %c, %d\n\n", total_moves, current_player, move_id);

        // Update game state
        update_game(game_state, move_id, current_player);
        
        win_loss_draw = decide_game(game_state, current_player);

        // If current player win
        if(win_loss_draw==0){
            printf("Draw");
            return 0;
        }
        // If draw
        else if (win_loss_draw==1){
            printf("Win : %c", current_player);
            return 0;
        }

        current_player = players[start_player%2];
    }
}
