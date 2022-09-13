// TicTacToeDlg.h : header file
//

#pragma once


// CTicTacToeDlg dialog
class CTicTacToeDlg : public CDialogEx
{
	// Construction
public:
	CTicTacToeDlg(CWnd* pParent = nullptr);	// standard constructor
	static const CRect MySquares[16];
	int position[16];
	int m_nNextChar;
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TICTACTOE_DIALOG };
#endif

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	void DrawBoard(CDC* pDC);
public:
	void SetXOinGrid(CPoint point, int value);
	void DrawXO(CDC* pDC);
};