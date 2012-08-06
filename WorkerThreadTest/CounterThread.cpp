// CounterThread.cpp : implementation file
//

#include "stdafx.h"
#include "WorkerThreadTest.h"
#include "CounterThread.h"


// CCounterThread

IMPLEMENT_DYNCREATE(CCounterThread, CWinThread)

CCounterThread::CCounterThread()
{
}

CCounterThread::~CCounterThread()
{
}

BOOL CCounterThread::InitInstance()
{
	m_progressDlg = new CProgressDlg();
	m_progressDlg->m_progress = m_pProgress; 
	m_progressDlg->Create(IDD_PROGRESS_DLG);
	m_progressDlg->ShowWindow(SW_SHOWNORMAL);
	m_progressDlg->UpdateWindow();
	return TRUE;
}

int CCounterThread::ExitInstance()
{
	m_progressDlg->DestroyWindow();
	AfxMessageBox(_T("I'm done."));
	delete m_progressDlg;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCounterThread, CWinThread)
END_MESSAGE_MAP()


