// 0: Random move
// 1: User Input move
// 2: MinMax Move

int random_move(int available_moves[], int total_available_moves);

int user_move(int available_moves[], int total_available_moves);

int minmax(char game_state[9], int maximize);

int minmax_move(char game_state[9], char player);

int make_move(char game_state[9], int available_moves[9], int total_available_moves, char player, int mode);