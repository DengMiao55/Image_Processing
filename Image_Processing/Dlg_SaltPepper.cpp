// Dlg_SaltPepper.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Dlg_SaltPepper.h"
#include "afxdialogex.h"


// Dlg_SaltPepper �Ի���

IMPLEMENT_DYNAMIC(Dlg_SaltPepper, CDialogEx)

Dlg_SaltPepper::Dlg_SaltPepper(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SaltPepper, pParent),salt(0.2f),pepper(0.2f)
{

}

Dlg_SaltPepper::~Dlg_SaltPepper()
{
}

void Dlg_SaltPepper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Salt, salt);
	DDX_Text(pDX, IDC_EDIT_Pepper, pepper);
}


BEGIN_MESSAGE_MAP(Dlg_SaltPepper, CDialogEx)
END_MESSAGE_MAP()


// Dlg_SaltPepper ��Ϣ�������
