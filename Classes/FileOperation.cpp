// to enable CCLOG()
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "FileOperation.h"
#include <stdio.h>

USING_NS_CC;
using namespace std;

void FileOperation::saveFile(string sFileContents, FILE_TYPE fileType)
{
	string path = getFilePath(fileType);
	FILE *fp = fopen(path.c_str(), "w");
	if (! fp)
	{
		CCLOG("can not create file %s", path.c_str());
		return;
	}
	//const char * cFileContents = fileContents.c_str();
	fputs(sFileContents.c_str(), fp);
	fclose(fp);
}

vector<string> FileOperation::readFile(FILE_TYPE fileType)
{
	vector<string> mFileContents;
	const unsigned int fileSize = 50;
	char buf[fileSize] = { 0 };

	string path = getFilePath(fileType);
	FILE* fp = fopen(path.c_str(), "r");
	if (!fp)
	{
		CCLOG("can not open file %s", path.c_str());
		return mFileContents;
	}
	// Get file contents line by line
	while (fgets(buf, fileSize, fp))
	{
		// Put all lines in vector
		mFileContents.push_back(buf);
		// pop back "\n"
		mFileContents.back().pop_back();
	}

	fclose(fp);

	return mFileContents;
}

void FileOperation::removeFile(FILE_TYPE fileType)
{
	CCFileUtils::getInstance()->removeFile(getFilePath(fileType));
}

string FileOperation::getFilePath(FILE_TYPE fileType)
{
	string path("");
	switch (fileType)
	{
		case PLAYER_DATA_FILE_TYPE:
		{
			path = CCFileUtils::getInstance()->getWritablePath() + "playerfile";
			break;
		}
		case LEVEL_DATA_FILE_TYPE:
		{
			path = CCFileUtils::getInstance()->getWritablePath() + "levelfile";
			break;
		}
		case CURRENCY_DATA_FILE_TYPE:
		{
			path = CCFileUtils::getInstance()->getWritablePath() + "currencyfile";
			break;
		}
	}
//	string path("");
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	// In android, every programe has a director under /data/data.
//	// The path is /data/data/ + start activity package name.
//	// You can save application specific data here.
//	path.append("/data/data/org.cocos2dx.application/tmpfile");
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	// You can save file in anywhere if you have the permision.
//	path.append("D:/tmpfile");
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
//	path = cocos2d::CCApplication::sharedApplication().getAppDataPath();
//
//#ifdef _TRANZDA_VM_
//	// If runs on WoPhone simulator, you should insert "D:/Work7" at the
//	// begin. We will fix the bug in no far future.
//	path = "D:/Work7" + path;
//	path.append("tmpfile");
//#endif
//
//#endif

	return path;
}