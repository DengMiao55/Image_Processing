#pragma once


// Dlg_ButterWorth �Ի���

class Dlg_ButterWorth : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_ButterWorth)

public:
	Dlg_ButterWorth(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_ButterWorth();
	double D;
	int N;
	int Butter_highPass;

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ButterWorthFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
