
// SethcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sethc.h"
#include "SethcDlg.h"
#include "SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSethcDlg �Ի���

const static int g_nMaxCount = 3;


CSethcDlg::CSethcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSethcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurCount = 0;
}

void CSethcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSethcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSethcDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSethcDlg ��Ϣ�������

BOOL CSethcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSethcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSethcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSethcDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strInputPwd = _T("");  //�û����������
	GetDlgItemText(IDC_EDIT_PWD, strInputPwd);
	if (strInputPwd.IsEmpty())  //����Ϊ��
	{
		MessageBox(_T("Please Enter the Password!"), _T("Error"), MB_ICONWARNING);
		return;
	}
	TCHAR szPassWord[MAX_PATH] = _T("AAAAAAAAAAAAAAAA");
	if (0 == wcscmp(szPassWord, strInputPwd))
	{
		OnOK();
		CSystemDlg systemDlg;
		systemDlg.DoModal();
	}
	else
	{
		m_nCurCount++;
		CString strMsg = _T("");
		strMsg.Format(_T("Password Error, you have %d chances!"), g_nMaxCount - m_nCurCount);
		MessageBox(strMsg, _T("Error"), MB_ICONWARNING);
		SetDlgItemText(IDC_EDIT_PWD, _T(""));
		if (m_nCurCount >= g_nMaxCount)  //��������Ĵ������
		{
			OnOK();
		}
	}
}
