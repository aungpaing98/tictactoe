import random


def argmax(arr):
    ret = 0
    for i in range(1, len(arr)):
        if arr[i] > arr[ret]:
            ret = i
    return ret


def minmax_alpha_beta(game, maximize, alpha, beta):
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
            val = minmax_alpha_beta(game, False, alpha, beta)
            game.updateBoard(move, ' ')
            value = max(value, val)
            alpha = max(alpha, value)
            if beta <= alpha:
                break
        return value

    else:
        value = 1000
        available_moves = game.getAvailableMoves()
        for move in available_moves:
            game.updateBoard(move, current_player)
            val = minmax_alpha_beta(game, True, alpha, beta)
            game.updateBoard(move, ' ')

            value = min(value, val)
            beta = min(beta, value)
            if beta <= alpha:
                break
        return value

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


def get_minmax_score(game, name, alpha_beta):
    available_moves = game.getAvailableMoves()
    scores = []
    for move in available_moves:
        game.updateBoard(move, name)
        if alpha_beta:
            score = minmax_alpha_beta(game, name=='o', -1000, 1000)
        else:
            score = minmax(game, name=='o')
        game.updateBoard(move, ' ')
        scores.append(score)

    # print("Scores : \t", scores)
    return scores


def minmax_move(game, name, alpha_beta):
    scores = get_minmax_score(game, name, alpha_beta)
    print("Scores : \t", scores)

    available_moves = game.getAvailableMoves()
    moveId = available_moves[argmax(scores)]
    return moveId


def random_move(game, name):
    available_moves = game.getAvailableMoves()
    return random.choice(available_moves)


def user_move(game, name):
    scores = get_minmax_score(game, name, 1)
    scores = [-1 * s for s in scores]
    print("You might want to conside this from minmax :")
    print("Scores : \t", scores)

    moveId = -1
    available_moves = game.getAvailableMoves()
    try:
        while (moveId not in available_moves):
            moveId = int(input("Enter your move :"))
            if moveId in available_moves:
                return moveId
    except ValueError:
        print("Enter valid format in integer.")
        return user_move(available_moves)
