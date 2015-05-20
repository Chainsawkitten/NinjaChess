#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <sstream>

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
		pieces[4][7] = new King(Position(4, 7), false);
		pieces[4][0] = new King(Position(4, 0), true);
		addBoardToMap();
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

	bool Board::mustPromote() {
		return needsToPromote;
	}

	bool Board::move(const Position& oldPosition, const Position& newPosition) {
		Piece* piece = getPiece(oldPosition);
		Piece* targetPiece = getPiece(newPosition);

		if (piece != nullptr) {
			// Check if the piece is of the right color.
			if (piece->isWhite() == (turn % 2 == 0)) {
				halfMovesSinceCapture++;
				// Check if the move is legal.
				if (piece->isLegal(*this, newPosition)) {
					pieces[oldPosition.x][oldPosition.y] = nullptr;

					// En passant.
					if (newPosition == enPassantPossible && (piece->notation() == 'p' || piece->notation() == 'P')){
						if (piece->isWhite()) {
							delete pieces[newPosition.x][newPosition.y - 1];
							pieces[newPosition.x][newPosition.y - 1] = nullptr;
							halfMovesSinceCapture = 0;
						} else {
							delete pieces[newPosition.x][newPosition.y + 1];
							pieces[newPosition.x][newPosition.y + 1] = nullptr;
							halfMovesSinceCapture = 0;
						}
					}

					// Castling
					if (piece->notation() == 'k' || piece->notation() == 'K') {
						if (newPosition.x - oldPosition.x == 2){
							Piece* tempPiece = getPiece(Position(7, newPosition.y));
							pieces[7][newPosition.y] = nullptr;
							pieces[5][newPosition.y] = tempPiece;
							tempPiece->move(Position(5, newPosition.y));
						} else if (newPosition.x - oldPosition.x == -2) {
							Piece* tempPiece = getPiece(Position(0, newPosition.y));
							pieces[0][newPosition.y] = nullptr;
							pieces[3][newPosition.y] = tempPiece;
							tempPiece->move(Position(3, newPosition.y));
						}
					}

					// Delete captured enemy piece.
					if (pieces[newPosition.x][newPosition.y] != nullptr){
						delete pieces[newPosition.x][newPosition.y];
						halfMovesSinceCapture = 0;
					}
					// Update pieces and piece position
					pieces[newPosition.x][newPosition.y] = piece;
					if (piece->notation() == 'p' || piece->notation() == 'P')
						halfMovesSinceCapture = 0;
					piece->move(newPosition);

					// Promote pawns
					if(newPosition.y == 7 || newPosition.y == 0){
						if (piece->notation() == 'p' || piece->notation() == 'P'){
							needsToPromote = true;
						}
					}
					if ( (piece->notation() == 'p' || piece->notation() == 'P') ){
						if (abs(oldPosition.y - newPosition.y) == 2) {
							if (piece->notation() == 'p')
								enPassantPossible = Position(newPosition.x, newPosition.y + 1);
							else if (piece->notation() == 'P')
								enPassantPossible = Position(newPosition.x, newPosition.y - 1); 
						}
					}
					else {
						enPassantPossible = Position(-1, -1);
					}

					turn++;
					if (state == GameState::BLACKPLAYS)
						state = GameState::WHITEPLAYS;
					else
						state = GameState::BLACKPLAYS;
					addBoardToMap();
					if(isThreeFoldRepitition())
						state = GameState::DRAW;
					if (isFiftyMoveSincePawnOrCapture())
						state = GameState::DRAW;
					if (!sufficientMaterial())
						state = GameState::DRAW;
					checkWin();
					return true;
				}
			}
		}

		return false;
	}

	bool Board::willLeaveKingChecked(const Position& oldPosition, const Position& newPosition) {
		Piece* oldPiece = getPiece(oldPosition);
		Piece* newPiece = getPiece(newPosition);

		Piece* piece;
		switch (oldPiece->notation()) {
		case 'Q':
		case 'q':
			piece = new Queen(oldPiece->getPosition(), oldPiece->isWhite());
			break;
		case 'K':
		case 'k':
			piece = new King(oldPiece->getPosition(), oldPiece->isWhite());
			break;
		case 'P':
		case 'p':
			piece = new Pawn(oldPiece->getPosition(), oldPiece->isWhite());
			break;
		case 'R':
		case 'r':
			piece = new Rook(oldPiece->getPosition(), oldPiece->isWhite());
			break;
		case 'B':
		case 'b':
			piece = new Bishop(oldPiece->getPosition(), oldPiece->isWhite());
			break;
		case 'N':
		case 'n':
			piece = new Knight(oldPiece->getPosition(), oldPiece->isWhite());
			break;
		}

		pieces[newPosition.x][newPosition.y] = piece;
		piece->move(newPosition);
		pieces[oldPosition.x][oldPosition.y] = nullptr;

		King* king = getKing((turn % 2 == 0));
		bool checked = king->isChecked(*this);

		delete piece;
		pieces[newPosition.x][newPosition.y] = newPiece;
		pieces[oldPosition.x][oldPosition.y] = oldPiece;

		return checked;
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
		checkWin();
		needsToPromote = false;
	}
	void Board::addBoardToMap() {
		std::string tempstring = toFENString(false);
		if (previousBoards.find(tempstring) == previousBoards.end()) {
			previousBoards[tempstring] = 0;
		} else{  
			previousBoards[tempstring] += 1;
		}
	}

	std::string Board::toFENString(bool addExtraData) const {
		std::string tempstring;
		int emptyCounter = 0;
		for (int y = 7; y >= 0; y--) {
			for (int x = 0; x < 8; x++){
				if (pieces[x][y] == nullptr)
					emptyCounter++;
				else {
					if (emptyCounter != 0)
						tempstring += std::to_string(emptyCounter);
					tempstring.append(1, pieces[x][y]->notation());
					emptyCounter = 0;
				}
			}
			if (emptyCounter != 0) {
				tempstring += std::to_string(emptyCounter);
				emptyCounter = 0;
			}
			tempstring += '/';
		}
		tempstring += ' ';
		// Who played the turn?
		if (state == GameState::BLACKPLAYS)
			tempstring += "w";
		else
			tempstring += "b";
		tempstring += ' ' + std::to_string(enPassantPossible.x) + '.' + std::to_string(enPassantPossible.y);
		if (addExtraData) {
			// Number of half turns since last capture or pawn move.
			tempstring += ' ' + std::to_string(halfMovesSinceCapture) + ' ';
			// Number of full moves.
			tempstring += std::to_string((turn+1) / 2);
			tempstring += '#';
		}
		return tempstring;
	}

	bool Board::isThreeFoldRepitition() {
		return previousBoards[toFENString(false)] == 3;
	}

	bool Board::isFiftyMoveSincePawnOrCapture() const {
		return halfMovesSinceCapture >= 100;
	}

	void Board::checkWin() {
		bool white = (state == GameState::WHITEPLAYS);

		bool canMove = false;
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				Piece* piece = getPiece(Position(x, y));
				if (piece != nullptr && piece->isWhite() == white) {
					if (!piece->legalMoves(*this).empty()) {
						canMove = true;
						break;
					}
				}
			}
		}

		if (!canMove) {
			if (getKing(white)->isChecked(*this)) {
				if (white)
					state = GameState::BLACKWIN;
				else
					state = GameState::WHITEWIN;
			} else {
				state = GameState::DRAW;
			}
		}
	}

	bool Board::sufficientMaterial() const {
		// Get the material on the board.
		int pieceTypes[6] = { 0 };

		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				Piece* piece = getPiece(Position(x, y));
				if (piece != nullptr) {
					switch (piece->notation()) {
					case 'Q':
					case 'q':
						pieceTypes[0]++;
						break;
					case 'P':
					case 'p':
						pieceTypes[1]++;
						break;
					case 'R':
					case 'r':
						pieceTypes[2]++;
						break;
					case 'N':
					case 'n':
						pieceTypes[3]++;
						break;
					case 'B':
					case 'b':
						pieceTypes[((x + y) % 2 == 0) ? 4 : 5]++;
						break;
					}
				}
			}
		}

		// If there's a queen, pawn or rook on the board, there is sufficient material.
		if (pieceTypes[0] > 0 || pieceTypes[1] > 0 || pieceTypes[2] > 0)
			return true;

		// If there are 2 or more knights on the board, there is sufficient material.
		if (pieceTypes[3] > 1)
			return true;

		// If there are pieces from 2 or more categories (knight, bishop on light square, bishop on dark square), there is sufficient material.
		if ((pieceTypes[3] > 0) + (pieceTypes[4] > 0) + (pieceTypes[5] > 0) >= 2)
			return true;

		return false;

	}

	King* Board::getKing(bool white) const {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				Piece* piece = getPiece(Position(x, y));
				if (piece != nullptr && piece->notation() == (white ? 'K' : 'k'))
					return dynamic_cast<King*>(piece);
			}
		}

		return nullptr;
	}
	Position Board::getEnPassantPossible()const{
		return enPassantPossible;
	}
}