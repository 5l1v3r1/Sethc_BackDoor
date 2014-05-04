#pragma once


// CSystemDlg �Ի���

class CSystemDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemDlg)

public:
	CSystemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSystemDlg();

// �Ի�������
	enum { IDD = IDD_FUNCTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCmd();
	afx_msg void OnBnClickedBtnExplorer();
	afx_msg void OnBnClickedBtnReg();
	afx_msg void OnBnClickedBtnTask();

	void ExecSysCmd(IN const int nCmd); //ִ������
private:
	UINT32 GetSystem32Path(OUT CString& strPath, OUT bool* pbSuccess);  //��ȡSystem32·��
	UINT32 GetWindowsPath(OUT CString& strPath, OUT bool* pbSuccess); //��ȡWindowsĿ¼·��
	CString m_strSystemPath;
	CString m_strWindowsPath;
public:
	afx_msg void OnBnClickedBtnAdd();
	CString m_strUser;
	CString m_strPwd;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnReset();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool AddUser();
};
