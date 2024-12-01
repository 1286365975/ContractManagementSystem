#include <winsock2.h>
#include <windows.h>
#include "HMySQL.h"
#include "afxwin.h"  // 包含 MFC 的头文件


//#include "HMySQL.h"//若多个文件包含，需要把该句移动到stdafx.h中

HMySQL::HMySQL() :
	ErrorNum(0), ErrorInfo("ok")
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&mysql);

	// 设置字符集，否则无法处理中文
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
}

HMySQL::~HMySQL()
{
}

// 设置连接信息
void HMySQL::SetMySQLConInfo(char* server, char* username, char* password, char* database, int port)
{
	mysqlcon.server = server;
	mysqlcon.user = username;
	mysqlcon.password = password;
	mysqlcon.database = database;
	mysqlcon.port = port;
}

// 打开连接
bool HMySQL::Open()
{
	if (mysql_real_connect(&mysql, mysqlcon.server, mysqlcon.user,
		mysqlcon.password, mysqlcon.database, mysqlcon.port, 0, 0) != NULL)
	{
		return true;
	}
	else
	{
		ErrorIntoMySQL();
		return false;
	}
}

// 断开连接
void HMySQL::Close()
{
	mysql_close(&mysql);
}

//读取数据
bool HMySQL::Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data)
{
	if (0 != mysql_query(&mysql, Querystr.c_str()))
	{
		ErrorIntoMySQL();
		return false;
	}

	result = mysql_store_result(&mysql);

	// 行列数
	int row = mysql_num_rows(result);
	int field = mysql_num_fields(result);

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);

	int j = 0;
	std::string temp;
	std::vector<std::vector<std::string> >().swap(data);
	while (NULL != line)
	{
		std::vector<std::string> linedata;
		for (int i = 0; i < field; i++)
		{
			if (line[i])
			{
				temp = line[i];
				linedata.push_back(temp);
			}
			else
			{
				temp = "";
				linedata.push_back(temp);
			}
		}
		line = mysql_fetch_row(result);
		data.push_back(linedata);
	}
	return true;
}

// 其他增删改的操作
bool HMySQL::Query(const std::string& Querystr)
{
	if (0 == mysql_query(&mysql, Querystr.c_str()))
	{
		return true;
	}
	ErrorIntoMySQL();
	return false;
}

// 插入并获取插入的ID,针对自动递增ID
int HMySQL::GetInsertID(const std::string& Querystr)
{
	if (!Query(Querystr))
	{
		ErrorIntoMySQL();
		return ERROR_QUERY_FAIL;
	}
	// 获取ID
	return mysql_insert_id(&mysql);
}

//错误信息
void HMySQL::ErrorIntoMySQL()
{
	ErrorNum = mysql_errno(&mysql);
	ErrorInfo = mysql_error(&mysql);
}
//错误信息
void HMySQL::ShowErrorInto()
{
	AfxMessageBox(ErrorInfo);//最好写到数据库日志里面  从日志里面读取加载到界面上，而不是弹出！
}