#pragma once
#include "afxdialogex.h"


// addContracts 对话框

class addContracts : public CDialogEx
{
	DECLARE_DYNAMIC(addContracts)

public:
	BOOL OnInitDialog();
	addContracts(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addContracts();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddConfirm();
	void InitCombobox();
	afx_msg void OnEnChangeName();
	CString m_name;
	CString m_date;
	CString m_client_name;
	CString m_amount;
	CString m_start_date;
	CString m_end_date;
	CComboBox m_status;
};
