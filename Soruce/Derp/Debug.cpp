#include "Debug.hpp"
#include "DerpEngine.h"

void Debug::print(std::string message) {
	std::cout << message << std::endl;
}

void Debug::clear_log() {
	system("cls");
}

void Debug::log_error(std::string message, bool halt_engine) {
	std::cout << "===========================================" <<
		"\n ERROR LOGGED HALT= " << halt_engine << "\n" << message <<
		"\n===========================================" << std::endl;
	if (halt_engine)
		system("pause");
}