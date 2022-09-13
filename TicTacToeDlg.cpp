
// TicTacToeDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TicTacToe.h"
#include "TicTacToeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTicTacToeDlg dialog



CTicTacToeDlg::CTicTacToeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TICTACTOE_DIALOG, pParent)
{
	::ZeroMemory(position, 16 * sizeof(int));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTicTacToeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTicTacToeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CTicTacToeDlg message handlers

BOOL CTicTacToeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: Add extra initialization here



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTicTacToeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTicTacToeDlg::OnPaint()
{
	CPaintDC dc(this);
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
		DrawBoard(&dc);
		DrawXO(&dc);
	}


}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTicTacToeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


const CRect CTicTacToeDlg::MySquares[16] = {
	CRect(10, 10,110,110),
	CRect(110, 10,210,110),
	CRect(210, 10,310,110),
	CRect(310,10,410,110),

	CRect(10,110,110,210),
	CRect(110,110,210,210),
	CRect(210,110,310,210),
	CRect(310,110,410,210),

	CRect(10,210,110,310),
	CRect(110,210,210,310),
	CRect(210,210,310,310),
	CRect(310,210,410,310),

	CRect(10,310,110,410),
	CRect(110,310,210,410),
	CRect(210,310,310,410),
	CRect(310,310,410,410)

};

void CTicTacToeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default	
	SetXOinGrid(point, 1);
	this->Invalidate();

}


void CTicTacToeDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default	
	SetXOinGrid(point, 2);
	this->Invalidate();
}


void CTicTacToeDlg::DrawBoard(CDC* pDC)
{
	// TODO: Add your implementation code here.
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	pDC->SelectObject(&pen);

	pDC->MoveTo(110, 10);
	pDC->LineTo(110, 410);
	pDC->MoveTo(210, 10);
	pDC->LineTo(210, 410);
	pDC->MoveTo(310, 10);
	pDC->LineTo(310, 410);

	pDC->MoveTo(10, 110);
	pDC->LineTo(410, 110);
	pDC->MoveTo(10, 210);
	pDC->LineTo(410, 210);
	pDC->MoveTo(10, 310);
	pDC->LineTo(410, 310);
}


void CTicTacToeDlg::SetXOinGrid(CPoint point, int value)
{
	// TODO: Add your implementation code here.
	for (int i = 0; i < 16; i++) {
		if (MySquares[i].left<point.x && MySquares[i].right>point.x && MySquares[i].top<point.y && MySquares[i].bottom>point.y && position[i] == 0) {
			position[i] = value;
			MessageBox(MB_OK);
		}
	}
}


void CTicTacToeDlg::DrawXO(CDC* pDC)
{
	// TODO: Add your implementation code here.
	for (int i = 0; i < 16; i++) {
		if (position[i] == 2) {
			CRect rect = MySquares[i];
			rect.DeflateRect(16, 16);
			pDC->Ellipse(rect);
		}
		if (position[i] == 1) {
			CRect rect = MySquares[i];
			rect.DeflateRect(16, 16);
			pDC->MoveTo(rect.left, rect.top);
			pDC->LineTo(rect.right, rect.bottom);
			pDC->MoveTo(rect.right, rect.top);
			pDC->LineTo(rect.left, rect.bottom);
		}
	}
}