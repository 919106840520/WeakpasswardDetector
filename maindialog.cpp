// maindialog.cpp: 实现文件
//

#include "pch.h"
#include "MFCdemo3.h"
#include "afxinet.h"
#include "maindialog.h"
#include "afxdialogex.h"
#include "resource.h"
#include <vector>

// maindialog 对话框;

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
    DDX_Control(pDX, IDC_EDIT1, ip_range_show);
    DDX_Control(pDX, IDC_EDIT2, pwd_show);
}

// maindialog 消息处理程序

BEGIN_MESSAGE_MAP(maindialog, CDialogEx)
	ON_BN_CLICKED(IDC_connect, &maindialog::OnBnClickedconnect)
	ON_BN_CLICKED(IDCANCEL, &maindialog::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_file, &maindialog::OnBnClickedfile)
    ON_BN_CLICKED(IDC_BUTTON2, &maindialog::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON1, &maindialog::OnBnClickedButton1)
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
    /*
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
    }*/
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

void maindialog::Stock(char* user_name, char* passward, char* ip, char* port)
{
    CString strSum = _T("user:");
    strSum += CString(user_name);
    strSum += CString("  passward:") + CString(passward);
    strSum += CString("  IP:") + CString(ip);
    strSum += CString("  port:") + CString(port);
    strSum += "\r\n";
    AfxMessageBox(strSum);
    // 2 写入文件
    CStdioFile csFile;
    if (!csFile.Open(_T("ftpscan.txt"), CFile::modeCreate | CFile::modeWrite))
    {
        AfxMessageBox(_T("ftpscan.txt \r\n Open failed when write."));
    }
    csFile.SeekToEnd();
    csFile.WriteString(strSum);
    strSum.ReleaseBuffer();
}



BOOL maindialog::ConnctFTP_from_txt(char* user_name,char* passward,char* ip,char * port)
{
    m_lst.AddString( CString("正在扫描:") + CString(ip) + " " + CString(port) + "user:" + user_name + " passward:" + passward);
    CString strport(port);
    //UpdateData();
    CString sip(ip);
    if (sip.IsEmpty())
    {
        m_lst.AddString(_T("IP地址为空！"));
        return false;
    }
    if (strport.IsEmpty())
    {
        m_lst.AddString(_T("端口号为空！"));
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
        m_lst.AddString(szErr);
        pEx->Delete();
        return false;
    }
    END_CATCH

        return true;
}



void maindialog::OnBnClickedfile()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileDialog dlg(TRUE);
    dlg.m_ofn.lpstrTitle = _T("请选择文件");
    if (dlg.DoModal() == IDOK)
    {
        pwdfilestr = dlg.GetPathName();
    }
    pwd_show.SetWindowTextW(pwdfilestr);
}


void maindialog::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    CFile file;
    file.Open(pwdfilestr, CFile::modeRead);

    int len = file.GetLength();
    char* data = NULL;
    data = new char[len + 1];
    memset(data, 0, len + 1);
    file.Read(data, len);
    //AfxMessageBox(CString(data));
    int line1 = 0;
    //读取密码文件
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
                user_from_txt[line1][num] = '\0';
                break;
            }
            else
            {
                user_from_txt[line1][num++] = data[i];
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
                pwd_from_txt[line1++][num] = '\0';
                break;
            }
            else
            {
                pwd_from_txt[line1][num++] = data[i];
                i++;
            }
        }
        //如果文件结束没有换行,补上
        if (data[i] != '\n') pwd_from_txt[line1++][num] = '\0';
    }
    //debug
    /*
    for (int i = 0; i < line;i++)
    {
        MessageBox(CString(user_from_txt[i]) + _T(" ") + CString(pwd_from_txt[i]) + _T("\n"));
    }
    */
    //关闭密码文件
    file.Close();
    delete data;

    //打开iprange文件
    file.Open(iprange, CFile::modeRead);

    len = file.GetLength();
    data = new char[len + 1];
    memset(data, 0, len + 1);
    file.Read(data, len);
    int line2 = 0;
    //读取iprange文件
    for (int i = 0;i < len;i++)
    {
        //num用户读字符
        int num = 0;
        //读ip
        while (data[i])
        {
            //空格前面是ip，后面是端口
            if (data[i] == ' ')
            {
                //设置尾0
                ip_from_txt[line2][num] = '\0';
                break;
            }
            else
            {
                ip_from_txt[line2][num++] = data[i];
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
                port_from_txt[line2++][num] = '\0';
                break;
            }
            else
            {
                port_from_txt[line2][num++] = data[i];
                i++;
            }
        }
        //如果文件结束没有换行,补上
        if (data[i] != '\n') port_from_txt[line2++][num] = '\0';
    }
    //debug
    /*
    for (int i = 0; i < line2;i++)
    {
        MessageBox(CString(ip_from_txt[i]) + _T(" ") + CString(port_from_txt[i]) + _T("\n"));
    }
    */
    plen = line1;
    for (int j = 0;j < line2;j++)
    {
        m_lst.AddString(CString("线程" + j) + CString("创建"));
        hThread[j] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_fun, (void*)j, 0, &ThreadID[j]);
    }
}



void maindialog::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileDialog dlg(TRUE);
    dlg.m_ofn.lpstrTitle = _T("请选择文件");
    if (dlg.DoModal() == IDOK)
    {
        iprange = dlg.GetPathName();
    }
    ip_range_show.SetWindowTextW(iprange);
}
