#pragma once

#include <Windows.h>

#include <sstream> 
#include <fstream>
#include <string>

#include "ComponentBase.h"
#include "AddInDefBase.h"


inline std::string rjust(std::string text, size_t width, char fillchar = '0') {
	if (text.size() >= width) {
		return text;
	}
	std::string returnString = text;
	returnString.insert(0, width - text.size(), fillchar);
	return returnString;
}

inline void myLog(std::string text) {
	/*
	std::wstring messageW(text.begin(), text.end());
	WCHAR_T* wsData = messageW.data();

	std::string LOG_FILE_PATH = "C:/log.txt";
	std::ofstream outfile;

	SYSTEMTIME st;
	GetLocalTime(&st);
	std::stringstream buf;
	buf << st.wYear << "." <<
		rjust(std::to_string(st.wMonth), 2) << "." <<
		rjust(std::to_string(st.wDay), 2) << " " <<
		rjust(std::to_string(st.wHour), 2) << ":" <<
		rjust(std::to_string(st.wMinute), 2) << ":" <<
		rjust(std::to_string(st.wSecond), 2) << "_" <<
		rjust(std::to_string(st.wMilliseconds), 3);
	auto now = buf.str();

	std::ofstream logfile;
	logfile.open(LOG_FILE_PATH, std::ios_base::app);
	logfile << now << " | " << text << std::endl;
	logfile.close();
	*/
}

bool sendall(int fd, std::string message);