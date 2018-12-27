#pragma once


// Dlg_GaussNoisy 对话框

class Dlg_GaussNoisy : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_GaussNoisy)

public:
	Dlg_GaussNoisy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_GaussNoisy();
	//void Dlg_GaussNoisy::PostNcDestroy();
	float z;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GaussNosiy };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
