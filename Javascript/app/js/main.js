import TicTacToe from "./Game.js";
import { HumanPlayer, AIPlayer } from "./Players.js";
import { argmax, get_minmax_score, minmax_move, random_move } from "./utils.js";

// Initialize player
let human = new HumanPlayer();
let ai = new AIPlayer();
let players = [human, ai];
let total_moves = 0;
let current_player = players[total_moves];
let game = new TicTacToe();

// Control + View
// Queries
const cells = document.querySelectorAll(".cell");
const gameTag = document.querySelector(".game");
const container = document.querySelector(".container");
const winner = document.querySelector(".winner_message");
const nextRound = document.querySelector(".next_round");
const algorithm = document.querySelector("#algorithm");


// Restart game (Control)
nextRound.addEventListener("click", (e) => {
  location.reload();
});

// Control + View
const handleFinish = (gameResult) => {
  gameTag.classList.add("win");
  let text = "Draw"
  
  if (gameResult==1){
    text = `Win : ${current_player.name}`
  }
  let textContext = text;
  let finishElement = document.createElement("h1");
  finishElement.textContent = textContext;
  // winner.appendChild(finishElement);
  winner.insertBefore(finishElement, winner.firstChild)
};

// Control + View
const clickHandler = (event) => {
  let moveId = event.target.id;
  game.updateBoard(moveId, current_player.name);
  cells[moveId].classList.add(current_player.name);
  cells[moveId].classList.remove("o_hover");
  total_moves += 1;
  
  let win_loss_draw = game.decideGame(current_player.name);
  if (win_loss_draw != -1) {
    handleFinish(win_loss_draw);
  }
  current_player = players[total_moves % 2];
};

// Control + Model
const getAIMove = (event) => {
  let mode = algorithm.options[algorithm.selectedIndex].value
  if (current_player.name == "x") {
    let moveId = ai.makeMove(game, mode);
    cells[moveId].click();
  }
};

// Control
cells.forEach((cell) => {
  cell.addEventListener("click", clickHandler, { once: true });
});

cells.forEach((cell) => {
  cell.addEventListener("click", getAIMove);
});
