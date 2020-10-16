#pragma once
//--------------------include Section --------------------
#include <iostream>
#include <cstdlib> 
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <vector>

//--------------------const Section --------------------
//this consts are beeing used in most of the program ---
//with the help of the inheritance---

const int VERTICAL_GAP = 20; // gap between toolbars to matrix
const int HORIZONTAL_GAP = 50;//gap between toolbars
const int SLOT_GAP = 10;//gap between each slot
const int SLOT_SIZE = 80;	//size of each slot (rectangle)				
const int NUM_OF_BUTTONS = 8;//total num of buttons
const int OBJECT_BUTTONS = 5;
const int OPTIONS_BUTTONS = 3;
												 
const char DIGGER = '/';		
const char MONSTER = '!';
const char DIAMOND = 'D';	//charactars for board representation
const char ROCK = '@';		//in txt file
const char EMPTY = ' ';
const char WALL = '#';

const int DIGGER_BUT = 0;
const int MONSTER_BUT = 1;	//numbers to represent objects on matrix
const int DIAMOND_BUT = 2;	// for condition checks
const int ROCK_BUT = 3;
const int WALL_BUT = 4;
const int EMPTY_BUT = 5;

//--------------------Slot Class definition --------------------
class Slot
{
public:
	//constructor ---------------
	Slot();

	//setFunctions---------------
	void setTexture(sf::Texture texture);
	void setSlotSize(int size);

	//getFunctions---------------
	sf::RectangleShape getSlot() const;
	int getSlotSize();

private:
	//class members---------------
	sf::RectangleShape m_slot;
	int m_slotSize;
};