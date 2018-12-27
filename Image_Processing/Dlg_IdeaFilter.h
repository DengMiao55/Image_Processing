#pragma once
#include "afxcmn.h"


// Dlg_IdeaFilter 对话框

class Dlg_IdeaFilter : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_IdeaFilter)

public:
	Dlg_IdeaFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_IdeaFilter();
	double D;
	int Idel_highPass;
	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBtnClicked();
	CTabCtrl m_tab;
};
