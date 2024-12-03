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
	afx_msg void OnBnClickedSearchConfirm();   // 添加搜索按钮点击函数声明
	afx_msg void OnBnClickedCancel();          // 添加取消按钮的消息处理声明
};