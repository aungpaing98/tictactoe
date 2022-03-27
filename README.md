# Two Player Games

This repository contains the two player games implementation with multiple programming languages.

Currently supported game:
- TicTacToe

Currently supported languages:
- C
- Python

Currently supported Automation (AI):
- mode 0: Random move
- mode 1. User Input
- mode 2. MinMax Algorithm.


## Running with python runtime

### Step 1. Enter `Python` Directory

```console
cd Python
```

### Step 2. Run `main.py` with python interpreter.
```console
python main.py
```


## Running with C runtime

### Step 1. Enter `C` Directory
```console
cd C
```

### Step 2: Compile main file with `make` command
```console
make
```
This will output `main` executable file.

### Step 3: Run executable file.

```console
./main
```

Option: If you want to delete all the Object file `*.o` files and the executable file, enter below command to clean all the files.
```console
make clean
```


## File/Code structure, Pseudo Code and Flowchart.

For languages that is capable of OOP, we will use OOP, if not, we will use just Functional programming.
For OOP, see the below UMI.

![UMI for Two Player Game](images/Two_Player_UMI.jpg)



Pseudo Code for `main` function
```python
function main() is
    * initialize game board *
    * initialize players *
    select current player
    while not win or draw then
        current player decide move based on game state
        update game board with new move
        if win then
            return score for player
        if draw then
            return 0
        switch current player
```
Flow chart for `main` function

![Flow chart for main function](images/main_flow.jpg)

## MinMax Algorithm

Pseudo code for `MinMax` algorithm.
Reference from [Wiki](https://en.wikipedia.org/wiki/Minimax).
```python
function  minimax(node, maximizingPlayer) is
    if node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, TRUE))
        return value
```


Flow chart for `make move`

![Flow chart for different make move mode.](images/decide_move.jpg)
