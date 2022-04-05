import { minmax_move, random_move } from "./utils.js";

class Player {
  constructor(name) {
    this.name = name;
  }

  makeMove(game, mode) {
    return;
  }
}

class HumanPlayer extends Player {
  constructor(name = "o") {
    super(name);
  }

  makeMove(game, mode) {
    return;
  }
}

class AIPlayer extends Player {
  constructor(name = "x") {
    super(name);
  }

  makeMove(game, mode) {
    // 0: Random move
    // 1: User input
    // 2: Minmax algorithm
    // 3: Minmax Alpha Beta algorithm
    console.log("Mode : ", mode);
    if (mode == 0) {
      return random_move(game, this.name);
    } else if (mode == 1) {
      return random_move(game, this.name);
    } else if (mode == 2) {
      return minmax_move(game, this.name, 0);
    } else {
      return minmax_move(game, this.name, 1);
    }
  }
}

export { HumanPlayer, AIPlayer };
