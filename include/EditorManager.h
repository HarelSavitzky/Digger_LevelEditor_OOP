#pragma once

//--------------------include Section --------------------
#include "Board.h"
#include "Objects.h"

//--------------------EditorManager Class definition --------------------
class EditorManager : public Board
{									//***inherits from Board***
public:
	//constructor ---------------
	EditorManager();
	//main function to handle the editor---
	void runEditor();

	//functions to handle events ---------------
	bool toolBarPressed(int mouseX, int mouseY, 
		std::vector < sf::RectangleShape >&objectBar, int& buttonIndex);

	bool optionBarPressed(int mouseX, int mouseY, int& optionIndex,
		std::vector < sf::RectangleShape >& optionBar,
		std::vector < std::vector < sf::RectangleShape > >& levelMatrix,
		Board newBoard, bool& ifCleaned);

	bool pressedOnMatrix(int mouseX, int mouseY, int buttonIndex, int optionIndex, bool objectIsPressed,
		bool optionIsPressed,	std::vector < std::vector < sf::RectangleShape > >& levelMatrix);

	void movedOnMatrix(std::vector < std::vector < sf::RectangleShape > >& levelMatrix,
		sf::RenderWindow& window, bool optionIsPressed);


	//functions to handle different operations according to event accured ---------------
	void lightButton(std::vector < sf::RectangleShape >& bar, int& index, int i);
	bool isValid(int i, int j);
	void saveFile(Board newBoard);
	bool openFile(std::ifstream& levelFile);

	//functions to build the SFML matrix from a file---------------
	void buildBoardFromFile(std::vector <std::vector < char > > boardFromFile,
		std::vector < std::vector < sf::RectangleShape > >& levelMatrix);

private:
	//class members---------------
	Objects m_objects;
};