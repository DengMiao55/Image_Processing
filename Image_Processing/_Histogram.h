#pragma once


// _Histogram �Ի���

class _Histogram : public CDialog
{
	DECLARE_DYNAMIC(_Histogram)

public:
	_Histogram(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~_Histogram();

 //�Ի�������
	enum { IDD = IDD_Histogram };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int Arry[256];
	afx_msg void OnBnClickedEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
