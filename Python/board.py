class Board:
    def __init__(self):
        pass

    def init_board(self):
        pass

    def updateBoard(self, moveId, player):
        pass

    def decideGame(self, player):
        pass

    def getAvailableMoves(self):
        pass

    def printState(self):
        pass

    def copy(self):
        pass


class TicTacToe(Board):
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
