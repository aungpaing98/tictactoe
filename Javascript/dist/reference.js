class Player {
  constructor(name) {
    this.name = name;
  }

  makeMove(game) {
    return;
  }
}

class Human extends Player {
  constructor(name) {
    super(name);
  }

  makeMove(game) {
    return;
  }
}

class Robot extends Player {
  constructor(name) {
    super(name);
  }

  randomMove(game) {
    let avaMoves = game.availableMoves();
    let moveId = Math.floor(Math.random() * avaMoves.length);
    cells[avaMoves[moveId]].click();
  }

  makeMove(game) {
    let avaMoves = game.availableMoves()
    let moveLength = avaMoves.length
    let moveId = avaMoves[Math.floor(Math.random() * moveLength)]
    // Get MoveId
    let bestValue = -1000;
    for (let i=0; i<moveLength; i++){
      game.addState(avaMoves[i], robot)
      let value = this.minMax(game, 1, false)
      game.removeState(avaMoves[i])
      if (value > bestValue){
        moveId = avaMoves[i]
        bestValue = value
      }
    }
    cells[moveId].click();
  }

  minMax(game, depth, maxPlayer){
    let player = human
    if (maxPlayer){player=robot}

    let prePlayer = anotherPlayer(player)
    let isGame_ = game.isFinished(prePlayer)
    if (isGame_ != ""){return (scores[isGame_] * (10-depth))}

    let avaMoves = game.availableMoves()
    let numAvaMoves = avaMoves.length

    if (maxPlayer){
      let bestValue = -1000
      for (let i=0; i<numAvaMoves; i++){
        game.addState(avaMoves[i], player)
        let value = this.minMax(game, depth+1, false)
        bestValue = Math.max(bestValue, value)
        game.removeState(avaMoves[i])
      }
      return bestValue;
    }
    else{
      let bestValue = 1000
      for (let i=0; i<numAvaMoves; i++){
        game.addState(avaMoves[i], player)
        let value = this.minMax(game, depth+1, true)
        bestValue = Math.min(bestValue, value)
        game.removeState(avaMoves[i])
      }
      return bestValue;
    }
  }
}



class Game {
  constructor(gameState) {
    this.gameState = gameState;
  }

  availableMoves() {
    let avaMoves = [];
    for (let i = 0; i < 9; i++) {
      if (this.gameState[i] == "") {
        avaMoves.push(i);
      }
    }
    return avaMoves;
  }

  addState(moveId, player) {
    this.gameState[moveId] = player.name;
  }

  removeState(moveId) {
    this.gameState[moveId] = "";
  }

  isFinished(player) {
    let gameResult_ = "";
    const res = winRule
      .map((rule) =>
        rule
          .map((eachCell) => this.gameState[eachCell - 1] == player.name)
          .every((res) => res == true)
      )
      .some((res) => res == true);

    if (res) {
      gameResult_ = player.name;
    } else if (this.availableMoves().length == 0) {
      gameResult_ = "draw";
    }
    return gameResult_;
  }
}
