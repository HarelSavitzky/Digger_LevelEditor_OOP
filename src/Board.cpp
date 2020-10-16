#include "Board.h"

//--------------------using Section --------------------
using std::string;
using std::getline;
using std::istringstream;

//--------------------constructors functions --------------------
Board::Board()
{}
Board::Board(int row , int col, int rocks)
{
	m_numOfRocks = rocks;
	m_row = row;
	m_col = col;
}
//--------------------set (definition) functions --------------------
//functions to read level-----------------------------
void Board::readLevel(std::ifstream& levelFile)
{
	levelFile.open("Board.txt");
	int row, col, numOfRocks;
	std::string propertiesLine;
	std::getline(levelFile, propertiesLine);
	std::istringstream iss(propertiesLine);

	iss >> m_row >> m_col >> m_numOfRocks;	//reading the propertys line
	createBoardRepresentation(getRow(), getCol(), getNumOfRocks());
												//create representation variable
	char trash;
	for (int z = 0; z < m_row; z++)				//than building from file
	{
		for (int k = 0; k < m_col; k++)
		{
			levelFile.get(m_boardRepresentation[z][k]);
		}
		levelFile.get(trash);
	}
	levelFile.close();
}
//functions to create empty represntation veriable---------------------
void Board::createBoardRepresentation(int i, int j, int numOfRocks)
{
	m_boardRepresentation.clear();

	std::string propertiesLine;			//creating empty m_boardRepresentation
	std::stringstream stream1;			//in the size entered
	stream1 << i << " " << j << " " << numOfRocks;
	propertiesLine = stream1.str();

	for (int z = 0; z < i; z++)
	{
		std::vector < char >  t;
		for (int k = 0; k < j; k++)
		{
			t.push_back(' ');
		}
		m_boardRepresentation.push_back(t);
	}
}
//functions to update the board representation on file--------------------
void Board::updateBoardRepresentation(char insert, int i, int j)
{
	m_boardRepresentation[i][j] = insert;	//in each slot pressed by user, the board member 
}											//is beeing updated
//functions to clear all the representation--------------------
void Board::clearBoardRepresentation()
{
	for (int z = 0; z < m_boardRepresentation.size(); z++)	//inserting spaces to all the representation 
	{
		for (int k = 0; k < m_boardRepresentation[0].size(); k++)
		{
			m_boardRepresentation[z][k] = EMPTY;
		}
	}
}
//function to build the SFML representation matrix with empty slots and returning it--------
std::vector < std::vector < sf::RectangleShape > > Board::buildGetBoard(Board board, bool ifCleaned)
{
	Slot newRec;
	if (ifCleaned)
		m_slots.clear();		//if screen allready cleared - clear the existing member to avoid
								//memory leak error------and to build completely new member----
	for (int i = 0; i < board.getRow(); i++)
	{
		std::vector < sf::RectangleShape > t;
		for (int j = 0; j < board.getCol(); j++)
		{
			t.push_back(newRec.getSlot());
			t[j].setFillColor(sf::Color(100, 100, 100));
			if (i == 0)
			{
				if (j == 0)
					t[j].setPosition(((j + 1) * SLOT_SIZE), ((i + 1) * SLOT_SIZE));
				else
					t[j].setPosition(((j + 1) * SLOT_SIZE) + (SLOT_GAP * j), ((i + 1) * SLOT_SIZE));
			}
			else
				t[j].setPosition(((j + 1) * SLOT_SIZE) + (SLOT_GAP * j), ((i + 1) * SLOT_SIZE) + (SLOT_GAP * i));
		}
		m_slots.push_back(t);
	}
	return m_slots;
}
//get board TXT representation -----------------------------------
std::vector <std::vector < char > > Board::getBoardRepresentation() const
{
	return m_boardRepresentation;		//get the board text representation
}
//get num of rows -----------------------------------
int Board::getRow() const
{
	return m_row;		//get num of rows on current level
}
//get num of cols -----------------------------------
int Board::getCol() const
{
	return m_col;		//get num of cols on current level
}
//get num of rocks -----------------------------------
int Board::getNumOfRocks() const
{
	return m_numOfRocks;	//get num of rocks on current level
}




