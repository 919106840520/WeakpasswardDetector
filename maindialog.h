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

	DECLARE_MESSAGE_MAP()
public:
private:
public:
private:
	CEdit user;
	CEdit pwd;
	char user_from_txt[400][100];
	char pwd_from_txt[400][100];
public:
	afx_msg BOOL ConnectFTP();
	void OnBnClickedconnect();
	afx_msg void OnBnClickedCancel();
	BOOL ConnctFTP_from_txt(char* user_name, char* passward);
	CIPAddressCtrl ServerIP;
	CEdit port;
	CInternetSession* pInternetSession;
	CFtpConnection* pFtpConnection;
	afx_msg void UpdateDir();
	CListBox m_lst;
	afx_msg void OnBnClickedfile();
};
