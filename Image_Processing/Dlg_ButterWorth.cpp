// Dlg_ButterWorth.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_ButterWorth.h"
#include "afxdialogex.h"


// Dlg_ButterWorth �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDlg_ButterWorth ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {E7CC148C-101A-4310-823E-7E6AA37C3B04}
static const IID IID_IDlg_ButterWorth =
{ 0xE7CC148C, 0x101A, 0x4310, { 0x82, 0x3E, 0x7E, 0x6A, 0xA3, 0x7C, 0x3B, 0x4 } };

BEGIN_INTERFACE_MAP(Dlg_ButterWorth, CDialogEx)
	INTERFACE_PART(Dlg_ButterWorth, IID_IDlg_ButterWorth, Dispatch)
END_INTERFACE_MAP()


// Dlg_ButterWorth ��Ϣ�������


void Dlg_ButterWorth::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"�Ƿ��Ϊ��ͨ");
	Butter_highPass = 1;
}
