// HMySQL

// 功能描述：实现对MySQL访问操作的封装
#ifndef __HMYSQL__H__  
#define __HMYSQL_H__  

#include <string>  
#include <vector>  
#include <mysql.h>

#include <winsock.h>
#define ERROR_QUERY_FAIL -1 // 操作失败


// 定义MySQL连接信息
typedef struct
{
	char* server;
	char* user;
	char* password;
	char* database;
	int port;
}MySQLConInfo;

class HMySQL
{
public:
	HMySQL();
	virtual ~HMySQL();

	void SetMySQLConInfo(char* server, char* username, char* password, char* database, int port);// 设置连接信息
	bool Open();  // 打开连接
	void Close(); // 关闭连接
	bool Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data);	     // 读取数据
	bool Query(const std::string& Querystr);     // 其他操作
	int GetInsertID(const std::string& Querystr);// 插入并获取插入的ID,针对自动递增ID
	void ErrorIntoMySQL();		 // 错误消息
	void ShowErrorInto();        // 显示

public:
	int ErrorNum;				 // 错误代号  
	const char* ErrorInfo;       // 错误提示  

private:
	MySQLConInfo mysqlcon;	 // 连接信息 库
	MYSQL mysql;		 // MySQL对象 表
	MYSQL_RES* result;		 // 用于存放结果 
};

#endif  