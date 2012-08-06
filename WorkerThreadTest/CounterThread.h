#pragma once

#include "ProgressDlg.h"

// CCounterThread

class CCounterThread : public CWinThread
{
	DECLARE_DYNCREATE(CCounterThread)
public:
	CCounterThread();

private:
	virtual ~CCounterThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CProgressDlg* m_progressDlg;
	double* m_pProgress;
};


