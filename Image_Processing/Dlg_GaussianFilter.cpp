// Dlg_GaussianFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_GaussianFilter.h"
#include "afxdialogex.h"


// Dlg_GaussianFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_GaussianFilter, CDialogEx)

Dlg_GaussianFilter::Dlg_GaussianFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GaussianFilter, pParent)
{

	EnableAutomation();

}

Dlg_GaussianFilter::~Dlg_GaussianFilter()
{
}

void Dlg_GaussianFilter::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void Dlg_GaussianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_Gaussian_D, D);
}


BEGIN_MESSAGE_MAP(Dlg_GaussianFilter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg_GaussianFilter::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Dlg_GaussianFilter, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDlg_GaussianFilter 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {3251A595-F336-4219-A084-6BD02DC2308E}
static const IID IID_IDlg_GaussianFilter =
{ 0x3251A595, 0xF336, 0x4219, { 0xA0, 0x84, 0x6B, 0xD0, 0x2D, 0xC2, 0x30, 0x8E } };

BEGIN_INTERFACE_MAP(Dlg_GaussianFilter, CDialogEx)
	INTERFACE_PART(Dlg_GaussianFilter, IID_IDlg_GaussianFilter, Dispatch)
END_INTERFACE_MAP()


// Dlg_GaussianFilter 消息处理程序


void Dlg_GaussianFilter::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"是否变为高通");
	Gaussian_highPass = 1;
}
