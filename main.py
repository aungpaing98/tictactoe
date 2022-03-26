from board import Board
from players import HumanPlayer, AIPlayer


def main():
    # Init Game
    game = Board()
    # Init Players
    human = HumanPlayer()   # o
    ai = AIPlayer()         # x
    players = [human, ai]

    start_player = 0
    current_player = players[start_player]
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
        moveId = current_player.makeMove(game)
        total_moves += 1
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

        current_player = players[total_moves%2]


if __name__ == '__main__':
    print("Start the Tic Tac Toe game")
    main()