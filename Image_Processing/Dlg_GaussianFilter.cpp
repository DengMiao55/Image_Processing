// Dlg_GaussianFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_GaussianFilter.h"
#include "afxdialogex.h"


// Dlg_GaussianFilter �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDlg_GaussianFilter ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {3251A595-F336-4219-A084-6BD02DC2308E}
static const IID IID_IDlg_GaussianFilter =
{ 0x3251A595, 0xF336, 0x4219, { 0xA0, 0x84, 0x6B, 0xD0, 0x2D, 0xC2, 0x30, 0x8E } };

BEGIN_INTERFACE_MAP(Dlg_GaussianFilter, CDialogEx)
	INTERFACE_PART(Dlg_GaussianFilter, IID_IDlg_GaussianFilter, Dispatch)
END_INTERFACE_MAP()


// Dlg_GaussianFilter ��Ϣ�������


void Dlg_GaussianFilter::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"�Ƿ��Ϊ��ͨ");
	Gaussian_highPass = 1;
}
