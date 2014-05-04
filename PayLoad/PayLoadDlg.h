
// PayLoadDlg.h : ͷ�ļ�
//

#pragma once


// CPayLoadDlg �Ի���
class CPayLoadDlg : public CDialog
{
// ����
public:
	CPayLoadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PAYLOAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnEnChangeEditPassword();
	CString m_strPwd;  //����
	bool ReleaseSethc();  //�ͷ�Sethc.exe��Դ
	CString GetCurDir() const;
	bool FindMem(IN TCHAR* pMem, IN const int nLen, IN TCHAR* pFrom, IN TCHAR* pTo);
	afx_msg void OnBnClickedBtnInstall();
	void StopServer();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
