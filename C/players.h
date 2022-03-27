// 0: Random move
// 1: User Input move
// 2: MinMax Move
// 3: MinMax Alpha Beta

int random_move(char game_state[9], char player);

int user_move(char game_state[9], char player);

int minmax(char game_state[9], int maximize);
int minmax_alpha_beta(char game_state[9], int maximize, int alpha, int beta);

int *get_minmax_score(char game_state[9], char player, int alpha_beta);

int minmax_move(char game_state[9], char player, int alpha_beta);

int make_move(char game_state[9], char player, int mode);
