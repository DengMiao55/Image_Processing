// _Histogram.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "_Histogram.h"
#include "afxdialogex.h"


// _Histogram �Ի���

IMPLEMENT_DYNAMIC(_Histogram, CDialog)

_Histogram::_Histogram(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Histogram, pParent)
{

}

_Histogram::~_Histogram()
{
}

void _Histogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(_Histogram, CDialog)
	ON_BN_CLICKED(IDC_EDIT1, &_Histogram::OnBnClickedEdit1)
	ON_BN_CLICKED(IDOK, &_Histogram::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &_Histogram::OnBnClickedButton1)
END_MESSAGE_MAP()


// _Histogram ��Ϣ�������


void _Histogram::OnBnClickedEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CenterWindow();
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));  //��ɫ����	
	CClientDC dc(this);
	CPen* pOldPen = dc.SelectObject(&pen);  //�������ʶ���
	dc.MoveTo(0, 0);  //����һ��������
	dc.LineTo(0, 256);  //Y��
	dc.MoveTo(0, 256);
	dc.LineTo(256, 256);

	for (int i = 0; i<256; i++)
	{
		dc.MoveTo(i, 256);
		dc.LineTo(i, (256 - Arry[i] / 100));
	}
	
	dc.SelectObject(pOldPen);
	
}


void _Histogram::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void _Histogram::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
