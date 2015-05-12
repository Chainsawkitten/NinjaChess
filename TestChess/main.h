#ifndef MAIN_H
#define MAIN_H

#include <Board.h>

/// Main function.
int main();

/// Print board.
/**
 * @param board %Board to print.
 */
void printBoard(const Chess::Board& board);

/// Print legal moves.
/**
 * @parma board %Board.
 * @param position %Piece position.
 */
void printLegalMoves(const Chess::Board& board, const Chess::Position& position);

#endif