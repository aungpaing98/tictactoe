class TicTacToe {
  constructor() {
    this.init_board();
  }

  init_board = () => {
    this.game_state = [" ", " ", " ", " ", " ", " ", " ", " ", " "];
  };

  updateBoard = (moveId, player) => {
    this.game_state[moveId] = player;
  };

  decideGame = (player) => {
    let win_rules = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [2, 4, 6],
      [0, 4, 8]
    ];
    let ret = -1;

    win_rules.forEach((rule) => {
      let total_count = 0;
      for (let i = 0; i < 3; i++) {
        if (this.game_state[rule[i]] == player) {
          total_count += 1;
        } else {
          break;
        }
      }
      if (total_count == 3){
          ret = 1
      }
    });

    let total_moves = 0;
    if (ret != 1) {
      for (let i = 0; i < 9; i++) {
        if (this.game_state[i] != " ") {
          total_moves += 1;
        }
      }
      if (total_moves == 9) {
        ret = 0;
      }
    }
    return ret;
  };

  getAvailableMoves = () => {
    let available_moves = [];
    for (let i = 0; i < 9; i++) {
      if (this.game_state[i] == " ") {
        available_moves.push(i);
      }
    }
    return available_moves;
  };

  printState = () => {
    for (let i = 0; i < 9; i++) {
      if (i % 3 == 0 && i != 0) {
        console.log("\n- - -\n");
      }
      if (this.game_state[i] == " ") {
        console.log(i);
      } else {
        console.log(this.game_state[i]);
      }
    }
  };
}

export default TicTacToe;
