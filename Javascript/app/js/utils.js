const argmax = (arr) => {
  let ret = 0;
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] > arr[ret]) {
      ret = i;
    }
  }
  return ret;
};

const minmax_alpha_beta = (game, maximize, alpha, beta) => {
  let players = ["o", "x"];
  let scores = [-1, 1];
  let pre_player = players[!maximize + 0];
  let current_player = players[maximize + 0];
  let win_loss_draw = game.decideGame(pre_player);

  // Base case
  if (win_loss_draw == 1) {
    return scores[!maximize + 0] * (game.getAvailableMoves().length + 1);
  } else if (win_loss_draw == 0) {
    return 0;
  }

  if (maximize) {
    let value = -1000;
    let val;
    let available_moves = game.getAvailableMoves();
    available_moves.every((move) => {
      game.updateBoard(move, current_player);
      val = minmax_alpha_beta(game, false, alpha, beta);
      game.updateBoard(move, " ");

      value = Math.max(value, val);
      alpha = Math.max(alpha, value);
      if (beta <= alpha) {
        return false;
      }
      return true;
    });
    return value;
  } else {
    let value = 1000;
    let val;
    let available_moves = game.getAvailableMoves();
    available_moves.every((move) => {
      game.updateBoard(move, current_player);
      val = minmax_alpha_beta(game, true, alpha, beta);
      game.updateBoard(move, " ");

      value = Math.min(value, val);
      beta = Math.min(beta, value);
      if (beta <= alpha) {
        return false;
      }
      return true;
    });
    return value;
  }
};

const minmax = (game, maximize) => {
  let players = ["o", "x"];
  let scores = [-1, 1];
  let pre_player = players[!maximize + 0];
  let current_player = players[maximize + 0];
  let win_loss_draw = game.decideGame(pre_player);

  // Base case
  if (win_loss_draw == 1) {
    return scores[!maximize + 0] * (game.getAvailableMoves().length + 1);
  } else if (win_loss_draw == 0) {
    return 0;
  }

  if (maximize) {
    let value = -1000;
    let available_moves = game.getAvailableMoves();
    available_moves.forEach((move) => {
      game.updateBoard(move, current_player);
      value = Math.max(value, minmax(game, false));
      game.updateBoard(move, " ");
    });
    return value;
  } else {
    let value = 1000;
    let available_moves = game.getAvailableMoves();
    available_moves.forEach((move) => {
      game.updateBoard(move, current_player);
      value = Math.min(value, minmax(game, true));
      game.updateBoard(move, " ");
    });
    return value;
  }
};

const get_minmax_score = (game, name, alpha_beta) => {
  let available_moves = game.getAvailableMoves();
  let scores = [];
  let score;
  available_moves.forEach((move) => {
    game.updateBoard(move, name);
    if (alpha_beta == 1) {
      score = minmax_alpha_beta(game, name == "o", -1000, 1000);
    } else {
      score = minmax(game, name == "o");
    }
    game.updateBoard(move, " ");
    scores.push(score);
  });
  return scores;
};

const minmax_move = (game, name, alpha_beta) => {
  let scores = get_minmax_score(game, name, alpha_beta);
  console.log("Scores : ", scores);

  let available_moves = game.getAvailableMoves();
  return available_moves[argmax(scores)];
};

const random_move = (game, name) => {
  let available_moves = game.getAvailableMoves();
  let random_id = Math.floor(Math.random() * available_moves.length);
  return available_moves[random_id];
};

const get_user_input = () => {
  const cells = document.querySelectorAll(".cell");
  cells.forEach((cell) => {
    cell.addEventListener("click", (event) => {
      console.log("Clicking : ", event.target.id);
      return event.target.id;
    });
  });
};


export { argmax, get_minmax_score, minmax_move, random_move };
