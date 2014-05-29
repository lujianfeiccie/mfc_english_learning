#pragma once
#define APP_NAME "APP_NAME"
typedef struct 
{
   int no;
   int starttime;
   int endtime;
}Record;
class Config
{
public:	
	static Config* getInstance();
	char file_name[100];
	Config(void);
	~Config(void);
private:
	static Config* instance;
	
	void WriteConfig(const char* appname,const char* keyname,const char* value,const char* file);
	void WriteConfig(const char* keyname,const char* value);
	void ReadConfig(const char* appname,const char* keyname,	char* value,unsigned int size,const char* file);
	void ReadConfig(const char* keyname,char* value);
public:
	void ReadConfig(Record* record);
	void WriteConfig(const Record* record);
};
