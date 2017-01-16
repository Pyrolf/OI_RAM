#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>

class FileOperation 
{
public:
	enum FILE_TYPE
	{
		PLAYER_DATA_FILE_TYPE = 0,
		LEVEL_DATA_FILE_TYPE,
		CURRENCY_DATA_FILE_TYPE,
		NUM_OF_FILE_TYPES
	};
	static void saveFile(std::string vecFileContents, FILE_TYPE fileType);
	static std::vector<std::string> readFile(FILE_TYPE fileType);
	static void removeFile(FILE_TYPE fileType);
private:
	static std::string getFilePath(FILE_TYPE fileType);
};

#endif
