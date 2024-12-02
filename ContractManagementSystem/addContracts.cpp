#include "pch.h"
#include "ContractManagementSystem.h"
#include "afxdialogex.h"
#include "addContracts.h"

// 只需要包含 ContractManagementSystemDlg.h
#include "ContractManagementSystemDlg.h"

// 其他代码




// addContracts 对话框

IMPLEMENT_DYNAMIC(addContracts, CDialogEx)

BOOL addContracts::OnInitDialog()
{
	CDialogEx::OnInitDialog();  // 调用父类的 OnInitDialog 来完成默认的初始化

	InitCombobox();  // 初始化下拉框内容

	return TRUE;  // 返回 TRUE, 表示初始化成功
}


addContracts::addContracts(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIALOG, pParent)
	, m_name(_T(""))
	, m_date(_T(""))
	, m_client_name(_T(""))
	, m_amount(_T(""))
	, m_start_date(_T(""))
	, m_end_date(_T(""))
{

}

addContracts::~addContracts()
{
}

void addContracts::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(addContracts, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CONFIRM, &addContracts::OnBnClickedButtonAddConfirm)
	ON_EN_CHANGE(IDC_NAME, &addContracts::OnEnChangeName)
END_MESSAGE_MAP()


// addContracts 消息处理程序


void addContracts::OnBnClickedButtonAddConfirm()
{
    // 获取文本框和控件中的数据
    GetDlgItem(IDC_NAME)->GetWindowText(m_name);
    GetDlgItem(IDC_DATE)->GetWindowText(m_date);
    GetDlgItem(IDC_CLIENT_NAME)->GetWindowText(m_client_name);
    GetDlgItem(IDC_AMOUNT)->GetWindowText(m_amount);
    GetDlgItem(IDC_START_DATE)->GetWindowText(m_start_date);
    GetDlgItem(IDC_END_DATE)->GetWindowText(m_end_date);

    // 获取下拉框选中的状态
    int index = m_status.GetCurSel();
    TCHAR m_status_result[100] = { 0 };
    m_status.GetLBText(index, m_status_result);

    // 使用 CT2A 将 MFC CString 转换为 char*（ANSI 字符串）
    CT2A d1(m_name);        // contract_name
    CT2A d2(m_date);        // contract_data
    CT2A d3(m_client_name); // client_name
    CT2A d4(m_amount);      // contract_amount
    CT2A d5(m_start_date);  // start_date
    CT2A d6(m_end_date);    // end_date
    CT2A d7(m_status_result); // status

    // 构建 SQL 插入语句，假设 contract_id 是自增的
    std::string query = "INSERT INTO contracts (contract_name, contract_data, client_name, contract_amount, start_date, end_date, status) VALUES ('" + 
        std::string(d1) + "', '" + std::string(d2) + "', '" + std::string(d3) + "', '" + std::string(d4) + "', '" + 
        std::string(d5) + "', '" + std::string(d6) + "', '" + std::string(d7) + "')";

    // 执行 SQL 插入操作
    if (SQL.Query(query)) {
        AfxMessageBox(_T("添加成功"));
        CContractManagementSystemDlg* pDlg = (CContractManagementSystemDlg*)AfxGetMainWnd();
        EndDialog(IDOK);  // 结束对话框并返回 IDOK
        pDlg->LoadData();  // 加载最新数据
        pDlg->ShowData();  // 刷新界面显示

    } else {
        SQL.ErrorIntoMySQL();
        SQL.ShowErrorInto();

        //AfxMessageBox(_T("添加失败"));
    }
}


void addContracts::InitCombobox()
{
	m_status.AddString("已完成");
	m_status.AddString("进行中");
	m_status.AddString("违约");

}

void addContracts::OnEnChangeName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
