#include "AnalogReader.h"

#include <Arduino.h>

AnalogReader::AnalogReader(const int pin) : m_pin(pin) {}

/**
 * R
 */
int AnalogReader::read()
{
	return analogRead(m_pin);
}
