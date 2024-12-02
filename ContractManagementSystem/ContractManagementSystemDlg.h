
// ContractManagementSystemDlg.h: 头文件
//
#include"HMySQL.h"
#pragma once



// CContractManagementSystemDlg 对话框
class CContractManagementSystemDlg : public CDialogEx
{
// 构造
public:
	CContractManagementSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTRACTMANAGEMENTSYSTEM_DIALOG };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX)
		{
			CDialogEx::DoDataExchange(pDX);
			DDX_Control(pDX, IDC_LIST, m_listCtrl);
		}	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedButton2();
	void ShowData();   // 显示数据
	void LoadData();
	bool ConnectDB();

	void InitListCtrl();

	CListCtrl m_listCtrl;

	std::vector<std::string> OneStr;   // 存储一行数据
	std::vector<std::vector<std::string>> AllStr;   // 存储所有查询结果（二维数组）
private:
	HMySQL SQL;
public:
	CStatic m_num;
};


