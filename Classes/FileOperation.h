#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>

class FileOperation 
{
public:
	static void saveFile(std::string vecFileContents);
	static std::vector<std::string> readFile();
	static std::string getFilePath();
};

#endif
