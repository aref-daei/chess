# The chess game document

**Chess Game Implementation in C**

**Project Overview:**
- **Topic:** Implementation of a Chess Game in the Terminal using C.

**How to Install It**

1. **Open Terminal:** Launch your terminal application.

2. **Navigate to the Project Directory:** Use the `cd` command to change to the directory where your C source file (e.g., `chess.c`) is located.
   ```bash
   cd path/to/your/project
   ```

3. **Compile the Program:** Use the `gcc` command to compile your C program. Replace `chess.c` with the name of your source file.
   ```bash
   gcc -o chess chess.c
   ```
   - The `-o chess` option specifies the name of the output executable file.

4. **Run the Program:** After successful compilation, run the program using:
   ```bash
   ./chess
   ```

**Main Features:**

1. **Display the Chessboard:**
   - 10x10 grid representation.
   - Empty squares represented by spaces instead of dots.
   - The chessboard alternates between black and white squares.

2. **Movement of Pieces:**
   - **Pawn (P):** Moves one or two squares forward initially, one square thereafter, can capture diagonally, and can be promoted upon reaching the last row.
   - **Rook (R):** Moves vertically or horizontally any number of squares until blocked.
   - **Knight (N):** Moves in an "L" shape, can go one additional square in any direction.
   - **Bishop (B):** Moves diagonally any number of squares until blocked.
   - **Queen (Q):** Combines movements of rook and bishop.
   - **King (K):** Moves one square in any direction, cannot move into check.

3. **End of Game Conditions:**
   - **Checkmate:** King is in check and cannot escape.
   - **Stalemate:** No legal moves available, king is not in check.
   - **Threefold Repetition:** Position occurs three times, players can request a draw.

4. **Managing Player Turns:**
   - Players alternate turns, with white starting first.
   - Display the current player's turn, number of rounds, game logs, and messages on the right side of the game board.

5. **Input Handling:**
   - Moves entered in the format: Piece symbol (P, R, N, B, Q, K), Source square (e.g., e2), Destination square (e.g., e4).
   - Example: `Pe2e4` (Pawn from e2 to e4).
   - Invalid moves prompt an error message.

**Code Structure:**
1. **Display Board Function:**
   - `void displayBoard()`
2. **Move Validation Functions:**
   - `int isValidPawnMove()`
   - `int isValidRookMove()`
   - `int isValidKnightMove()`
   - `int isValidBishopMove()`
   - `int isValidQueenMove()`
   - `int isValidKingMove()`
   - `int isCheckMate()`
3. **Turn Management Function:**
   - `void switchTurn()`
4. **Main Game Loop:**
   - `while (1)`
     - Display the board
     - Get player input
     - Validate the move
     - Update the board
     - Check for end game conditions
     - Update and display game logs, moved pieces, and messages.

This chess game implementation in C allows you to experience the classic game in a terminal environment. By following the outlined features and installation steps, you can easily compile and run the game. Enjoy coding and playing your chess game!
