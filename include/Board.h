#pragma once

//--------------------include Section --------------------
#include "Slot.h"
#include <fstream>
#include <sstream>

//--------------------Board Class definition --------------------
class Board : public Slot
{								//***inherits from Slot***
public:
	//constructors ---------------
	Board();
	Board(int row, int col, int rocks);

	//set functions ---------------
	void readLevel(std::ifstream& levelFile);	//reading level into representation
	void createBoardRepresentation(int i, int j, int numOfRocks); //creating representation on file
	void updateBoardRepresentation(char insert, int i, int j); //updating representation on file
	void clearBoardRepresentation(); //clear representation on file

	//get functions ---------------
	std::vector < std::vector < sf::RectangleShape > > buildGetBoard(Board board, bool ifCleaned);//building and getting matrix
	std::vector <std::vector < char > > getBoardRepresentation() const;
	int getRow() const;
	int getCol() const;
	int getNumOfRocks() const;

private:
	//class members---------------
	std::vector <std::vector < char > > m_boardRepresentation;//represent gameboard on file
	std::vector < std::vector < sf::RectangleShape > > m_slots; //represent gameboard on SFML
	int m_row;
	int m_col;
	int m_numOfRocks;

};