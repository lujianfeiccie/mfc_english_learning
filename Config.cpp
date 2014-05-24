#include "StdAfx.h"
#include "Config.h"


Config::Config(void)
{
}


Config::~Config(void)
{

}
void Config::WriteConfig(const char* appname,const char* keyname,const char* value,const char* file)
{
	WritePrivateProfileString(appname,keyname,value,file);
}
void Config::WriteConfig(const char* keyname,const char* value)
{
	///////////////获取当前文件夹路径//////////////////////
	char bufferCurDir[1024];
	GetCurrentDirectory(1024,bufferCurDir);
	strcat(bufferCurDir,"\\");
	strcat(bufferCurDir,FILE_NAME);
	WriteConfig(APP_NAME,keyname,value,bufferCurDir);
}
void Config::ReadConfig(const char* appname,const char* keyname,char* value,unsigned int size,const char* file)
{
	GetPrivateProfileString(APP_NAME,keyname,"",value,size,file);
}
void Config::ReadConfig(const char* keyname,char* value)
{
	///////////////获取当前文件夹路径//////////////////////
	char bufferCurDir[1024];
	GetCurrentDirectory(1024,bufferCurDir);
	strcat(bufferCurDir,"\\");
	strcat(bufferCurDir,FILE_NAME);

	ReadConfig(APP_NAME,keyname,value,1024,bufferCurDir);	
}

void Config::ReadConfig(Record* record)
{
	char keyname[50];
	
	char tempstr[50];
	
	//start
	sprintf(keyname,"start%d",record->no);
	ReadConfig(keyname,tempstr);
	record->starttime = atoi(tempstr);
	//end
	sprintf(keyname,"end%d",record->no);
	ReadConfig(keyname,tempstr);
	record->endtime = atoi(tempstr);
}

void Config::WriteConfig(const Record* record)
{
	char keyname[50];
	char tempstr[50];
	//start
	sprintf(keyname,"start%d",record->no);
	sprintf(tempstr,"%d",record->starttime);
	WriteConfig(keyname,tempstr);
	//end
	sprintf(keyname,"end%d",record->no);
	sprintf(tempstr,"%d",record->endtime);
	WriteConfig(keyname,tempstr);
}