#include "Objects.h"

//--------------------constructor function --------------------
Objects::Objects()
{}

//--------------------set (definition) functions --------------------
//functions to build bars-------------------------
void Objects::buildBars(int row)
{
	loadObjects();
	Slot newSlot;
	int i;
	for (i = 0; i < OBJECT_BUTTONS; i++)				//building the objects toolbar---
	{
		m_objectBar.push_back(newSlot.getSlot()); //define new slot using inheritance

		m_objectBar[i].setPosition(i * SLOT_SIZE + (i * SLOT_GAP), //seting new location
			((row + 1) * SLOT_SIZE) + VERTICAL_GAP + (row * SLOT_GAP));

		if (i == 0)										//setting texture
			m_objectBar[i].setTexture(&m_diggerTex);
		if (i == 1)
			m_objectBar[i].setTexture(&m_monsterTex);
		if (i == 2)
			m_objectBar[i].setTexture(&m_diamondTex);
		if (i == 3)
			m_objectBar[i].setTexture(&m_rockTex);
		if (i == 4)
			m_objectBar[i].setTexture(&m_wallTex);
	}
	int count = 0;
	for (; i < NUM_OF_BUTTONS; i++)						//building the options toolbar---
	{
		m_optionsBar.push_back(newSlot.getSlot());			//same operation as object bar

		m_optionsBar[count].setPosition((i * SLOT_SIZE) + HORIZONTAL_GAP + (i * SLOT_GAP),
			((row + 1) * SLOT_SIZE) + VERTICAL_GAP + (row * SLOT_GAP));

		if (count == 0)
			m_optionsBar[count].setTexture(&m_eraseTex);
		if (count == 1)
			m_optionsBar[count].setTexture(&m_saveTex);
		if (count == 2)
			m_optionsBar[count].setTexture(&m_trashTex);
		count++;
	}
}
//functions to load images into texture members---------------
void Objects::loadObjects()
{
	m_diggerTex.loadFromFile("Dig.png");		
	m_rockTex.loadFromFile("Rock.png");
	m_diamondTex.loadFromFile("diamond.png");
	m_monsterTex.loadFromFile("Monster.png");
	m_wallTex.loadFromFile("wall.jpg");
	m_eraseTex.loadFromFile("erase.png");
	m_trashTex.loadFromFile("trash.png");
	m_saveTex.loadFromFile("save.png");
}

//functions to set and get a certain object---------------
sf::RectangleShape Objects::setGetObject(int i, int j, int numOfObject)
{
	Slot temp;
	sf::RectangleShape rec = temp.getSlot();

	if (numOfObject == 0)
		rec.setTexture(&m_diggerTex);
	if (numOfObject == 1)
		rec.setTexture(&m_monsterTex);	//according to desired object
	if (numOfObject == 2)				//setting texture and sending to
		rec.setTexture(&m_diamondTex);	//set position func, than returning
	if (numOfObject == 3)				//the rectangle created
		rec.setTexture(&m_rockTex);
	if (numOfObject == 4)
		rec.setTexture(&m_wallTex);
	if (numOfObject == 5)
	{
		rec.setOutlineThickness(3);		//empty slot
		rec.setFillColor(sf::Color(100, 100, 100));
		rec.setOutlineColor(sf::Color::Black);
	}
	setNewPos(rec, i, j);
	return rec;
}
//functions to set position of a object created----- called by setGetObject func----------
void Objects::setNewPos(sf::RectangleShape& shape, int i, int j)
{
	if (i == 0)
	{
		if (j == 0)					//position algorithm, according to gap between each slot and matrix size
			shape.setPosition(((j + 1) * SLOT_SIZE), ((i + 1) * SLOT_SIZE));
		else
			shape.setPosition(((j + 1) * SLOT_SIZE) + (SLOT_GAP * j), ((i + 1) * SLOT_SIZE));
	}
	else
		shape.setPosition(((j + 1) * SLOT_SIZE) + (SLOT_GAP * j), ((i + 1) * SLOT_SIZE) + (SLOT_GAP * i));
}
//get objectbar function----------------------------------------
std::vector < sf::RectangleShape > Objects::getObjectBar() const
{
	return m_objectBar;			//get the object bar
}
//get optionbar function----------------------------------------
std::vector < sf::RectangleShape > Objects::getOptionstBar() const
{
	return m_optionsBar;		//get the options bar
}