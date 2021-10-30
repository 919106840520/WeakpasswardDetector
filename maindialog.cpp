// maindialog.cpp: 实现文件
//

#include "pch.h"
#include "MFCdemo3.h"
#include "afxinet.h"
#include "maindialog.h"
#include "afxdialogex.h"
#include "resource.h"
#include <vector>

// maindialog 对话框

IMPLEMENT_DYNAMIC(maindialog, CDialogEx)

maindialog::maindialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
{

}

maindialog::~maindialog()
{
}

void maindialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_user, user);
    DDX_Control(pDX, IDC_pwd, pwd);
    DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
    DDX_Control(pDX, IDC_port, port);
    DDX_Control(pDX, IDC_LIST1, m_lst);
}

// maindialog 消息处理程序

BEGIN_MESSAGE_MAP(maindialog, CDialogEx)
	ON_BN_CLICKED(IDC_connect, &maindialog::OnBnClickedconnect)
	ON_BN_CLICKED(IDCANCEL, &maindialog::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_file, &maindialog::OnBnClickedfile)
END_MESSAGE_MAP()


BOOL maindialog::ConnectFTP()
{
    BYTE nFild[4];
    CString strport;
    port.GetWindowTextW(strport);
    UpdateData();
    ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
    CString sip;
    sip.Format(_T("%d.%d.%d.%d"), nFild[0], nFild[1], nFild[2], nFild[3]);
    if (sip.IsEmpty())
    {
        AfxMessageBox(_T("IP地址为空！"));
        return false;
    }
    if (strport.IsEmpty())
    {
        AfxMessageBox(_T("端口号为空！"));
        return false;
    }
    //建立一个Internet会话
    pInternetSession = new CInternetSession();
    
    CString filename = _T("C:\\Users\\19119\\Desktop");
    CString content;
    CStdioFile csFile;
    CFileException cfException;
    if (csFile.Open(filename, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate, &cfException))
    {
        csFile.ReadString(content);
        AfxMessageBox(content);
    }
    else
    {
        TCHAR szErr[1024];
        cfException.GetErrorMessage(szErr, 1024);
        AfxMessageBox(szErr);
    }
    TRY
    {
        //利用Internet会话对象pInternetSession打开一个FTP连接
        pFtpConnection = pInternetSession->GetFtpConnection(sip, _T("anonymous"), _T(""), _ttoi(strport));
    }
    CATCH(CInternetException, pEx)
    {
        TCHAR szErr[1024];
        pEx->GetErrorMessage(szErr, 1024);
        AfxMessageBox(szErr);
        pEx->Delete();
        return false;
    }
    END_CATCH

    return true;
}


void maindialog::OnBnClickedconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	user.GetWindowTextW(str);
	pwd.SetWindowTextW(str);

    if(this->ConnectFTP())//连接FTP服务器
	this->UpdateDir();//显示服务器上的目录和文件夹列表

	/*ServerIP.EnableWindow(FALSE);
	m_port.EnableWindow(FALSE);
	m_connect.EnableWindow(FALSE);
	m_disconnect.EnableWindow(TRUE);
	m_enterdir.EnableWindow(TRUE);
	m_upload.EnableWindow(TRUE);
	m_download.EnableWindow(TRUE);
	m_delete.EnableWindow(TRUE);
	m_noname.EnableWindow(FALSE);
	m_exit.EnableWindow(FALSE);*/
}
void maindialog::UpdateDir() {
    m_lst.ResetContent();
    //读写服务器中的数据，需要创建一个CFtpFileFind的实例
    CFtpFileFind ftpfind(pFtpConnection);
    //找到第一个文件或者文件夹，通过CFtpFileFind::FindFile实现
    BOOL bfind = ftpfind.FindFile(NULL);
    while (bfind)
    {
        bfind = ftpfind.FindNextFile();
        CString strpath;
        if (!ftpfind.IsDirectory())//判断是目录还是文件夹
        {
            strpath = ftpfind.GetFileName();//是文件则读取文件名
            m_lst.AddString(strpath);
        }
        else {
            strpath = ftpfind.GetFilePath();//如果是文件夹则获取相对路径
            m_lst.AddString(strpath);
        }
    }
}

void maindialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	delete this->GetParent();
}


BOOL maindialog::ConnctFTP_from_txt(char* user_name,char* passward)
{
    BYTE nFild[4];
    CString strport;
    port.GetWindowTextW(strport);
    UpdateData();
    ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
    CString sip;
    sip.Format(_T("%d.%d.%d.%d"), nFild[0], nFild[1], nFild[2], nFild[3]);
    if (sip.IsEmpty())
    {
        AfxMessageBox(_T("IP地址为空！"));
        return false;
    }
    if (strport.IsEmpty())
    {
        AfxMessageBox(_T("端口号为空！"));
        return false;
    }
    //建立一个Internet会话
    pInternetSession = new CInternetSession();
    TRY
    {
        //利用Internet会话对象pInternetSession打开一个FTP连接
        pFtpConnection = pInternetSession->GetFtpConnection(sip, CString(user_name), CString(passward), _ttoi(strport));
    }
        CATCH(CInternetException, pEx)
    {
        TCHAR szErr[1024];
        pEx->GetErrorMessage(szErr, 1024);
        AfxMessageBox(szErr);
        pEx->Delete();
        return false;
    }
    END_CATCH

        return true;
}



void maindialog::OnBnClickedfile()
{
    // TODO: 在此添加控件通知处理程序代码
    CFile file(_T("ini.txt"), CFile::modeRead);
    int len = file.GetLength();
    char* data = NULL;
    data = new char[len + 1];
    memset(data, 0, len + 1);
    file.Read(data, len);
    int line = 0;
    for (int i = 0;i < len;i++)
    {
        //num用户读字符
        int num = 0;
        //读用户名
        while (data[i])
        {
            //空格前面是用户，后面是密码
            if (data[i] == ' ')
            {
                //设置尾0
                user_from_txt[line][num] = '\0';
                break;
            }
            else
            {
                user_from_txt[line][num++] = data[i];
                i++;
            }
        }
        i++;
        num = 0;
        //读密码
        while (data[i])
        {
            //遇到换行符结束
            if (data[i] == '\n')
            {
                //设置尾0,行数+1
                pwd_from_txt[line++][num] = '\0';
                break;
            }
            else
            {
                pwd_from_txt[line][num++] = data[i];
                i++;
            }
        }
        //如果文件结束没有换行,补上
        if (data[i] != '\n') pwd_from_txt[line++][num] = '\0';
    }
    //debug
    /*
    for (int i = 0; i < line;i++)
    {
        MessageBox(CString(user_from_txt[i]) + _T(" ") + CString(pwd_from_txt[i]) + _T("\n"));
    }
    */
    for (int i = 0;i < line;i++)
    {
        if(ConnctFTP_from_txt(user_from_txt[i],pwd_from_txt[i]))
            MessageBox(CString("Succeed with user:\'") + CString(user_from_txt[i]) + CString("\' and pwd:\'") + CString(pwd_from_txt[i]) + CString("\'\n"));
    }
    
}
