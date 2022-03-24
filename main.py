import random
from utils import minmax_move, random_move, user_move


class Board:
    def __init__(self):
        self.init_board()
    
    def init_board(self):
        self.game_state =  [' ' for _ in range(9)]

    def updateBoard(self, moveId, player):
        self.game_state[moveId] = player

    def decideGame(self, player):
        win_rules = [[0, 1, 2], [3, 4, 5], [6, 7, 8], [0,3,6], [1, 4, 7], [2, 5, 8], [0,4,8],[2, 4, 6]]
        # 1 for win, 0 for draw, -1 for continue
        ret = -1

        # Decide if current player win condition
        for win_rule in win_rules:
            total_count = 0
            for i in range(3):
                if self.game_state[win_rule[i]] == player:
                    total_count += 1
                    continue
                else:
                    break
            if total_count == 3:
                ret = 1
                break
        
        # Decide for draw condition
        total_moves = 0
        if ret != 1:
            for i in range(9):
                if self.game_state[i] != " ":
                    total_moves += 1
        if total_moves == 9:
            ret = 0
        # Continue the game
        return ret

    def getAvailableMoves(self):
        available_moves = []
        for i in range(9):
            if self.game_state[i] == " ":
                available_moves.append(i)
        return available_moves
    
    def printState(self):
        for i in range(9):
            if i%3 ==0 and i!=0:
                print('\n- - -')
            print(self.game_state[i], end=' ')

    def copy(self):
        game_ = Board()
        for i in range(9):
            if self.game_state[i] != " ":
                game_.updateBoard(i, self.game_state[i])
        return game_

class Player:
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return self.name

    def makeMove(self, game):
        pass

class HumanPlayer(Player):
    def __init__(self, name="o"):
        super().__init__(name)

    def makeMove(self, game):
        moveId = user_move(game.getAvailableMoves())
        return moveId

class AIPlayer(Player):
    def __init__(self, name="x"):
        super().__init__(name)

    def makeMove(self, game):
        # available_moves = game.getAvailableMoves()
        # scores = []
        # for move in available_moves:
        #     tmp_game = game.copy()
        #     tmp_game.updateBoard(move, 'x')
        #     score = minmax(tmp_game, False)
        #     scores.append(score)
        # print(f"Scores : \t{scores}")
        # moveId = available_moves[argmax(scores)]
        moveId = minmax_move(game, self.name)
        return moveId


def main():
    # Init Game
    game = Board()
    # Init Players
    human = HumanPlayer()   # o
    ai = AIPlayer()         # x
    current_player = human
    players = [human, ai]
    total_moves = 0
    while game.decideGame(current_player.name)==-1:
        # Display current game status
        game.printState()

        # Get available moves for players
        available_moves = game.getAvailableMoves()
        # Display available moves for players
        print(f"\nAvailable Moves : {available_moves}")

        # Player decide move based on available moves
        moveId = current_player.makeMove(game)
        total_moves += 1
        print(f"Make Move : {total_moves}, {current_player.name}, {moveId}")

        # Update game state with player input
        game.updateBoard(moveId, current_player.name)

        # If current player win
        if game.decideGame(current_player.name) == 0:
            print("Draw")
            return
        # If draw
        elif game.decideGame(current_player.name) == 1:
            print(f"Win : {current_player}")
            return

        current_player = players[total_moves%2]


if __name__ == '__main__':
    print("Start the Tic Tac Toe game")
    main()