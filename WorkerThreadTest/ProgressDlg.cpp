// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorkerThreadTest.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg dialog

IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BAR, m_progressCtrl);
	DDX_Control(pDX, IDC_STATUS, m_status);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProgressDlg message handlers


BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_progressCtrl.SetRange(0,100);
	m_progressCtrl.SetPos(50);
	UpdateWindow();
	SetTimer(1,0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1)
	{
		CString s;
		s.Format(_T("Progress of %4.3f."),m_progress);
		m_status.SetWindowTextW(s);
		m_progressCtrl.SetPos((int) (*m_progress*100.));
		SetTimer(1,0,0);
	}
	CDialogEx::OnTimer(nIDEvent);
}
