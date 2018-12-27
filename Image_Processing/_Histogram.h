#pragma once


// _Histogram 对话框

class _Histogram : public CDialog
{
	DECLARE_DYNAMIC(_Histogram)

public:
	_Histogram(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~_Histogram();

 //对话框数据
	enum { IDD = IDD_Histogram };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Arry[256];
	afx_msg void OnBnClickedEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
