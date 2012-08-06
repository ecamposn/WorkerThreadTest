
// WorkerThreadTestDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define WM_USER_THREAD_FINISHED WM_USER+0x100

UINT ThreadFunc( LPVOID pParam );

typedef struct tagTHREADPARMS {
	int nMax;
	HWND hWnd;
	double* progress;	// A number between 0 and 1 representing progress in the operation
} THREADPARMS;

// CWorkerThreadTestDlg dialog
class CWorkerThreadTestDlg : public CDialogEx
{
// Construction
public:
	CWorkerThreadTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WORKERTHREADTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG ThreadDone( WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_progressBar;
	CStatic m_status;
	CWinThread *m_pThread;
	double m_progress;
	afx_msg void OnBnClickedStartThread();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStartThread2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedStartThread3();
};
