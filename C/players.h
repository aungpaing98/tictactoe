// 0: Random move
// 1: User Input move
// 2: MinMax Move

int random_move(char game_state[9], char player);

int user_move(char game_state[9], char player);

int minmax(char game_state[9], int maximize);

int *get_minmax_score(char game_state[9], char player);

int minmax_move(char game_state[9], char player);

int make_move(char game_state[9], char player, int mode);