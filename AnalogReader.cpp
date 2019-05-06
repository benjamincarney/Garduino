#include "AnalogReader.h"

#include <Arduino.h>

AnalogReader::AnalogReader(const int pin) : m_pin(pin) {}

/**
 * Read analog value from 
 */
int AnalogReader::read()
{
	return analogRead(m_pin);
}
