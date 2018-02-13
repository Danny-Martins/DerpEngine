#pragma once
// #ifndef

#include <string>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include <Windows.h>
#include <WinBase.h>
#include <direct.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "DerpEngine.h"

DerpEngine::DerpEngine() : is_debug_mode(true){

	std::cout << "starting app \n";

	this->check_hardware();
	this->init_graphics();
}

bool DerpEngine::check_hardware() {
	std::cout << "Starting init \n ";

	this->check_enough_disk_space();
	//this->mhz = this->get_cpu_speed();
	//std::cout << mhz << std::endl;
	this->get_cpu_architecture();
	this->check_memory();
	//this->check_io_devices();

	std::cout << "hardware cheked son \n\n";

	return true;
}


unsigned int DerpEngine::check_enough_disk_space() {
	// int const drive = _getdrive();
	// struct _diskfree_t diskfree;  
	// _getdiskfree(drive, &diskfree);  
	// unsigned __int64 const needed_clusters = disk_bytes_needed /
	// (diskfree.sectors_per_cluster*diskfree.bytes_per_sector);  

	// return diskfree.avail_clusters*diskfree.bytes_per_sector;
	
	const DWORDLONG disk_bytes_needed = 300000000;

	int const drive = _getdrive();
	//int const drive = 0;
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const needed_clusters = disk_bytes_needed /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < needed_clusters) {
		std::cout << "ERROR NOT ENOUGH SPACE" << std::endl;
		return false;
	}
	return true;
}

unsigned int DerpEngine::get_cpu_speed() {
	
	DWORD buffer_size = sizeof(DWORD);
	DWORD mhz = 0;
	DWORD value_type = REG_DWORD;
	HKEY hive_key;

	long error_type = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hive_key);
	if (error_type == ERROR_SUCCESS) {
		RegQueryValueEx(hive_key,
			"~MHz", NULL, &value_type, (LPBYTE)&mhz, &buffer_size);
	}
	else {
		std::cout << "Could get CPU speed";
		return 0;
	}
	return mhz;
}

std::string DerpEngine::get_cpu_architecture() {

	TCHAR architecture[1024];
	DWORD architecture_length = sizeof(architecture);
	DWORD value_type = REG_SZ;
	HKEY hive_key;
	long error_type = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hive_key);
	if (error_type == ERROR_SUCCESS) {
		RegQueryValueEx(hive_key, TEXT("ProcessorNameString"), NULL, &value_type,
			reinterpret_cast<LPBYTE>(&architecture), &architecture_length);
	}
	std::cout << architecture << std::endl;
	
	return "DERP";
}

//plz fix this
void DerpEngine::check_memory() {

	MEMORYSTATUSEX memoryStatus;
	GlobalMemoryStatusEx(&memoryStatus);

	DWORDLONG phyiscal_memory = memoryStatus.ullAvailPhys;

	DWORDLONG virtual_memory = memoryStatus.ullAvailVirtual;

	std::cout << "You have " << phyiscal_memory << " avaliable bytes for phyisical memory." << std::endl;

	std::cout << "You have " << virtual_memory << " avaliable bytes for virtual memory." << std::endl;

}

void DerpEngine::init_graphics() {
	DerpEngine::render_window.create(sf::VideoMode(800, 600), "Derp Engine", sf::Style::Close);
}