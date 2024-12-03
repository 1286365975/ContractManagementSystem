// contractInfo.cpp
#include "pch.h"
#include "ContractManagementSystem.h"
#include "afxdialogex.h"
#include "ContractInfo.h"

#include<string.h>

IMPLEMENT_DYNAMIC(contractInfo, CDialogEx)

BOOL contractInfo::OnInitDialog()
{
    // 调用父类的 OnInitDialog 来完成默认初始化
    CDialogEx::OnInitDialog();

    // 初始化下拉框内容
    m_status.AddString(_T("已完成"));
    m_status.AddString(_T("进行中"));
    m_status.AddString(_T("违约"));
    if (!m_status_result.IsEmpty()) {
        int nIndex = m_status.FindStringExact(-1, m_status_result); // 查找匹配的项
        if (nIndex != CB_ERR) {
            m_status.SetCurSel(nIndex); // 设置选中项
        }
    }

    return TRUE; // 返回 TRUE 表示初始化完成
}

contractInfo::contractInfo(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_ADD_DIALOG, pParent),
    m_name(_T("")),
    m_date(_T("")),
    m_client_name(_T("")),
    m_amount(_T("")),
    m_start_date(_T("")),
    m_end_date(_T(""))
{
}

contractInfo::~contractInfo()
{
}

void contractInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME, m_name);
    DDX_Text(pDX, IDC_DATE, m_date);
    DDX_Text(pDX, IDC_CLIENT_NAME, m_client_name);
    DDX_Text(pDX, IDC_AMOUNT, m_amount);
    DDX_Text(pDX, IDC_START_DATE, m_start_date);
    DDX_Text(pDX, IDC_END_DATE, m_end_date);
    DDX_Control(pDX, IDC_STATUS, m_status);
}

BEGIN_MESSAGE_MAP(contractInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ADD_CONFIRM, &contractInfo::OnBnClickedButtonConfirm)
END_MESSAGE_MAP()

void contractInfo::InitCombobox()
{
    m_status.AddString("已完成");
    m_status.AddString("进行中");
    m_status.AddString("违约");
}

void contractInfo::OnBnClickedButtonConfirm()
{
    // 获取控件中的数据
    GetDlgItem(IDC_NAME)->GetWindowText(m_name);
    GetDlgItem(IDC_DATE)->GetWindowText(m_date);
    GetDlgItem(IDC_CLIENT_NAME)->GetWindowText(m_client_name);
    GetDlgItem(IDC_AMOUNT)->GetWindowText(m_amount);
    GetDlgItem(IDC_START_DATE)->GetWindowText(m_start_date);
    GetDlgItem(IDC_END_DATE)->GetWindowText(m_end_date);

    // 获取下拉框选中的状态
    int index = m_status.GetCurSel();
    m_status.GetLBText(index, m_status_result);

    // 使用 CT2A 将 MFC CString 转换为 char*（ANSI 字符串）
    CT2A d1(m_name);        // contract_name
    CT2A d2(m_date);        // contract_data
    CT2A d3(m_client_name); // client_name
    CT2A d4(m_amount);      // contract_amount
    CT2A d5(m_start_date);  // start_date   
    CT2A d6(m_end_date);    // end_date
    CT2A d7(m_status_result); // status

    EndDialog(IDOK);  // 结束对话框并返回 IDOK
}