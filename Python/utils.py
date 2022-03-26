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
    win_loss_draw = game.decideGame(pre_player)

    # Base case
    if win_loss_draw==1:
        return scores[not maximize] * (len(game.getAvailableMoves()) + 1)
    elif win_loss_draw==0:
        return 0

    if maximize:
        value = -1000
        available_moves = game.getAvailableMoves()
        for move in available_moves:
            game.updateBoard(move, current_player)
            value = max(value, minmax(game, False))
            game.updateBoard(move, ' ')
        return value

    else:
        value = 1000
        available_moves = game.getAvailableMoves()
        for move in available_moves:
            game.updateBoard(move, current_player)
            value = min(value, minmax(game, True))
            game.updateBoard(move, ' ')
        return value


def minmax_move(game, name):
    available_moves = game.getAvailableMoves()
    scores = []
    for move in available_moves:
        game.updateBoard(move, name)
        score = minmax(game, False)
        game.updateBoard(move, ' ')
        scores.append(score)

    print("Scores : \t", scores)
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
