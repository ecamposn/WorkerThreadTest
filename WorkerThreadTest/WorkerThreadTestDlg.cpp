
// WorkerThreadTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorkerThreadTest.h"
#include "WorkerThreadTestDlg.h"
#include "afxdialogex.h"
#include "CounterThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWorkerThreadTestDlg dialog



CWorkerThreadTestDlg::CWorkerThreadTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkerThreadTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWorkerThreadTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BAR, m_progressBar);
	DDX_Control(pDX, IDC_STATUS, m_status);
}

BEGIN_MESSAGE_MAP(CWorkerThreadTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_THREAD, &CWorkerThreadTestDlg::OnBnClickedStartThread)
	ON_MESSAGE(WM_USER_THREAD_FINISHED,CWorkerThreadTestDlg::ThreadDone)
	ON_BN_CLICKED(IDCANCEL, &CWorkerThreadTestDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START_THREAD2, &CWorkerThreadTestDlg::OnBnClickedStartThread2)
	ON_BN_CLICKED(IDOK, &CWorkerThreadTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_START_THREAD3, &CWorkerThreadTestDlg::OnBnClickedStartThread3)
END_MESSAGE_MAP()


// CWorkerThreadTestDlg message handlers

BOOL CWorkerThreadTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	m_progressBar.SetRange(0,100);
	m_progressBar.SetPos(0);
	GetDlgItem(IDC_PROGRESS_BAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	m_status.SetWindowTextW(_T("Welcome to the thread master!...right"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWorkerThreadTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWorkerThreadTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWorkerThreadTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWorkerThreadTestDlg::OnBnClickedStartThread()
{
	m_progressBar.ShowWindow(SW_SHOW);
	m_progressBar.SetRange(0,100);
	m_progressBar.SetPos(0);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow();
	GetDlgItem(IDC_START_THREAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_START_THREAD2)->EnableWindow(FALSE);

	THREADPARMS* ptp = new THREADPARMS;

	ptp->nMax = 1100;
	ptp->hWnd = m_hWnd;
	ptp->progress = &m_progress;
	m_pThread = AfxBeginThread(ThreadFunc, ptp);
	SetTimer(1,500,NULL);
}

UINT ThreadFunc (LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	int nMax = ptp->nMax;
	HWND hWnd = ptp->hWnd;
	double* progress = ptp->progress;
	delete ptp;
	long maxCount = nMax*nMax*nMax;
	long nCount=0;
	for(long i=0; i<nMax; i++)
		for(long j=0; j<nMax; j++)
			for( long l=0; l<nMax; l++)
			{
				nCount++;
				*progress = (double)nCount/(double)maxCount;
			}
	::PostMessage(hWnd, WM_USER_THREAD_FINISHED,(WPARAM) nCount, 0);
	return 0;
}

LONG CWorkerThreadTestDlg::ThreadDone( WPARAM wParam, LPARAM lParam)
{
	CString s;
	s.Format(_T("Thread finished with %d as a result."),(int) wParam);
	m_status.SetWindowTextW(s);
	m_progressBar.ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_START_THREAD)->EnableWindow();
	GetDlgItem(IDC_START_THREAD2)->EnableWindow();
	KillTimer(1);
	return 0;
}


void CWorkerThreadTestDlg::OnBnClickedCancel()
{
	m_pThread->SuspendThread();
	CString s;
	s.Format(_T("Process interrupted at %d progress. Do you want to interrupt?"),(int)(100.*(m_progress)));
	if (AfxMessageBox(s,MB_ICONEXCLAMATION | MB_YESNO)==IDYES)
	{
		m_pThread->Delete();
		m_pThread = NULL;
		m_progressBar.ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_START_THREAD)->EnableWindow();
		GetDlgItem(IDC_START_THREAD2)->EnableWindow();
		KillTimer(1);
	} else {
		m_pThread->ResumeThread();
	}
}


void CWorkerThreadTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString s;
	m_progressBar.SetPos((int)(m_progress * 100));
	s.Format(_T("Progress is %5.4f."),m_progress);
	m_status.SetWindowTextW(s);
	SetTimer(1,500,NULL);

	CDialogEx::OnTimer(nIDEvent);
}


void CWorkerThreadTestDlg::OnBnClickedStartThread2()
{
	GetDlgItem(IDCANCEL)->EnableWindow();
	GetDlgItem(IDC_START_THREAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_START_THREAD2)->EnableWindow(FALSE);
	m_progressBar.SetRange(0,100);
	m_progressBar.SetPos(0);
	m_progressBar.ShowWindow(SW_SHOW);
	m_progressBar.SetPos(50);
	Sleep(2000);
	const long nMax = 1100;
	long maxCount = nMax*nMax*nMax;
	long nCount=0;
	double progress;
	CString s;
	for(long i=0; i<nMax; i++)
	{
		for(long j=0; j<nMax; j++)
		{
			for( long l=0; l<nMax; l++)
			{
				nCount++;
			}
		}
		progress = (double) nCount / (double) maxCount;
		s.Format(_T("Progress at %4.3f"),progress);
		m_status.SetWindowTextW(s);
		m_progressBar.SetPos((int)(100.*progress));
	}
	s.Format(_T("Process finished with results %d."),nCount);
	m_status.SetWindowTextW(s);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_START_THREAD)->EnableWindow();
	GetDlgItem(IDC_START_THREAD2)->EnableWindow();
	m_progressBar.ShowWindow(SW_HIDE);
}


void CWorkerThreadTestDlg::OnBnClickedOk()
{
	if (AfxMessageBox(_T("Sure you want to quit?"),MB_YESNO)==IDNO)
		return;
	CDialogEx::OnOK();
}


void CWorkerThreadTestDlg::OnBnClickedStartThread3()
{
	CCounterThread* pThread = (CCounterThread*)AfxBeginThread(RUNTIME_CLASS(CCounterThread),0,0,CREATE_SUSPENDED);
	long nMax = 1100;
	long nCount = 0;
	double progress;
	pThread->m_pProgress=&progress;
	long maxCount = nMax * nMax * nMax;
	for(long i=0; i<nMax; i++)
	{
		for(long j=0; j<nMax; j++)
		{
			for( long l=0; l<nMax; l++)
			{
				nCount++;
			}
		}
		progress = (double) nCount / (double) maxCount;
	}
	pThread->PostThreadMessageW(WM_QUIT, 0, 0);
}
