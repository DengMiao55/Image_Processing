// Dlg_IdeaFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_IdeaFilter.h"
#include "afxdialogex.h"


// Dlg_IdeaFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_IdeaFilter, CDialogEx)

Dlg_IdeaFilter::Dlg_IdeaFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IdelFilter, pParent),D(50)
{

	EnableAutomation();

}

Dlg_IdeaFilter::~Dlg_IdeaFilter()
{
}

void Dlg_IdeaFilter::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void Dlg_IdeaFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_IdelLowPass, D);
}


BEGIN_MESSAGE_MAP(Dlg_IdeaFilter, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_IdelLowPass, &Dlg_IdeaFilter::OnEnChangeEdit1)
	ON_COMMAND(IDC_BUTTON_IsHighPass,&Dlg_IdeaFilter::OnBtnClicked)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Dlg_IdeaFilter, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDlg_IdeaFilter 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {AF3F0087-641B-406C-AF8A-E7FA53570A4C}
static const IID IID_IDlg_IdeaFilter =
{ 0xAF3F0087, 0x641B, 0x406C, { 0xAF, 0x8A, 0xE7, 0xFA, 0x53, 0x57, 0xA, 0x4C } };

BEGIN_INTERFACE_MAP(Dlg_IdeaFilter, CDialogEx)
	INTERFACE_PART(Dlg_IdeaFilter, IID_IDlg_IdeaFilter, Dispatch)
END_INTERFACE_MAP()


// Dlg_IdeaFilter 消息处理程序


void Dlg_IdeaFilter::OnEnChangeEdit1()
{
}
void Dlg_IdeaFilter::OnBtnClicked()
{
	MessageBox(L"是否想变为高通");
	Idel_highPass = 1;

	//MessageBox(L"点饿了");
}
