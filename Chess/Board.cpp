#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

namespace Chess {
	Board::Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				pieces[x][y] = nullptr;
			}
		}

		// Black pawns
		for (int x = 0; x < 8; x++) {
			pieces[x][1] = new Pawn(Position(x, 1), false);
		}

		// White pawns
		for (int x = 0; x < 8; x++) {
			pieces[x][6] = new Pawn(Position(x, 6), true);
		}

		// Rooks
		pieces[0][0] = new Rook(Position(0, 0), false);
		pieces[7][0] = new Rook(Position(7, 0), false);
		pieces[0][7] = new Rook(Position(0, 7), true);
		pieces[7][7] = new Rook(Position(7, 7), true);

		// Knights
		pieces[1][0] = new Knight(Position(1, 0), false);
		pieces[6][0] = new Knight(Position(6, 0), false);
		pieces[1][7] = new Knight(Position(1, 7), true);
		pieces[6][7] = new Knight(Position(6, 7), true);

		// Bishops
		pieces[2][0] = new Bishop(Position(2, 0), false);
		pieces[5][0] = new Bishop(Position(5, 0), false);
		pieces[2][7] = new Bishop(Position(2, 7), true);
		pieces[5][7] = new Bishop(Position(5, 7), true);

		// Queens
		pieces[3][0] = new Queen(Position(3, 0), false);
		pieces[3][7] = new Queen(Position(3, 7), true);

		// Kings
		blackKing = new King(Position(4, 0), false);
		pieces[4][0] = blackKing;
		whiteKing = new King(Position(4, 7), true);
		pieces[4][7] = whiteKing;
	}

	Board::~Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (pieces[x][y] != nullptr)
					delete pieces[x][y];
			}
		}
	}

	Piece* Board::getPiece(const Position& position) const {
		return pieces[position.x][position.y];
	}
}