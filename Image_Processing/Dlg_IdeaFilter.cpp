// Dlg_IdeaFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_IdeaFilter.h"
#include "afxdialogex.h"


// Dlg_IdeaFilter �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDlg_IdeaFilter ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {AF3F0087-641B-406C-AF8A-E7FA53570A4C}
static const IID IID_IDlg_IdeaFilter =
{ 0xAF3F0087, 0x641B, 0x406C, { 0xAF, 0x8A, 0xE7, 0xFA, 0x53, 0x57, 0xA, 0x4C } };

BEGIN_INTERFACE_MAP(Dlg_IdeaFilter, CDialogEx)
	INTERFACE_PART(Dlg_IdeaFilter, IID_IDlg_IdeaFilter, Dispatch)
END_INTERFACE_MAP()


// Dlg_IdeaFilter ��Ϣ�������


void Dlg_IdeaFilter::OnEnChangeEdit1()
{
}
void Dlg_IdeaFilter::OnBtnClicked()
{
	MessageBox(L"�Ƿ����Ϊ��ͨ");
	Idel_highPass = 1;

	//MessageBox(L"�����");
}
