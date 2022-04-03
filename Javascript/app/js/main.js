import TicTacToe from "./Game.js";
import { HumanPlayer, AIPlayer } from "./Players.js";
import { argmax, get_minmax_score, minmax_move, random_move } from "./utils.js";

// Queries
const cells = document.querySelectorAll(".cell");
const gameTag = document.querySelector(".game");
const container = document.querySelector(".container");
const winner = document.querySelector(".winner");
const nextRound = document.querySelector(".next_round");
// Restart game
nextRound.addEventListener("click", (e) => {
  location.reload();
});

const handleFinish = (gameResult) => {
  gameTag.classList.add("win");
  let textContext = gameResult;
  let finishElement = document.createElement("h1");
  finishElement.textContent = textContext;
  winner.appendChild(finishElement);
};

const clickHandler = (event) => {
  let moveId = event.target.id;
  cells[moveId].classList.add(current_player.name);
};

cells.forEach((cell) => {
  cell.addEventListener("click", clickHandler, { once: true });
});

// Initialization
const game = new TicTacToe();
const human = new HumanPlayer("o");
const ai = new AIPlayer("x");
const players = [human, ai];
let total_moves = 0;
let current_player = players[total_moves];
let win_loss_draw = -1;
let moveId;

while (win_loss_draw == -1) {  
  console.log("Total move, current plyaer : ", total_moves, current_player);
  moveId = current_player.makeMove(game);
  console.log("Decided move id", moveId);

  cells[moveId].click();
  total_moves += 1;

  game.updateBoard(moveId, current_player.name);
  win_loss_draw = game.decideGame(current_player.name);

  if (win_loss_draw != 0) {
    handleFinish(win_loss_draw);
  }
  current_player = players[total_moves % 2];
}
