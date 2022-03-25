int min(int a, int b);
int max(int a, int b);
int argmax(int a[], int len_a);

void print_game_state(char game_state[9]);

void update_game(char game_state[9], int move_id, char player);

int get_total_available_moves(char game_state[9]);

int *get_available_moves(char game_state[9]);

void print_available_moves(int available_moves[], int total_available_moves);

char *copy_board(char game_state[9]);

int decide_game(char game_state[], char player);

int check_input_valid(int available_moves[], int total_available_moves, int move_id_);

int random_move(int available_moves[], int total_available_moves);

int user_move(int available_moves[], int total_available_moves);

int minmax(char game_state[9], int maximize);

int minmax_move(char game_state[9], char player);

int make_move(char game_state[9], int available_moves[9], int total_available_moves);
