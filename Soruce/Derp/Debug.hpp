#pragma once

#include <iostream>
#include <string>

class Debug {

	public:
		void static print(std::string message);
		void static log_error(std::string message, bool halt_engine);
		void static clear_log();

	//quick and dirty way to disallow instances of this class
	private:
		Debug();
};