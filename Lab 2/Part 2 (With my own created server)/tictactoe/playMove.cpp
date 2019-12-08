#include "tictactoe.h"
#include "gameState.h"

void playMove(gameState& game_state) {
    // Check for valid moves by seeing if it is in the boards' dimensions and if the spot on the board is empty
    if(game_state.get_clickedRow() < 3 && game_state.get_clickedColumn() < 3 && game_state.get_clickedRow() >=0 && game_state.get_clickedColumn() >= 0 && game_state.get_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn()) == Empty){
        game_state.set_moveValid(true);
    } else {
        game_state.set_moveValid(false);
    }
    // If move is valid 
    if(game_state.get_moveValid()) {
        //If it is X's turn:
        if(game_state.get_turn()) {
            // Place X at location gameBoard[clickedRow][clickedCol];
            game_state.set_gameBoard(game_state.get_clickedRow(),  game_state.get_clickedColumn(), X);
            // Check if there is a winner
            if (game_state.get_gameBoard(0,2) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,2) == game_state.get_gameBoard(2,0) && game_state.get_gameBoard(2,0)!= Empty) {
                game_state.set_winCode(8);
                game_state.set_gameOver(true);
            // Left to right diagonal  
            } else if (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(1,1) == game_state.get_gameBoard(2,2) && game_state.get_gameBoard(2,2)!= Empty) {
                game_state.set_winCode(7);
                game_state.set_gameOver(true);
            // COlumn 2 of the board 
            } else if(game_state.get_gameBoard(0,2) == game_state.get_gameBoard(1,2) && game_state.get_gameBoard(1,2) == game_state.get_gameBoard(2,2) && game_state.get_gameBoard(2,2)!= Empty) {
                game_state.set_winCode(6);
                game_state.set_gameOver(true);
            // Column 1 of the board 
            } else if(game_state.get_gameBoard(0,1) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,1) == game_state.get_gameBoard(2,1) && game_state.get_gameBoard(2,1)!= Empty) {
                game_state.set_winCode(5);
                game_state.set_gameOver(true);
            // Column 0 of the board 
            } else if (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,0) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(2,0) && game_state.get_gameBoard(2,0)!= Empty) {
                game_state.set_winCode(4);
                game_state.set_gameOver(true);
            // Row 2 of the board 
            } else if(game_state.get_gameBoard(2,0) == game_state.get_gameBoard(2,1) && game_state.get_gameBoard(2,0) == game_state.get_gameBoard(2,2) && game_state.get_gameBoard(2,2)!= Empty) {
                game_state.set_winCode(3);
                game_state.set_gameOver(true);
            // Row 1 of the board  
            } else if(game_state.get_gameBoard(1,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(1,0) == game_state.get_gameBoard(1,2) && game_state.get_gameBoard(1,0)!= Empty) { 
                game_state.set_winCode(2);
                game_state.set_gameOver(true);
            // Row 0 of the board 
            } else if (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(0,1) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(0,2) && game_state.get_gameBoard(0,0)!= Empty) {
                game_state.set_winCode(1);
                game_state.set_gameOver(true);
            // No win
            } else {
                game_state.set_winCode(0);
                //Change player to O since no win
                game_state.set_turn(false);
            }
        } else {
            // It is O's Turn:
            // Place O at location gameBoard[clickedRow][clickedCol];
            game_state.set_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn(), O);
            // Check if there is a winner
            if (game_state.get_gameBoard(0,2) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,2) == game_state.get_gameBoard(2,0) && game_state.get_gameBoard(2,0)!= Empty) {
                game_state.set_winCode(8);
                game_state.set_gameOver(true);
            // Left to right diagonal  
            } else if (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(1,1) == game_state.get_gameBoard(2,2) && game_state.get_gameBoard(2,2)!= Empty) {
                game_state.set_winCode(7);
                game_state.set_gameOver(true);
            // COlumn 2 of the board 
            } else if(game_state.get_gameBoard(0,2) == game_state.get_gameBoard(1,2) && game_state.get_gameBoard(1,2) == game_state.get_gameBoard(2,2) && game_state.get_gameBoard(2,2)!= Empty) {
                game_state.set_winCode(6);
                game_state.set_gameOver(true);
            // Column 1 of the board 
            } else if(game_state.get_gameBoard(0,1) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,1) == game_state.get_gameBoard(2,1) && game_state.get_gameBoard(2,1)!= Empty) {
                game_state.set_winCode(5);
                game_state.set_gameOver(true);
            // Column 0 of the board 
            } else if (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,0) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(2,0) && game_state.get_gameBoard(2,0)!= Empty) {
                game_state.set_winCode(4);
                game_state.set_gameOver(true);
            // Row 2 of the board 
            } else if(game_state.get_gameBoard(2,0) == game_state.get_gameBoard(2,1) && game_state.get_gameBoard(2,0) == game_state.get_gameBoard(2,2) && game_state.get_gameBoard(2,2)!= Empty) {
                game_state.set_winCode(3);
                game_state.set_gameOver(true);
            // Row 1 of the board  
            } else if(game_state.get_gameBoard(1,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(1,0) == game_state.get_gameBoard(1,2) && game_state.get_gameBoard(1,0)!= Empty) { 
                game_state.set_winCode(2);
                game_state.set_gameOver(true);
            // Row 0 of the board 
            } else if (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(0,1) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(0,2) && game_state.get_gameBoard(0,0)!= Empty) {
                game_state.set_winCode(1);
                game_state.set_gameOver(true);
            // No win
            } else {
                game_state.set_winCode(0);
                //Change player to x since no win
                game_state.set_turn(true);
            }
        }   
    }       
}
