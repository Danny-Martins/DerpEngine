#pragma once
// #ifndef

#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dos.h>
#include <assert.h>
#include "Application.h"
#include <Python/python.h>
#include <direct.h>
#include <ctype.h>
#include <WinBase.h>
#include <Windows.h>
#include <stdlib.h>

Application::Application() : is_debug_mode(true){
	std::cout << "starting app \n";

	this->init();

	//this->is_debug_mode = true;

	//this->init_python();

	// this->init();
}

bool Application::init(){
	// this->herp = 15;
	// std::cout << "inside init";

	//this->check_hardware();

	this->mhz = this->get_cpu_speed();
	std::cout << mhz << std::endl;

	this->get_cpu_architecture();


}

bool Application::init_python(){

}

unsigned int Application::get_aviliable_disk_space(){
	// int const drive = _getdrive();
	// struct _diskfree_t diskfree;  
	// _getdiskfree(drive, &diskfree);  
	// //unsigned __int64 const needed_clusters = disk_bytes_needed /
	// //	(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);  
	
	// return diskfree.avail_clusters*diskfree.bytes_per_sector;
	const DWORDLONG disk_bytes_needed = 300000000;

	int const drive = _getdrive();
	struct _diskfree_t diskfree;  
	_getdiskfree(drive, &diskfree);  
	unsigned __int64 const needed_clusters = disk_bytes_needed /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);  
	if (diskfree.avail_clusters < needed_clusters){
		std::cout << "NOT ENOUGH SPACE" << std::endl;
		return false;
	}
	return true;
}

unsigned int Application::get_cpu_speed(){
	DWORD buffer_size = sizeof(DWORD); 
	DWORD mhz = 0;
	DWORD value_type = REG_DWORD;
	HKEY hive_key;

	long error_type = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hive_key);
	if(error_type == ERROR_SUCCESS){  
		RegQueryValueEx(hive_key, 
			"~MHz", NULL, &value_type, (LPBYTE)&mhz, &buffer_size);
	}
	else{
		std::cout << "Could get CPU speed";
		return 0;
	}
	return mhz;
}

std::string Application::get_cpu_architecture() {

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
}
