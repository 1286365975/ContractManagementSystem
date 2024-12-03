// SearchDlg.cpp: 实现文件
//

#include "pch.h"
#include "ContractManagementSystem.h"
#include "afxdialogex.h"
#include "SearchDlg.h"


// SearchDlg 对话框

IMPLEMENT_DYNAMIC(SearchDlg, CDialogEx)

SearchDlg::SearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCH_DIALOG, pParent)
	, m_search_edit(_T(""))
{

}

SearchDlg::~SearchDlg()
{
}

void SearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_search_edit);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_search_combobox);
}


BEGIN_MESSAGE_MAP(SearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SEARCH_CONFIRM, &SearchDlg::OnBnClickedSearchConfirm)
	ON_BN_CLICKED(IDCANCEL, &SearchDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL SearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化下拉框数据
	m_search_combobox.AddString(_T("合同ID"));
	m_search_combobox.AddString(_T("合同名称"));
	m_search_combobox.AddString(_T("客户名称"));
	m_search_combobox.AddString(_T("合同金额"));

	return TRUE;  // 返回 TRUE 以启动对话框
}

// SearchDlg 消息处理程序


void SearchDlg::OnBnClickedSearchConfirm()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_SEARCH_EDIT)->GetWindowText(m_search_edit);
	// 获取下拉框选中的状态
	int index = m_search_combobox.GetCurSel();
	m_search_combobox.GetLBText(index, m_search_combobox_result);

	EndDialog(IDOK);  // 结束对话框并返回 IDOK
}


void SearchDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
