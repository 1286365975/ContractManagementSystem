#pragma once
#include "afxdialogex.h"


// addContracts 对话框

class addContracts : public CDialogEx
{
	DECLARE_DYNAMIC(addContracts)

public:
	addContracts(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addContracts();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
