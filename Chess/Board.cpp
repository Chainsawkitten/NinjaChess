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
			pieces[x][6] = new Pawn(Position(x, 6), false);
		}

		// White pawns
		for (int x = 0; x < 8; x++) {
			pieces[x][1] = new Pawn(Position(x, 1), true);
		}

		// Rooks
		pieces[0][7] = new Rook(Position(0, 7), false);
		pieces[7][7] = new Rook(Position(7, 7), false);
		pieces[0][0] = new Rook(Position(0, 0), true);
		pieces[7][0] = new Rook(Position(7, 0), true);

		// Knights
		pieces[1][7] = new Knight(Position(1, 7), false);
		pieces[6][7] = new Knight(Position(6, 7), false);
		pieces[1][0] = new Knight(Position(1, 0), true);
		pieces[6][0] = new Knight(Position(6, 0), true);

		// Bishops
		pieces[2][7] = new Bishop(Position(2, 7), false);
		pieces[5][7] = new Bishop(Position(5, 7), false);
		pieces[2][0] = new Bishop(Position(2, 0), true);
		pieces[5][0] = new Bishop(Position(5, 0), true);

		// Queens
		pieces[3][7] = new Queen(Position(3, 7), false);
		pieces[3][0] = new Queen(Position(3, 0), true);

		// Kings
		blackKing = new King(Position(4, 7), false);
		pieces[4][7] = blackKing;
		whiteKing = new King(Position(4, 0), true);
		pieces[4][0] = whiteKing;
	}

	Board::~Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (pieces[x][y] != nullptr)
					delete pieces[x][y];
			}
		}
	}

	GameState Board::getState(){
		return state;
	}

	Piece* Board::getPiece(const Position& position) const {
		return pieces[position.x][position.y];
	}

	bool Board::signalPromote(){
		bool temp = needsToPromote;
		needsToPromote = false;
		return temp;
	}

	bool Board::move(const Position& oldPosition, const Position& newPosition) {
		Piece* piece = getPiece(oldPosition);

		if (piece != nullptr) {
			// Check if the piece is of the right color.
			if (piece->isWhite() == (turn % 2 == 0)) {
				// Check if the move is legal.
				if (piece->isLegal(*this, newPosition)) {
					pieces[oldPosition.x][oldPosition.y] = nullptr;

					// Delete captured piece.
					if (pieces[newPosition.x][newPosition.y] != nullptr)
						delete pieces[newPosition.x][newPosition.y];

					// TODO: En passant.


					//Promote pawns
					pieces[newPosition.x][newPosition.y] = piece;
					piece->move(newPosition);
					if(newPosition.y == 7 || newPosition.y == 0){
						if (piece->notation() == 'p' || piece->notation() == 'P'){
							needsToPromote = true;
						}
					}
					// TODO: Castling, promotion, pawn double move.

					turn++;
					if (state == GameState::BLACKPLAYS)
						state = GameState::WHITEPLAYS;
					else
						state = GameState::BLACKPLAYS;
					return true;
				}
			}
		}

		return false;
	}

	void Board::promotePawn(Piece* pawn, PromoteTypes type){
		Position tempPosition = pawn->getPosition();
		bool tempIsWhite = pawn->isWhite();
		delete pawn;
		if (type == PromoteTypes::QUEEN){
			pawn = new Queen(tempPosition, tempIsWhite);
		}
		else if (type == PromoteTypes::ROOK){
			pawn = new Rook(tempPosition, tempIsWhite);
		}
		else if (type == PromoteTypes::BISHOP){
			pawn = new Bishop(tempPosition, tempIsWhite);
		}
		else if (type == PromoteTypes::KNIGHT){
			pawn = new Knight(tempPosition, tempIsWhite);
		}
	}
}