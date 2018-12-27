// Dlg_MedianFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_MedianFilter.h"
#include "afxdialogex.h"


// Dlg_MedianFilter 对话框

IMPLEMENT_DYNAMIC(Dlg_MedianFilter, CDialogEx)

Dlg_MedianFilter::Dlg_MedianFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MedianFilter, pParent),size(3)
{

	EnableAutomation();

}

Dlg_MedianFilter::~Dlg_MedianFilter()
{
}

void Dlg_MedianFilter::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void Dlg_MedianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FilterSize, size);
}


BEGIN_MESSAGE_MAP(Dlg_MedianFilter, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Dlg_MedianFilter, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDlg_MedianFilter 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {B4D5E3CA-B1A6-4AA5-BC6C-DAAE2F48CA8A}
static const IID IID_IDlg_MedianFilter =
{ 0xB4D5E3CA, 0xB1A6, 0x4AA5, { 0xBC, 0x6C, 0xDA, 0xAE, 0x2F, 0x48, 0xCA, 0x8A } };

BEGIN_INTERFACE_MAP(Dlg_MedianFilter, CDialogEx)
	INTERFACE_PART(Dlg_MedianFilter, IID_IDlg_MedianFilter, Dispatch)
END_INTERFACE_MAP()


// Dlg_MedianFilter 消息处理程序
