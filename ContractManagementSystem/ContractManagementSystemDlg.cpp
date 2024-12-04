#include "framework.h"
#include "ContractManagementSystem.h"
#include "ContractManagementSystemDlg.h"
#include "afxdialogex.h"
#include "ContractInfo.h"
#include "SearchDlg.h"
#include "HMySQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HMySQL SQL;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CContractManagementSystemDlg 对话框



CContractManagementSystemDlg::CContractManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTRACTMANAGEMENTSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CContractManagementSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CContractManagementSystemDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CContractManagementSystemDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CContractManagementSystemDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CContractManagementSystemDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CContractManagementSystemDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CContractManagementSystemDlg::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// CContractManagementSystemDlg 消息处理程序

BOOL CContractManagementSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//初始化列表
	InitListCtrl();
	
	// 数据库连接
	if (ConnectDB()) {
		LoadData();
		ShowData();
	}
	else {
		AfxMessageBox("Connect ERROR");
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CContractManagementSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CContractManagementSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CContractManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CContractManagementSystemDlg::ShowData()
{
	m_listCtrl.DeleteAllItems();  // 清空列表控件

	if (AllStr.empty()) {
		AfxMessageBox("没有数据可显示");
		return;
	}
	for (int i = 0; i < AllStr.size(); i++) {
		for (int j = 0; j < AllStr[i].size(); j++) {
			if (j == 0)
				m_listCtrl.InsertItem(i, AllStr[i][j].c_str()); 
			else
				m_listCtrl.SetItemText(i, j, AllStr[i][j].c_str());
		}
	}

	// 输出查询结果数量
	CString strt;
	strt.Format("查询结果 %d 条", AllStr.size());
	if (GetDlgItem(IDC_TEXT)) {
		GetDlgItem(IDC_TEXT)->SetWindowText(strt);  // 更新查询统计
	}
}

void CContractManagementSystemDlg::LoadData()
{
	AllStr.clear();  // 清空之前的数据
	CString strsql = "SELECT * FROM contracts";  // SQL 查询语句

	// 执行查询并将结果存入 AllStr
	int row = SQL.Select(strsql.GetBuffer(), AllStr);

	// 调试信息
	CString debugMsg;
	debugMsg.Format("查询返回的行数: %d", row);

	// 如果没有数据
	if (row <= 0) {
		AfxMessageBox("没有查询到数据");
		return;
	}

	// 输出 AllStr 内容进行检查
	CString contentMsg;
	contentMsg.Format("数据内容:\n");
	for (int i = 0; i < AllStr.size(); i++) {
		contentMsg.AppendFormat("行 %d: ", i + 1);
		for (int j = 0; j < AllStr[i].size(); j++) {
			contentMsg.AppendFormat("%s ", AllStr[i][j].c_str());
		}
		contentMsg.Append("\n");
	}
}

bool CContractManagementSystemDlg::ConnectDB()
{
	SQL.SetMySQLConInfo("localhost", "contract_user", "password123", "contractmanagementsystem", 3306);
	if (!SQL.Open()) {
		return false; 
	}
	return true;
}

void CContractManagementSystemDlg::InitListCtrl()
{
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, _T("合同ID"), LVCFMT_LEFT, 60); // 合同ID
	m_listCtrl.InsertColumn(1, _T("合同名称"), LVCFMT_LEFT, 120); // 合同名称
	m_listCtrl.InsertColumn(2, _T("签订日期"), LVCFMT_LEFT, 100); // 签订日期
	m_listCtrl.InsertColumn(3, _T("客户名称"), LVCFMT_LEFT, 120); // 客户名称
	m_listCtrl.InsertColumn(4, _T("合同金额"), LVCFMT_LEFT, 100); // 合同金额
	m_listCtrl.InsertColumn(5, _T("起始日期"), LVCFMT_LEFT, 100); // 起始日期
	m_listCtrl.InsertColumn(6, _T("到期日期"), LVCFMT_LEFT, 100); // 到期日期
	m_listCtrl.InsertColumn(7, _T("合同状态"), LVCFMT_LEFT, 100); // 合同状态
}

void CContractManagementSystemDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	contractInfo Info;
	if (Info.DoModal() == IDOK)
	{

		std::string query = "INSERT INTO contracts (contract_name, contract_data, client_name, contract_amount, start_date, end_date, status) VALUES ('" +
			Info.m_name + "', '" + Info.m_date + "', '" + Info.m_client_name + "', '" +
			Info.m_amount + "', '" + Info.m_start_date + "', '" + Info.m_end_date + "', '" +
			Info.m_status_result + "')";

		if (SQL.Query(query)) {
			AfxMessageBox(_T("添加成功"));
			LoadData();
			ShowData();
		}
		else {
			SQL.ErrorIntoMySQL();
			SQL.ShowErrorInto();
		}
	}
}


void CContractManagementSystemDlg::OnBnClickedButtonDelete()
{
	std::vector<int> selectedContractIDs;

	int nCount = m_listCtrl.GetSelectedCount();

	if (nCount == 0)
	{
		AfxMessageBox(_T("没有选中任何合同"));
		return;
	}

	// 遍历所有选中的项
	for (int nItem = 0; nItem < m_listCtrl.GetItemCount(); ++nItem)
	{
		if (m_listCtrl.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
		{
			CString contractIDStr = m_listCtrl.GetItemText(nItem, 0);

			int contractID = _ttoi(contractIDStr); 
			selectedContractIDs.push_back(contractID);
		}
	}

	int response = AfxMessageBox(_T("确定删除选中的合同吗？"), MB_YESNO | MB_ICONQUESTION);

	if (response == IDYES)
	{
		// 遍历所有选中的合同 ID
		for (int i = 0; i < selectedContractIDs.size(); ++i)
		{
			std::string query = "DELETE FROM contracts WHERE contract_id = " + std::to_string(selectedContractIDs[i]);
			if (SQL.Query(query))
			{
				AfxMessageBox(_T("合同删除成功"));
				LoadData();
				ShowData();
			}
			else
			{
				AfxMessageBox(_T("删除合同失败"));
			}
		}
	}
}


void CContractManagementSystemDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	contractInfo Info;
	// 存储选中的合同ID
	std::vector<int> selectedContractIDs;

	// 获取选中的行数
	int nCount = m_listCtrl.GetSelectedCount();

	// 如果没有选中任何项
	if (nCount == 0)
	{
		AfxMessageBox(_T("没有选中任何合同"));
		return;
	}
	//如何选中的项超过一个
	if (nCount > 1)
	{
		AfxMessageBox(_T("修改合同仅支持单选"));
		return;
	}

	int nIndex = m_listCtrl.GetSelectionMark();   //获取选中行的行号
	Info.m_name = m_listCtrl.GetItemText(nIndex, 1);          
	Info.m_date = m_listCtrl.GetItemText(nIndex, 2);          
	Info.m_client_name = m_listCtrl.GetItemText(nIndex, 3);  
	Info.m_amount = m_listCtrl.GetItemText(nIndex, 4);        
	Info.m_start_date = m_listCtrl.GetItemText(nIndex, 5);    
	Info.m_end_date = m_listCtrl.GetItemText(nIndex, 6);     
	Info.m_status_result = m_listCtrl.GetItemText(nIndex, 7); 

	if (Info.DoModal() == IDOK)
	{
		// 获取修改后的信息
		CString updatedName = Info.m_name;
		CString updatedDate = Info.m_date;
		CString updatedClientName = Info.m_client_name;
		CString updatedAmount = Info.m_amount;
		CString updatedStartDate = Info.m_start_date;
		CString updatedEndDate = Info.m_end_date;
		CString updatedStatus = Info.m_status_result;

		// 构建 SQL 更新语句
		CString contractIDStr = m_listCtrl.GetItemText(nIndex, 0);  // 获取 ID

		std::string query = "UPDATE contracts SET contract_name = '" + std::string(CT2A(updatedName)) + "', " +
			"contract_data = '" + std::string(CT2A(updatedDate)) + "', " +
			"client_name = '" + std::string(CT2A(updatedClientName)) + "', " +
			"contract_amount = '" + std::string(CT2A(updatedAmount)) + "', " +
			"start_date = '" + std::string(CT2A(updatedStartDate)) + "', " +
			"end_date = '" + std::string(CT2A(updatedEndDate)) + "', " +
			"status = '" + std::string(CT2A(updatedStatus)) + "' " +
			"WHERE contract_id = " + std::string(CT2A(contractIDStr));

		// 执行 SQL 更新操作
		if (SQL.Query(query)) {
			AfxMessageBox(_T("合同修改成功"));
			LoadData();  // 重新加载数据
			ShowData();  // 刷新界面显示
		}
		else {
			SQL.ErrorIntoMySQL();
			SQL.ShowErrorInto();
			AfxMessageBox(_T("合同修改失败"));
		}
	}

}


void CContractManagementSystemDlg::OnBnClickedButtonSearch()
{
	SearchDlg search;
	if (search.DoModal() == IDOK)
	{
		CString searchOption = search.m_search_combobox_result;
		CString searchKeyword = search.m_search_edit;

		AllStr.clear();

		CString strsql;

		if (searchKeyword.IsEmpty()) {
			strsql = "SELECT * FROM contracts";
		}
		else {
			if (searchOption == _T("合同ID")) {
				strsql.Format(_T("SELECT * FROM contracts WHERE contract_id LIKE '%%%s%%'"), searchKeyword);
			}
			else if (searchOption == _T("合同名称")) {
				strsql.Format(_T("SELECT * FROM contracts WHERE contract_name LIKE '%%%s%%'"), searchKeyword);
			}
			else if (searchOption == _T("客户名称")) {
				strsql.Format(_T("SELECT * FROM contracts WHERE client_name LIKE '%%%s%%'"), searchKeyword);
			}
			else if (searchOption == _T("合同金额")) {
				strsql.Format(_T("SELECT * FROM contracts WHERE contract_amount LIKE '%%%s%%'"), searchKeyword);
			}
			else {
				AfxMessageBox(_T("无效的搜索选项"));
				return;
			}
		}

		int row = SQL.Select(strsql.GetBuffer(), AllStr);

		if (row > 0) {
			ShowData();
		}
		else {
			AfxMessageBox(_T("没有查询到数据"));
		}
	}
}


void CContractManagementSystemDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	SQL.Close();
	EndDialog(IDCANCEL);
}


void CContractManagementSystemDlg::OnBnClickedButtonRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	LoadData();
	ShowData();
}
