#pragma once

#include <iostream>
#include <string>

static class Debug {

	public:
		static void print(std::string message);
		static void log_error(std::string message, bool halt_engine);
		static void clear_log();
};