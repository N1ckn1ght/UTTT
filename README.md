# Ultimate Tic-Tac-Toe

Rules are taken from: https://web.archive.org/web/20210830092027/https://mathwithbaddrawings.com/2013/06/16/ultimate-tic-tac-toe/

Each small 3 × 3 tic-tac-toe board is referred to as a local board, and the larger 3 × 3 board is referred to as the global board.

The game starts with X playing wherever they want in any of the 81 empty spots. This move "sends" their opponent to its relative location. For example, if X played in the top right square of their local board, then O needs to play next in the local board at the top right of the global board. O can then play in any one of the nine available spots in that local board, each move sending X to a different local board.

If a move is played so that it is to win a local board by the rules of normal tic-tac-toe, then the entire local board is marked as a victory for the player in the global board. Once a local board is won by a player or it is filled completely, no more moves may be played in that board. If a player is sent to such a board, then that player may play in any other board. Game play ends when either a player wins the global board or there are no legal moves remaining, in which case the game is a draw.

There are other variants of Ultimate Tic-Tac-Toe rules, e.g. that one where players are able to make a move on already adjudicated boards, however this variation contains really simple winning strategy thus I've decided to avoid its implementation.

# How to play

When it's your turn to make move, you'll be asked to input its full coordinates in this format:

board_X board_Y X Y

### Example of move

3 3 1 2

This input will place your mark (X or O) on board (3, 3) in cell (1, 2) if possible;

Otherwise you'll need to repeat the input until it's correct.

### "I accidentally made a wrong move, what do?"

-1 1 1 1

Type in console full coordinate with -1 as bx and it'll revert your move.

Note, that it will make two reverts in games versus bot to keep move order correct.

Just don't abuse this mechanic =)

# FAQ

### "Which bots are stronger? Why can't I play with heuristic bot anymore?"

There's a detailed description of what's hapenning, it's in the Github wiki, but it's in Russian.

Short answer - old heuristic bot had many severe memory leaks and wasn't as effective as I wish it would. So I rewrote whole field class, now it's memory efficient. I've also implemented a simple min-max engine and I have a plan to make a new Heurist bot based on it, but... that engine is time inefficient.

So, I just need more time to re-implement Heurist again, with even more power and shine. You can always download old release of UTTT (ver. 1.0) and play with ol' buddy Eurist, if you want!

...And, of course, EdgeBot v1.1 is stronger than EdgeBot v1.0 in most case scenario, potentially in all cases. You can test it for yourself. But first version, sometimes, can make interesting plays... and it confuses first version of heuristic bot a lot. 

A difference between EdgeBot v1.0 and EdgeBot v1.1 is provided by slight static evaluation function changes, they are both based on the same MinMax Engine...

### "Meh, it could be better."

If you have some issues with the game or suggestions for AI/Engine improvement, feel free to create a github issue, because this may help a lot.
