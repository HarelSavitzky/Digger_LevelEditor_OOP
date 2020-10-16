#include "EditorManager.h"

//--------------------using Section --------------------
using std::string;
using std::getline;
using std::istringstream;
using std::cout;
using std::cin;
using std::endl;

//--------------------constructor function --------------------
EditorManager::EditorManager()
{}

//--------------------EditorManager main handling function --------------------
void EditorManager::runEditor()
{
	int row = 0, col = 0, rocks = 0;		//variables definition
	std::ifstream levelFile;				//(needs to be defined before everything)
	Board newBoard;
	std::vector < std::vector < sf::RectangleShape > >
		levelMatrix;
	static bool ifCleaned = false;	//if the level cleaned once
	static bool inputMessage = false;//message to show only once

	if (!openFile(levelFile) || (ifCleaned))	//if the file didnt opened
	{										//or if the file as been cleaned
		if (!inputMessage)					//(if it was cleaned, function will return recursively)
		{
			cout << "(Max input for optimum display:\n";			//first message to explain input
			cout << "row = 20, col = 40, for this slots size,\n";	//input can be bigger, but for optimum display
			cout << "can be change on SLOT_SIZE const)\n\n" << endl;//and for each slot not beeing too small (in a ugly way)
			inputMessage = true;									//it has to be in this limits. can change SLOT_SIZE
		}															//to be smaller, than can ensert more slots -
		if(!ifCleaned)												// but they will be super tiny;
			cout << "Cannot open file...\nEnter values manualy:" << endl;//message if file didnt opened
		if(ifCleaned)
			cout << "Window Cleaned\nEnter new values:" << endl;//message if file opened
		cin >> row >> col >> rocks;
		newBoard = { row, col, rocks };
		createBoardRepresentation(row, col, rocks);		//getting values and building TXT and SFML representations
		levelMatrix = buildGetBoard(newBoard, ifCleaned);
		ifCleaned = false;		//if the file cleaned once, reset variable to false
	}
	else     //(if the file was opened)
	{
		readLevel(levelFile);
		newBoard = { getRow(),getCol(),getNumOfRocks() };			//read from file and
		levelMatrix = buildGetBoard(newBoard, ifCleaned);		//build TXT and SFML representations
		std::vector <std::vector < char > > boardFromFile = getBoardRepresentation();
		buildBoardFromFile(boardFromFile, levelMatrix);
	}
	int windowRow = newBoard.getRow();			//define sizes for window after input from user/file
	int windowCol = newBoard.getCol();
	if (newBoard.getCol() < NUM_OF_BUTTONS)
		windowCol = NUM_OF_BUTTONS;			//if too small for toolbar, keep so it will fir

	sf::RenderWindow window(sf::VideoMode(((windowCol + 2) * SLOT_SIZE) + VERTICAL_GAP + (windowCol * SLOT_GAP),
		((windowRow + 2) * SLOT_SIZE) + VERTICAL_GAP + (windowRow * SLOT_GAP)), "DIGGER - LEVEL EDITOR");
	sf::Event event;								//build dynamic window according to input + event

	m_objects.buildBars(windowRow);		//build the object bars according to window size

	std::vector < sf::RectangleShape >			
		objectBar = m_objects.getObjectBar();			//geing onject/optin bars
	std::vector < sf::RectangleShape >
		optionBar = m_objects.getOptionstBar();
	int mouseX, mouseY, buttonIndex = 0, optionIndex = 0;		//last definition/REST of variables
	bool objectIsPressed = false;								//(has to be only here in case of recursion)
	bool optionIsPressed = false;


	sf::Font font;
	if (!font.loadFromFile("font.ttf"))		//simple headline to display on top of window
		std::cout << "error" << std::endl;	//"LEVEL EDITOR"
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setLetterSpacing(3);
	text.setColor(sf::Color::Red);
	text.setString("LEVEL EDITOR");
	text.setPosition(20, 0);

	while (window.isOpen())			//begginnig of window/events
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:	//closing case (using X)
				window.close();
				break;
			default:
				break;
			
			case sf::Event::MouseMoved:			//if mouse moved after presing object/eraser
				if (objectIsPressed || (optionIsPressed && optionIndex == 0))
				{
					movedOnMatrix(levelMatrix,window, optionIsPressed);
				}
				break;

			case sf::Event::MouseButtonPressed:

				switch (event.key.code)
				{
				case sf::Mouse::Left:
					mouseX = event.mouseButton.x;	//saving press indexes
					mouseY = event.mouseButton.y;
					if (objectIsPressed || optionIsPressed)	//if pressed on toolbars (round before) - will check if pressed on matrix
						pressedOnMatrix(mouseX, mouseY, buttonIndex, optionIndex, objectIsPressed, optionIsPressed, levelMatrix);
																							
					if (toolBarPressed(mouseX, mouseY, objectBar, buttonIndex))	//if toolbar pressed
					{
						objectIsPressed = true;
						if (optionIsPressed)			//erase mark of option bar (if object bar pressed)
						{
							optionBar[optionIndex].setOutlineColor(sf::Color::Black);
							optionBar[optionIndex].setOutlineThickness(3);
							optionIsPressed = false;			//update boolian
						}
					}
					if (optionBarPressed(mouseX, mouseY, optionIndex,
						optionBar, levelMatrix, newBoard, ifCleaned))
					{
						optionIsPressed = true;
						if (objectIsPressed)			//erase mark of object bar (if option bar pressed)
						{
							objectBar[buttonIndex].setOutlineColor(sf::Color::Black);
							objectBar[buttonIndex].setOutlineThickness(3);
							objectIsPressed = false;			//update boolian
						}
						if (ifCleaned)
						{
							window.close();			//if level cleaned using clean button.
							window.clear();			//reset window (close+clear)
							runEditor();			//and repeat recursivly (with relevant updated values
						}
					}
					break;
				}
				break;
			}
		}
		window.clear(sf::Color::White);
		for (int i = 0; i < newBoard.getRow(); i++)	//print matrix to window
		{
			for (int j = 0; j < newBoard.getCol(); j++)
			{
				window.draw(levelMatrix[i][j]);
			}
		}
		for (int i = 0; i < OBJECT_BUTTONS; i++)	//print objectbar to window
		{
			window.draw(objectBar[i]);
		}
		for (int i = 0; i < OPTIONS_BUTTONS; i++)   //print optionbar to window 
		{
			window.draw(optionBar[i]);
		}
		window.draw(text);
		window.display();
	}
}
//--------------------Functions to handle different events --------------------
//toolbar pressed event function------------------------
bool EditorManager::toolBarPressed(int mouseX, int mouseY,
	std::vector < sf::RectangleShape >& objectBar, int& buttonIndex)
{
	for (int i = 0; i < OBJECT_BUTTONS; i++)		//if toolbar pressed
	{												//mark button + save index (beeing referenced from
		sf::FloatRect buttonLoc = objectBar[i].getGlobalBounds();//light button function to here
		if (buttonLoc.contains(mouseX, mouseY))					//and from here to the runeditor function;
		{
			lightButton(objectBar, buttonIndex, i);
			return true;
		}
	}
	return false;
}
//optionbar pressed event function--------------------------------
bool EditorManager::optionBarPressed(int mouseX, int mouseY, int& optionIndex,
	std::vector < sf::RectangleShape >& optionBar,
	std::vector < std::vector < sf::RectangleShape > >& levelMatrix,
	Board newBoard, bool& ifCleaned)
{
	int i;
	for (i = 0; i < OPTIONS_BUTTONS; i++)			//if optionbar pressed
	{												//mark button + save index (beeing referenced from
		sf::FloatRect buttonLoc = optionBar[i].getGlobalBounds();//light button function to here
		if (buttonLoc.contains(mouseX, mouseY))					//and from here to the runeditor function;
		{
			lightButton(optionBar, optionIndex, i);
			if (i == 1)
			{
				saveFile(newBoard);		//in case of saving file
				cout << "LEVEL SAVED TO - Board.txt" << endl;
			}
			if (i == 2)
			{
				ifCleaned = true;		//in case that clean button pressed
				int x = getBoardRepresentation().size();
				int y = getBoardRepresentation()[0].size();
				Board empty{ x, y, getNumOfRocks() };
				clearBoardRepresentation();
			}
			return true;
		}
	}
	return false;
}
//matrix pressed event function--------------------------------
bool EditorManager::pressedOnMatrix(int mouseX, int mouseY, int buttonIndex, int optionIndex, bool objectIsPressed,
	bool optionIsPressed, std::vector < std::vector < sf::RectangleShape > >& levelMatrix)
{
	int i, j;
	static bool diggerBool = false;	//static digger veriables for first press
	static int diggerRow = 0, diggerCol = 0;//and than to change his location just by pressing
	for (i = 0; i < levelMatrix.size(); i++)//o new slot
	{
		for (j = 0; j < levelMatrix[i].size(); j++)
		{
			sf::FloatRect buttonLoc = levelMatrix[i][j].getGlobalBounds();
			if (buttonLoc.contains(mouseX, mouseY))
			{
				if (isValid(i, j))	//if the slot is valid to draw on
				{
					if (objectIsPressed)	//if the object bar presed - object conditions
					{
						if (buttonIndex == 0)	//0 for digger
						{
							if (diggerBool)	//for each press after the first one - delete last location
							{
								updateBoardRepresentation(EMPTY, diggerRow, diggerCol);
								levelMatrix[diggerRow][diggerCol] = m_objects.setGetObject(diggerRow, diggerCol, 5);//empty-----
							}
							levelMatrix[i][j] = m_objects.setGetObject(i, j, buttonIndex); //update on SFML representation
							updateBoardRepresentation(DIGGER, i, j);	//update on TXT representation			
							diggerRow = i;
							diggerCol = j;		//save location for next round (for deleting last)
							diggerBool = true;		//update boolian 
						}
						if (buttonIndex == 1) // 1 for monster
						{
							levelMatrix[i][j] = m_objects.setGetObject(i, j, buttonIndex);	//update on SFML representation
							updateBoardRepresentation(MONSTER, i, j);						//update on TXT representation	....
						}
						if (buttonIndex == 2) //2 for diamond
						{
							levelMatrix[i][j] = m_objects.setGetObject(i, j, buttonIndex); 
							updateBoardRepresentation(DIAMOND, i, j);
						}
						if (buttonIndex == 3) //3 for rock
						{
							levelMatrix[i][j] = m_objects.setGetObject(i, j, buttonIndex);
							updateBoardRepresentation(ROCK, i, j);
						}
						if (buttonIndex == 4) //4 for wall
						{
							levelMatrix[i][j] = m_objects.setGetObject(i, j, buttonIndex);
							updateBoardRepresentation(WALL, i, j);
						}
					}
				}
				if (optionIsPressed)		//if option pressed
				{
					if (optionIndex == 0)	//only option in SFML matrix is eraser
					{
						levelMatrix[i][j] = m_objects.setGetObject(i, j, EMPTY_BUT);	//draw empty slot
						updateBoardRepresentation(EMPTY, i, j);
					}
				}
			}
		}
	}
	return false;
}
//moved on matrix event function--------------------------------
void EditorManager::movedOnMatrix(std::vector < std::vector < sf::RectangleShape > > &levelMatrix,
	sf::RenderWindow &window, bool optionIsPressed)
{
	int i, j;
	for (i = 0; i < levelMatrix.size(); i++)
	{
		for (j = 0; j < levelMatrix[i].size(); j++)
		{
			sf::FloatRect buttonLoc = levelMatrix[i][j].getGlobalBounds();
			if (buttonLoc.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				if (!isValid(i, j))
				{
					if (!optionIsPressed)//if a key is pressed light it in a color (differnt colors for object/option) 
					{					//for the button itself, and also on matrix - object will be red or green if valid
						levelMatrix[i][j].setOutlineColor(sf::Color::Red);//but eraser is valid on object so therfore
					}														//will be green
					else
					levelMatrix[i][j].setOutlineColor(sf::Color::Green);

				}
				else
				{
					levelMatrix[i][j].setOutlineColor(sf::Color::Green);
				}
				levelMatrix[i][j].setOutlineThickness(8);
			}
			else
			{								//clear button when move to another
				levelMatrix[i][j].setOutlineColor(sf::Color::Black);
				levelMatrix[i][j].setOutlineThickness(3);
			}
		}
	}
}
//--------------------functions to handle different operations according to event accured --------------------
//light button function--------------------------------
void EditorManager::lightButton(std::vector < sf::RectangleShape >& bar, int& index, int i)
{
	bar[index].setOutlineColor(sf::Color::Black);
	bar[index].setOutlineThickness(3);			//light buttons
	if (bar.size() <= 3)
	{
		bar[i].setOutlineColor(sf::Color::Blue);//blue for option bar
		bar[i].setOutlineThickness(8);
	}
	else
	{
		bar[i].setOutlineColor(sf::Color::Green);//green for object bar
		bar[i].setOutlineThickness(8);
	}
	index = i;		//updating by referance index that pressed - and sending back to runeditor func
}
//check if valid function--------------------------------
bool EditorManager::isValid(int i, int j)
{
	if (getBoardRepresentation()[i][j] == EMPTY)	//checking if a key is valid
		return true;
	else
		return false;
}
//save function--------------------------------
void EditorManager::saveFile(Board newBoard)
{				//saving the TXT representation to a file called board.txt (or creating and saving if not exist)
	std::ofstream outPutFile;
	outPutFile.open("Board.txt");
	outPutFile << newBoard.getRow() << EMPTY << newBoard.getCol() << EMPTY << newBoard.getNumOfRocks() << endl;
	for (int i = 0; i < newBoard.getRow(); i++)
	{
		for (int j = 0; j < newBoard.getCol(); j++)
		{
			outPutFile << getBoardRepresentation()[i][j];
		}
		outPutFile << endl;
	}
	outPutFile.close();
}
//open file function--------------------------------
bool EditorManager::openFile(std::ifstream& levelFile)
{
	levelFile.open("Board.txt");			//function to open the game file
	if (!levelFile.is_open())
		return false;
	else
	{
		levelFile.close();
		return true;
	}
}
//build level frim input function--------------------------------
void EditorManager::buildBoardFromFile(std::vector <std::vector < char > > boardFromFile,
	std::vector < std::vector < sf::RectangleShape > >& levelMatrix)
{
	m_objects.loadObjects();
	for (int i = 0; i < levelMatrix.size(); i++)	//build the SFML representation from input file
	{
		for (int j = 0; j < levelMatrix[0].size(); j++)
		{
			if (boardFromFile[i][j] == DIGGER)
				levelMatrix[i][j] = m_objects.setGetObject(i, j, DIGGER_BUT);
			if (boardFromFile[i][j] == MONSTER)
				levelMatrix[i][j] = m_objects.setGetObject(i, j, MONSTER_BUT);
			if (boardFromFile[i][j] == DIAMOND)
				levelMatrix[i][j] = m_objects.setGetObject(i, j, DIAMOND_BUT);
			if (boardFromFile[i][j] == ROCK)
				levelMatrix[i][j] = m_objects.setGetObject(i, j, ROCK_BUT);
			if (boardFromFile[i][j] == WALL)
				levelMatrix[i][j] = m_objects.setGetObject(i, j, WALL_BUT);
		}
	}
}