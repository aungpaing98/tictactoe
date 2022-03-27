from utils import user_move, random_move, minmax_move


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
        moveId = user_move(game, self.name)
        return moveId


class AIPlayer(Player):
    def __init__(self, name="x"):
        super().__init__(name)

    def makeMove(self, game):
        moveId = minmax_move(game, self.name)
        return moveId