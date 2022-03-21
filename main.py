import random


class Board:
    def __init__(self):
        self.init_board()
    
    def init_board(self):
        self.game_state =  [' ' for _ in range(9)]

    def updateBoard(self, moveId, player):
        self.game_state[moveId] = player

    def decideGame(self, player):
        win_rules = [[0, 1, 2], [3, 4, 5], [6, 7, 8], [0,3,6], [1, 4, 7], [2, 5, 8], [0,4,8],[2, 4, 6]]
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
                return 1
        
        # Decide for draw condition
        total_moves = 0
        for i in range(9):
            if self.game_state[i] != " ":
                total_moves += 1
        if total_moves == 9:
            return 0
        # Continue the game
        return -1

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


class Player:
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return self.name

    def makeMove(self, available_moves):
        return random.choice(available_moves)


def main():
    # Init Game
    game = Board()
    # Init Players
    player1 = Player("o")
    player2 = Player("x")
    current_player = player1
    players = [player1, player2]
    total_moves = 0
    while game.decideGame(current_player.name)==-1:
        # Display current game status
        game.printState()

        # Get available moves for players
        available_moves = game.getAvailableMoves()
        # Display available moves for players
        print(f"\nAvailable Moves : {available_moves}")

        # Player decide move based on available moves
        moveId = current_player.makeMove(available_moves)
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