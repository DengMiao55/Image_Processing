// _Histogram.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "_Histogram.h"
#include "afxdialogex.h"


// _Histogram 对话框

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


// _Histogram 消息处理程序


void _Histogram::OnBnClickedEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	CenterWindow();
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));  //红色画笔	
	CClientDC dc(this);
	CPen* pOldPen = dc.SelectObject(&pen);  //创建画笔对象
	dc.MoveTo(0, 0);  //绘制一个坐标轴
	dc.LineTo(0, 256);  //Y轴
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
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void _Histogram::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
