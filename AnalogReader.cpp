#include "AnalogReader.h"

#include <Arduino.h>

AnalogReader::AnalogReader(const int pin) : m_pin(pin) {}

/**
 * Read analog valu
 */
int AnalogReader::read()
{
	return analogRead(m_pin);
}
