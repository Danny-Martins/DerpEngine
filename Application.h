#pragma once
// #ifndef

#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>

class Application{

	public:
		const bool is_debug_mode;
		unsigned int mhz;

	public:
		Application();

	private:
		bool init_python();
		unsigned int get_aviliable_disk_space();
		unsigned int get_cpu_speed();
		std::string get_cpu_architecture();
		bool check_hardware();
		bool init();
};
