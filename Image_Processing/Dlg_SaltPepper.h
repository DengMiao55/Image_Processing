#pragma once


// Dlg_SaltPepper �Ի���

class Dlg_SaltPepper : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_SaltPepper)

public:
	Dlg_SaltPepper(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_SaltPepper();
	float salt, pepper;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SaltPepper };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
