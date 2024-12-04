#pragma once
#include "afxdialogex.h"


// SearchDlg 对话框

class SearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchDlg)

public:
	SearchDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SearchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_search_edit;
	CString m_search_combobox_result;
	CComboBox m_search_combobox;

	// 消息处理函数
	afx_msg void OnBnClickedSearchConfirm();   
	afx_msg void OnBnClickedCancel();   
};