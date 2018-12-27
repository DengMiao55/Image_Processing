#pragma once


// Dlg_GaussianFilter 对话框

class Dlg_GaussianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_GaussianFilter)

public:
	Dlg_GaussianFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_GaussianFilter();
	double D;
	int Gaussian_highPass;
	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GaussianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
