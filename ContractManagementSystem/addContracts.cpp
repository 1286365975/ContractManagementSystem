// addContracts.cpp: 实现文件
//

#include "pch.h"
#include "ContractManagementSystem.h"
#include "afxdialogex.h"
#include "addContracts.h"


// addContracts 对话框

IMPLEMENT_DYNAMIC(addContracts, CDialogEx)

addContracts::addContracts(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIALOG, pParent)
{

}

addContracts::~addContracts()
{
}

void addContracts::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(addContracts, CDialogEx)
END_MESSAGE_MAP()


// addContracts 消息处理程序
