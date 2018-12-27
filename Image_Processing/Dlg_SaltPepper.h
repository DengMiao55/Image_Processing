#pragma once


// Dlg_SaltPepper 对话框

class Dlg_SaltPepper : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_SaltPepper)

public:
	Dlg_SaltPepper(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_SaltPepper();
	float salt, pepper;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SaltPepper };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
