import { minmax_move, random_move, user_move } from "./utils.js";

class Player {
  constructor(name) {
    this.name = name;
  }

  makeMove(game) {
    return;
  }
}

class HumanPlayer extends Player {
  constructor(name = "o") {
    super(name);
  }

  makeMove(game) {
    return user_move(game, this.name);
  }
}

class AIPlayer extends Player {
  constructor(name = "x") {
    super(name);
  }

  makeMove(game) {
    return minmax_move(game, this.name, 1);
  }
}

export { HumanPlayer, AIPlayer };
