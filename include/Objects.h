#pragma once

//--------------------include Section --------------------
#include "Slot.h"

//--------------------Objects Class definition --------------------
class Objects : public Slot
{				
public:					//***inherits from Slot***
	//constructor ---------------
	Objects();

	//set functions ---------------
	void buildBars(int row); //building bars
	void loadObjects(); // load all objects to textures
	void setNewPos(sf::RectangleShape& shape, int i, int j); //setting new location for slot

	sf::RectangleShape setGetObject(int i, int j, int numOfObject); //set and get objects

	//get functions ---------------
	std::vector < sf::RectangleShape > getObjectBar() const;	//get object/options bar
	std::vector < sf::RectangleShape > getOptionstBar() const;

private:
	//class members---------------
	std::vector < sf::RectangleShape >  m_objectBar; //object bar
	std::vector < sf::RectangleShape >  m_optionsBar; //option bar
	//textures members---------
	sf::Texture m_diggerTex;
	sf::Texture m_monsterTex;
	sf::Texture m_diamondTex;
	sf::Texture m_rockTex;
	sf::Texture m_wallTex;
	sf::Texture m_eraseTex;
	sf::Texture m_trashTex;
	sf::Texture m_saveTex;
};