char *init_board();

void update_game(char game_state[9], int move_id, char player);

int decide_game(char game_state[], char player);

int *get_available_moves(char game_state[9]);
int get_total_available_moves(char game_state[9]);

void print_game_state(char game_state[9]);
void print_available_moves(int available_moves[], int total_available_moves);

char *copy_board(char game_state[9]);