#pragma once


// Dlg_MedianFilter �Ի���

class Dlg_MedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_MedianFilter)

public:
	Dlg_MedianFilter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_MedianFilter();

	virtual void OnFinalRelease();
	int size;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MedianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
