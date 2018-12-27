#pragma once


// Dlg_MedianFilter 对话框

class Dlg_MedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_MedianFilter)

public:
	Dlg_MedianFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_MedianFilter();

	virtual void OnFinalRelease();
	int size;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MedianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
