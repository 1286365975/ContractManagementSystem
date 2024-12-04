// contractInfo.cpp
#include "pch.h"
#include "ContractManagementSystem.h"
#include "afxdialogex.h"
#include "ContractInfo.h"

#include<string.h>

IMPLEMENT_DYNAMIC(contractInfo, CDialogEx)

BOOL contractInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_status.AddString(_T("已完成"));
    m_status.AddString(_T("进行中"));
    m_status.AddString(_T("违约"));
    if (!m_status_result.IsEmpty()) {
        int nIndex = m_status.FindStringExact(-1, m_status_result); // 查找匹配的项
        if (nIndex != CB_ERR) {
            m_status.SetCurSel(nIndex); // 设置选中项
        }
    }

    return TRUE;
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
    GetDlgItem(IDC_NAME)->GetWindowText(m_name);
    GetDlgItem(IDC_DATE)->GetWindowText(m_date);
    GetDlgItem(IDC_CLIENT_NAME)->GetWindowText(m_client_name);
    GetDlgItem(IDC_AMOUNT)->GetWindowText(m_amount);
    GetDlgItem(IDC_START_DATE)->GetWindowText(m_start_date);
    GetDlgItem(IDC_END_DATE)->GetWindowText(m_end_date);

    int index = m_status.GetCurSel();
    m_status.GetLBText(index, m_status_result);

    CT2A d1(m_name);       
    CT2A d2(m_date);        
    CT2A d3(m_client_name);
    CT2A d4(m_amount);    
    CT2A d5(m_start_date);  
    CT2A d6(m_end_date);   
    CT2A d7(m_status_result); 

    EndDialog(IDOK); 
}