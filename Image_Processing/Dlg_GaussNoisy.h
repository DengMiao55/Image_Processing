#pragma once


// Dlg_GaussNoisy �Ի���

class Dlg_GaussNoisy : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_GaussNoisy)

public:
	Dlg_GaussNoisy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_GaussNoisy();
	//void Dlg_GaussNoisy::PostNcDestroy();
	float z;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GaussNosiy };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
