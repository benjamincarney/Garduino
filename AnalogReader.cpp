#include "AnalogReader.h"

#include <Arduino.h>

AnalogReader::AnalogReader(const int pin) : m_pin(pin) {}

/**
 * Read ana
 */
int AnalogReader::read()
{
	return analogRead(m_pin);
}
