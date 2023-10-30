#pragma once

class Transmitter {
public:
	virtual ~Transmitter() = default;
	virtual void run() = 0;
};