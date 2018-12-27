// Dlg_GaussNoisy.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_GaussNoisy.h"
#include "afxdialogex.h"


// Dlg_GaussNoisy 对话框

IMPLEMENT_DYNAMIC(Dlg_GaussNoisy, CDialogEx)

Dlg_GaussNoisy::Dlg_GaussNoisy(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GaussNosiy, pParent),z(50)
{

}

Dlg_GaussNoisy::~Dlg_GaussNoisy()
{
}
//
//void Dlg_GaussNoisy::PostNcDestroy()
//{
//	delete this;
//	CDialog::PostNcDestroy();
//}

void Dlg_GaussNoisy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Gauss, z);
}


BEGIN_MESSAGE_MAP(Dlg_GaussNoisy, CDialogEx)
END_MESSAGE_MAP()


// Dlg_GaussNoisy 消息处理程序
