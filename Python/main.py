from board import TicTacToe
from players import HumanPlayer, AIPlayer


def main():
    # Init Game
    game = TicTacToe()
    # Init Players
    human = HumanPlayer()   # o
    ai = AIPlayer()         # x
    players = [human, ai]
    modes = []

    query_msg = "How would you like to play?\nSelect one of the option below.\nO First\t: 0\nX First\t: 1\n: "
    try:
        start_player = int(input(query_msg))
    except:
        start_player = 0

    current_player = players[start_player]
    print("Starting player : ", current_player)
    print("Select one mode :\n\n0 : random move\n1 : User Input mode\n2 : Minmax algorithm\n3: Minmax Alpha Beta algorithm\n")
    query_msg = "How would you like `O` to play : "
    try:
        mode = int(input(query_msg))
    except:
        mode = 0

    modes.append(mode)
    query_msg = "How would you like `X` to play : "
    try:
        mode = int(input(query_msg))
    except:
        mode = 0

    modes.append(mode)

    total_moves = 0
    win_loss_draw = -1
    while win_loss_draw==-1:
        # Display current game status
        game.printState()

        # Get available moves for players
        available_moves = game.getAvailableMoves()
        # Display available moves for players
        print(f"\nAvailable Moves : {available_moves}")

        # Player decide move based on available moves
        moveId = current_player.makeMove(game, modes[start_player%2])
        total_moves += 1
        start_player += 1
        print(f"Make Move : {total_moves}, {current_player.name}, {moveId}")

        # Update game state with player input
        game.updateBoard(moveId, current_player.name)

        # If current player win
        win_loss_draw = game.decideGame(current_player.name)
        if win_loss_draw== 0:
            print("Draw")
            return
        # If draw
        elif win_loss_draw == 1:
            print(f"Win : {current_player}")
            return

        current_player = players[start_player%2]


if __name__ == '__main__':
    print("Start the Tic Tac Toe game")
    main()
