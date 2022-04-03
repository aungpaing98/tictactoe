import TicTacToe from "./Game.js";
import {
  argmax,
  get_minmax_score,
  minmax_move,
  random_move,
} from "./utils.js";

let game = new TicTacToe();
game.updateBoard();
game.updateBoard(2, "o");
game.updateBoard(3, "o");
game.updateBoard(4, "o");
game.updateBoard(5, "x");
game.updateBoard(7, "x");
game.updateBoard(8, "x");
console.log(get_minmax_score(game, "x", 0));
console.log(minmax_move(game, "x", 1));

// game.updateBoard(6, 'x');
// game.printState()
// console.log(game.decideGame('x'));
