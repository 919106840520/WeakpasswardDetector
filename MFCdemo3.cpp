
// MFCdemo3.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCdemo3.h"
#include "MainFrm.h"
#include "MFCdemo3Doc.h"
#include "MFCdemo3View.h"
#include "maindialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

maindialog* maind = new maindialog();
// CMFCdemo3App

BEGIN_MESSAGE_MAP(CMFCdemo3App, CWinApp)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMFCdemo3App 构造

CMFCdemo3App::CMFCdemo3App() noexcept
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCdemo3.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CMFCdemo3App 对象

CMFCdemo3App theApp;


// CMFCdemo3App 初始化

BOOL CMFCdemo3App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	
	maind = new maindialog();
	maind->DoModal();

	return TRUE;
}

int CMFCdemo3App::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CMFCdemo3App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

void maindialog::Thread_fun(int num)
{
	for (int i = 0;i < maind->plen;i++)
	{
		if (maind->ConnctFTP_from_txt(maind->user_from_txt[i], maind->pwd_from_txt[i], maind->ip_from_txt[num], maind->port_from_txt[num]))
		{
			maind->m_lst.AddString(CString("Succeed with user:\'") + CString(maind->user_from_txt[i]) + CString("\'") + CString("pwd:\'") + CString(maind->pwd_from_txt[i]) + CString("\'\n"));
			maind->Stock(maind->user_from_txt[i], maind->pwd_from_txt[i], maind->ip_from_txt[num], maind->port_from_txt[num]);
		}
	}
}

//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}


// CMFCdemo3App 消息处理程序



