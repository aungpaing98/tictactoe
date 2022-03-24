import random

def argmax(arr):
    ret = 0
    for i in range(1, len(arr)):
        if arr[i] > arr[ret]:
            ret = i
    return ret


def minmax(game, maximize):
    # o : Human, x : AI
    players = ['o', 'x']
    scores = [-1, 1]
    pre_player = players[not maximize]
    current_player = players[maximize]

    # Base case
    if game.decideGame(pre_player)==1:
        return scores[not maximize]
    elif game.decideGame(pre_player)==0:
        return 0

    if maximize:
        value = -10000
        available_moves = game.getAvailableMoves()
        for move in available_moves:
            # Implement this
            tmp_game = game.copy()
            tmp_game.updateBoard(move, current_player)
            value = max(value, minmax(tmp_game, False))
        return value

    else:
        value = 10000
        available_moves = game.getAvailableMoves()
        for move in available_moves:
            tmp_game = game.copy()
            tmp_game.updateBoard(move, current_player)
            value = min(value, minmax(tmp_game, True))
        return value


def minmax_move(game, name):
    available_moves = game.getAvailableMoves()
    scores = []
    for move in available_moves:
        tmp_game = game.copy()
        tmp_game.updateBoard(move, name)
        score = minmax(tmp_game, False)
        scores.append(score)
    moveId = available_moves[argmax(scores)]
    return moveId


def random_move(available_moves):
    return random.choice(available_moves)


def user_move(available_moves):
    moveId = -1
    try:
        while (moveId not in available_moves):
            moveId = int(input("Enter your move :"))
            if moveId in available_moves:
                return moveId
    except ValueError:
        print("Enter valid format in integer.")
        return user_move(available_moves)
