# Ultimate Tic-Tac-Toe

Rules are taken from: https://web.archive.org/web/20210830092027/https://mathwithbaddrawings.com/2013/06/16/ultimate-tic-tac-toe/

Each small 3 × 3 tic-tac-toe board is referred to as a local board, and the larger 3 × 3 board is referred to as the global board.

The game starts with X playing wherever they want in any of the 81 empty spots. This move "sends" their opponent to its relative location. For example, if X played in the top right square of their local board, then O needs to play next in the local board at the top right of the global board. O can then play in any one of the nine available spots in that local board, each move sending X to a different local board.

If a move is played so that it is to win a local board by the rules of normal tic-tac-toe, then the entire local board is marked as a victory for the player in the global board. Once a local board is won by a player or it is filled completely, no more moves may be played in that board. If a player is sent to such a board, then that player may play in any other board. Game play ends when either a player wins the global board or there are no legal moves remaining, in which case the game is a draw.

There are other variants of Ultimate Tic-Tac-Toe rules, e.g. that one where players are able to make a move on already adjudicated boards, however this variation contains really simple winning strategy thus I've decided to avoid its implementation.

# How to play

There are two kinds of moves: full and specified.

You'll be required to input full move only if it's unclear on which board it's made;

Otherwise you must input a specified one with only two coordinates (x, y).

### Example of the full move (bx, by, x, y)

2 2 0 0

This input will place X on board (2, 2) in cell (0, 0) if possible;

Otherwise you'll need to repeat the input until it's correct.

### Example of a specified board move (x, y)

1 1

This input will place X on board (bx, by) in cell (0, 0) if possible where (bx, by) are coordinates of the last move by (x, y).
