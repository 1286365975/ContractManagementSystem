// contractInfo.h
#pragma once
#include "afxwin.h"

class contractInfo : public CDialogEx
{
    DECLARE_DYNAMIC(contractInfo)

public:
    BOOL OnInitDialog();
    contractInfo(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~contractInfo();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_INFO_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    CString m_name;
    CString m_date;
    CString m_client_name;
    CString m_amount;
    CString m_start_date;
    CString m_end_date;
    CComboBox m_status;
    CString m_status_result;

    // 界面控件初始化
    void InitCombobox();

    // 确认按钮点击事件，传递数据给主界面
    afx_msg void OnBnClickedButtonConfirm();
};