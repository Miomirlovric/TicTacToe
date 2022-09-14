
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
	ON_BN_CLICKED(IDC_BUTTON1, &CTicTacToeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTicTacToeDlg::OnBnClickedButton2)
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


	s.LoadString(IDS_STRING102);
	b.LoadString(IDS_STRING103);
	c.LoadString(IDS_STRING104);


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
	if (nextPlayer == 1) {
		SetXOinGrid(point, 1);
	}
	nextPlayer = 2;
	this->Invalidate();
	if (CheckForWinner() == 1) {		
		MessageBox(s,c);
		NewGame();
	}
}


void CTicTacToeDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (nextPlayer == 2) {
		SetXOinGrid(point, 2);
	}
	nextPlayer = 1;
	this->Invalidate();
	if (CheckForWinner() == 2) {
		MessageBox(b,c);
		NewGame();
	}
}


void CTicTacToeDlg::DrawBoard(CDC* pDC)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	int a = 100;
	for(int i=0;i<3;i++){
		pDC->MoveTo(10+a, 10);		
		pDC->LineTo(10+a, 410);
		pDC->MoveTo(10, 10+a);
		pDC->LineTo(410, 10+a);
		a += 100;
	}
}


void CTicTacToeDlg::SetXOinGrid(CPoint point, int value)
{
	for (int i = 0; i < 16; i++) {
		if (MySquares[i].left<point.x && 
			MySquares[i].right>point.x && 
			MySquares[i].top<point.y && 
			MySquares[i].bottom>point.y && position[i] == 0) {
			position[i] = value;
		}
	}
}


void CTicTacToeDlg::DrawXO(CDC* pDC)
{
	for (int i = 0; i < 16; i++) {
		if (position[i] == 2) {
			CRect rect = MySquares[i];
			rect.DeflateRect(10, 10);
			pDC->Ellipse(rect);
		}
		if (position[i] == 1) {
			CRect rect = MySquares[i];
			rect.DeflateRect(10, 10);
			pDC->MoveTo(rect.left, rect.top);
			pDC->LineTo(rect.right, rect.bottom);
			pDC->MoveTo(rect.right, rect.top);
			pDC->LineTo(rect.left, rect.bottom);
		}
	}
}

int CTicTacToeDlg::CheckForWinner()
{
	static int pattern[24][3] = {
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		5, 6, 7,
		8, 9, 10,
		9, 10, 11,
		12, 13, 14,
		13, 14, 15,
		0, 4, 8,
		4,8,12,
		1,5,9,
		5,9,13,
		2,6,10,
		6,10,14,
		3,7,11,
		7,11,15,
		0,5,10,
		5,10,15,
		3,6,9,
		6,9,12,
		4,9,14,
		8,5,2,
		13,10,7,
		11,6,1
	};
	for (int i = 0; i < 24; i++)
	{
		if ((position[pattern[i][0]] == 1) &&
			(position[pattern[i][1]] == 1) &&
			(position[pattern[i][2]] == 1))
			return 1;
		if ((position[pattern[i][0]] == 2) &&
			(position[pattern[i][1]] == 2) &&
			(position[pattern[i][2]] == 2))
			return 2;
	}
	return 0;
}


void CTicTacToeDlg::NewGame()
{
	::ZeroMemory(position, 16 * sizeof(int));
	this->Invalidate();
	nextPlayer = 1;
}


void CTicTacToeDlg::OnBnClickedButton1()
{
	NewGame();	
}


void CTicTacToeDlg::OnBnClickedButton2()
{
	PostMessage(WM_CLOSE);
}
