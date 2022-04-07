from utils import user_move, random_move, minmax_move


class Player:
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return self.name

    def makeMove(self, game, mode):
        if mode==0:
            moveId = random_move(game, self.name)
        elif mode==1:
            moveId = user_move(game, self.name)
        elif mode==2:
            moveId = minmax_move(game, self.name, alpha_beta=0)
        else:
            moveId = minmax_move(game, self.name, alpha_beta=1)
        return moveId


class HumanPlayer(Player):
    def __init__(self, name="o"):
        super().__init__(name)


class AIPlayer(Player):
    def __init__(self, name="x"):
        super().__init__(name)
