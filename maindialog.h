#pragma once


// maindialog 对话框
#include "afxinet.h"
class maindialog : public CDialogEx
{
	DECLARE_DYNAMIC(maindialog)

public:
	maindialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~maindialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HANDLE hThread[20];
	DWORD ThreadID[20];
	DECLARE_MESSAGE_MAP()
public:
private:
public:
	char user_from_txt[400][100];
	char pwd_from_txt[400][100];
	char ip_from_txt[400][100];
	char port_from_txt[400][100];
	int plen;
	int iplen;
private:
	CEdit user;
	CEdit pwd;
	CString pwdfilestr;
	CString iprange;
	
public:
	afx_msg BOOL ConnectFTP();
	static void Thread_fun(int num);
	void OnBnClickedconnect();
	afx_msg void OnBnClickedCancel();
	void Stock(char* user_name, char* passward, char* ip, char* port);
	BOOL ConnctFTP_from_txt(char* user_name, char* passward, char* ip, char* port);
	CIPAddressCtrl ServerIP;
	CEdit port;
	CInternetSession* pInternetSession;
	CFtpConnection* pFtpConnection;
	afx_msg void UpdateDir();
	CListBox m_lst;
	afx_msg void OnBnClickedfile();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CEdit ip_range_show;
	CEdit pwd_show;
};

