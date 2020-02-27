#include <windows.h>
#include <Lmcons.h>
#include <iostream>
#include <iomanip>
#include "NanoLog.hpp"


std::string returnUser()
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;

	GetUserName(username, &username_len);

	return username;
}

int main(int argc, char* argv[])
{
	std::ofstream logfile("log.txt", std::ios_base::app);
	tl::TinyLog filelog(tl::TinyLog::DEBUG, &logfile);
	
	filelog << "I was called by user: " << returnUser().c_str() << std::endl;
	std::cout << "I was called by user: " << returnUser().c_str() << std::endl;
}
