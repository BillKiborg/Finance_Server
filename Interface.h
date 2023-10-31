#pragma once
#include <iostream>
#include <memory>

class Abstract_Response {
public:
	virtual ~Abstract_Response() = default;
};

class Transmitter {
public:
	virtual ~Transmitter() = default;
	virtual void run() = 0;
	//virtual bool send_response(Abstract_Response*) = 0;
};

//-------------------------------------------------------------------------------

class Abstract_Validator {
	virtual ~Abstract_Validator() = default;
};

class Transmission_Queue_Manager { 
public:
	virtual ~Transmission_Queue_Manager() = default;
	virtual void add_query(std::string) = 0;
	virtual std::unique_ptr<Abstract_Response> get_response() = 0;
};

class Processing_Queue_Manager { 
public:
	virtual ~Processing_Queue_Manager() = default;
	virtual std::string get_query() = 0;
	virtual void add_response(std::unique_ptr<Abstract_Response>) = 0;
};