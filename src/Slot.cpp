#include "Slot.h"

//--------------------constructor function --------------------
Slot::Slot ()
{
	m_slot.setSize(sf::Vector2f(SLOT_SIZE, SLOT_SIZE));
	m_slot.setOutlineThickness(3);
	m_slot.setOutlineColor(sf::Color::Black);
	m_slotSize = 140; 
}

//--------------------set function--------------------
void Slot::setTexture(sf::Texture texture)
{
	m_slot.setTexture(&texture);
}	
void Slot::setSlotSize(int size)
{
	m_slotSize = size; 
}

//--------------------get function--------------------
sf::RectangleShape Slot::getSlot() const
{
	return m_slot;
}
int Slot::getSlotSize()
{
	return m_slotSize;
}