// Dlg_MedianFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_MedianFilter.h"
#include "afxdialogex.h"


// Dlg_MedianFilter �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDlg_MedianFilter ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {B4D5E3CA-B1A6-4AA5-BC6C-DAAE2F48CA8A}
static const IID IID_IDlg_MedianFilter =
{ 0xB4D5E3CA, 0xB1A6, 0x4AA5, { 0xBC, 0x6C, 0xDA, 0xAE, 0x2F, 0x48, 0xCA, 0x8A } };

BEGIN_INTERFACE_MAP(Dlg_MedianFilter, CDialogEx)
	INTERFACE_PART(Dlg_MedianFilter, IID_IDlg_MedianFilter, Dispatch)
END_INTERFACE_MAP()


// Dlg_MedianFilter ��Ϣ�������
