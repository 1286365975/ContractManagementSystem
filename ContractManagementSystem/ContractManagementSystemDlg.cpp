#include "framework.h"
#include "ContractManagementSystem.h"
#include "ContractManagementSystemDlg.h"
#include "afxdialogex.h"
#include "addContracts.h"

// 确保 HMySQL.h 只被包含一次
#include "HMySQL.h"


HMySQL SQL; // 确保在这个文件中进行实例化



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	ON_BN_CLICKED(IDC_Open, &CContractManagementSystemDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &CContractManagementSystemDlg::OnBnClickedButton2)
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

	//初始化列表和Combobox
	InitListCtrl();
	
	// 数据库连接与数据加载操作
	if (ConnectDB()) {
		LoadData();   // 加载数据
		ShowData();   // 显示数据
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

void CContractManagementSystemDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CContractManagementSystemDlg::OnBnClickedButton2()
{
	addContracts add;
	add.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

//void CContractManagementSystemDlg::ShowData()
//{
//	m_listCtrl.DeleteAllItems();
//	for (int i = 0; i < AllStr.size(); i++)//AllStr[i]
//	{
//		for (int j = 0; j < AllStr[i].size(); j++)
//		{
//			if (j == 0)
//				m_listCtrl.InsertItem(i, AllStr[i][j].c_str());
//			else
//				m_listCtrl.SetItemText(i, j, AllStr[i][j].c_str());
//		}
//	}
	//输出统计结果 计数 
	/*CString strt;
	strt.Format("查询结果%d条", AllStr.size());*/
	//GetDlgItem(IDC_TEXT)->SetWindowText(strt);
//}

//void CContractManagementSystemDlg::LoadData()
//{
//	AllStr.clear();  // 清空之前的数据
//	CString strsql = "SELECT * FROM contracts";  // SQL 查询语句
//
//	// 执行查询并将结果存入 AllStr
//	int row = SQL.Select(strsql.GetBuffer(), AllStr);
//	if (row <= 0) {
//		AfxMessageBox("没有查询到数据");
//	}
//}

void CContractManagementSystemDlg::ShowData()
{
	m_listCtrl.DeleteAllItems();  // 清空列表控件

	// 如果 AllStr 为空，则显示提示
	if (AllStr.empty()) {
		AfxMessageBox("没有数据可显示");
		return;
	}

	// 输出 AllStr 内容进行检查
	CString showMsg;
	showMsg.Format("准备显示的数据: %d 条\n", AllStr.size());
	for (int i = 0; i < AllStr.size(); i++) {
		showMsg.AppendFormat("行 %d: ", i + 1);
		for (int j = 0; j < AllStr[i].size(); j++) {
			showMsg.AppendFormat("%s ", AllStr[i][j].c_str());
		}
		showMsg.Append("\n");
	}

	// 插入数据到控件
	for (int i = 0; i < AllStr.size(); i++) {
		for (int j = 0; j < AllStr[i].size(); j++) {
			if (j == 0)
				m_listCtrl.InsertItem(i, AllStr[i][j].c_str());  // 插入第一列数据
			else
				m_listCtrl.SetItemText(i, j, AllStr[i][j].c_str());  // 设置其余列的数据
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
	// 设置列表控件的扩展样式
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 插入8个列
	m_listCtrl.InsertColumn(0, _T("合同ID"), LVCFMT_LEFT, 60); // 合同ID
	m_listCtrl.InsertColumn(1, _T("合同名称"), LVCFMT_LEFT, 120); // 合同名称
	m_listCtrl.InsertColumn(2, _T("签订日期"), LVCFMT_LEFT, 100); // 签订日期
	m_listCtrl.InsertColumn(3, _T("客户名称"), LVCFMT_LEFT, 120); // 客户名称
	m_listCtrl.InsertColumn(4, _T("合同金额"), LVCFMT_LEFT, 100); // 合同金额
	m_listCtrl.InsertColumn(5, _T("起始日期"), LVCFMT_LEFT, 100); // 起始日期
	m_listCtrl.InsertColumn(6, _T("到期日期"), LVCFMT_LEFT, 100); // 到期日期
	m_listCtrl.InsertColumn(7, _T("合同状态"), LVCFMT_LEFT, 100); // 合同状态
}
