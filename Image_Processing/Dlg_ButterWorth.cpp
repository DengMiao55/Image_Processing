// Dlg_ButterWorth.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_ButterWorth.h"
#include "afxdialogex.h"


// Dlg_ButterWorth 对话框

IMPLEMENT_DYNAMIC(Dlg_ButterWorth, CDialogEx)

Dlg_ButterWorth::Dlg_ButterWorth(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ButterWorthFilter, pParent),D(50),N(2)
{

	EnableAutomation();

}

Dlg_ButterWorth::~Dlg_ButterWorth()
{
}

void Dlg_ButterWorth::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void Dlg_ButterWorth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ButterWorth_D, D);
	DDX_Text(pDX, IDC_EDIT_ButterWorth_N, N);
}


BEGIN_MESSAGE_MAP(Dlg_ButterWorth, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg_ButterWorth::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Dlg_ButterWorth, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDlg_ButterWorth 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {E7CC148C-101A-4310-823E-7E6AA37C3B04}
static const IID IID_IDlg_ButterWorth =
{ 0xE7CC148C, 0x101A, 0x4310, { 0x82, 0x3E, 0x7E, 0x6A, 0xA3, 0x7C, 0x3B, 0x4 } };

BEGIN_INTERFACE_MAP(Dlg_ButterWorth, CDialogEx)
	INTERFACE_PART(Dlg_ButterWorth, IID_IDlg_ButterWorth, Dispatch)
END_INTERFACE_MAP()


// Dlg_ButterWorth 消息处理程序


void Dlg_ButterWorth::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"是否变为高通");
	Butter_highPass = 1;
}
