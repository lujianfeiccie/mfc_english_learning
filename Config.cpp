#include "StdAfx.h"
#include "Config.h"

Config* Config::instance = NULL;
Config* Config::getInstance()
{
	if(instance == NULL)
	{
		instance = new Config;
	}
	return instance;
}
Config::Config(void)
{
	memset(file_name,0,100);
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
	//char bufferCurDir[1024];
	//GetCurrentDirectory(1024,bufferCurDir);
	//strcat(bufferCurDir,"\\");
	//strcat(bufferCurDir,file_name);
	if(file_name[0]==0 && file_name[99]==0) return;
	WriteConfig(APP_NAME,keyname,value,file_name);
}
void Config::ReadConfig(const char* appname,const char* keyname,char* value,unsigned int size,const char* file)
{
	GetPrivateProfileString(APP_NAME,keyname,"",value,size,file);
}
void Config::ReadConfig(const char* keyname,char* value)
{
	///////////////获取当前文件夹路径//////////////////////
	char bufferCurDir[1024];
	//GetCurrentDirectory(1024,bufferCurDir);
	//strcat(bufferCurDir,"\\");
	//strcat(bufferCurDir,file_name);
	if(file_name[0]==0 && file_name[99]==0) return;
	ReadConfig(APP_NAME,keyname,value,1024,file_name);	
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