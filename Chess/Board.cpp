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

	GameState Board::getState() const {
		return state;
	}

	Piece* Board::getPiece(const Position& position) const {
		return pieces[position.x][position.y];
	}

	bool Board::signalPromote() {
		bool temp = needsToPromote;
		needsToPromote = false;
		return temp;
	}

	bool Board::move(const Position& oldPosition, const Position& newPosition) {
		Piece* piece = getPiece(oldPosition);
		Piece* targetPiece = getPiece(newPosition);

		if (piece != nullptr) {
			// Check if the piece is of the right color.
			if (piece->isWhite() == (turn % 2 == 0)) {
				// Check if the move is legal.
				if (piece->isLegal(*this, newPosition)) {
					pieces[oldPosition.x][oldPosition.y] = nullptr;

					//En passant.
					if (pieces[newPosition.x][newPosition.y] == nullptr && (piece->notation() == 'p' || piece->notation() == 'P') && newPosition.x != oldPosition.x){
						if (piece->isWhite()){
							delete pieces[newPosition.x][newPosition.y - 1];
							pieces[newPosition.x][newPosition.y - 1] = nullptr;
						}
						else{
							delete pieces[newPosition.x][newPosition.y + 1];
							pieces[newPosition.x][newPosition.y + 1] = nullptr;
						}
					}

					//Castling
					if (piece->notation() == 'k' || piece->notation() == 'K'){
						if (newPosition.x - oldPosition.x == 2){
							Piece* tempPiece = getPiece(Position(7, newPosition.y));
							pieces[7][newPosition.y] = nullptr;
							pieces[5][newPosition.y] = tempPiece;
							tempPiece->move(Position(5, newPosition.y));
						}
						else if (newPosition.x - oldPosition.x == -2){
							Piece* tempPiece = getPiece(Position(0, newPosition.y));
							pieces[0][newPosition.y] = nullptr;
							pieces[3][newPosition.y] = tempPiece;
							tempPiece->move(Position(3, newPosition.y));
						}
					}
					// Delete captured enemy piece.
					if (pieces[newPosition.x][newPosition.y] != nullptr && piece->isWhite() != targetPiece->isWhite()){
						delete pieces[newPosition.x][newPosition.y];
					}

					// Update pieces and piece position
					pieces[newPosition.x][newPosition.y] = piece;
					piece->move(newPosition);

					//Promote pawns
					if(newPosition.y == 7 || newPosition.y == 0){
						if (piece->notation() == 'p' || piece->notation() == 'P'){
							needsToPromote = true;
						}
					}
					// Set and reset lastMovedPiece
					if (lastMovedPawn != nullptr){
						if (lastMovedPawn->getLastMoveWasDouble()){
							//lastMovedPawn->resetLastMoveWasDouble(); //orsakar krasch..
						}
					}
					lastMovedPawn = dynamic_cast<Pawn *>(getPiece(newPosition));

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

	void Board::promotePawn(Piece* pawn, PromoteTypes type) {
		Position position = pawn->getPosition();
		bool white = pawn->isWhite();
		delete pawn;

		switch (type) {
		case PromoteTypes::QUEEN:
			pieces[position.x][position.y] = new Queen(position, white);
			break;
		case PromoteTypes::ROOK:
			pieces[position.x][position.y] = new Rook(position, white);
			break;
		case PromoteTypes::BISHOP:
			pieces[position.x][position.y] = new Bishop(position, white);
			break;
		case PromoteTypes::KNIGHT:
			pieces[position.x][position.y] = new Knight(position, white);
			break;
		}
	}

	King* Board::getKing(bool white) const {
		if (white) {
			return whiteKing;
		} else {
			return blackKing;
		}
	}
}