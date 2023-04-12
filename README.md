# connect-four-solver
Solving connect four so I can thrash my colleagues on a Friday afternoon.

Method is an exhaustive Monte Carlo Tree Search [MCTS](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search)

# Methods
Need to be able to save 'state': Who's turn it is, and the current state of the board. 

Once the game has finished, the game needs to be able to back-track all previous moves, and update win probabilities if a certain move is made.

Use DFS, keep a stack of all moves that can be made.
Keep a record (also a stack) of move history.
Once an end game condition is met, keep a track of the player that won. Backtrack (undo all moves) until the board is empty. Update GameStates for each move that was made, with win probabilities also updated.

Board: 
- A 6 x 7 2D binary vector.
- Can be 0 x 7 and only append.

GameState:
- Snapshot of board.
- Count of wins / draws / losses for snapshot.
- Whether all possible games given snapshot have been played to completion.

Game:
- Places tokens using Board class.
- Keeps track of last token placed.
- Keeps track of which players turn it is.
- Checks win condition of Board (4 in a row).
- Checks draw condition of Board (Board is 6 x 7).

    interations with GameState:
    - Creates GameState instance if board is in unseen state.
    - If board in seen state, then check whether game has been played to completion.
    - Backtracks moves and updates GameState win probabilities if win / draw condition met.
