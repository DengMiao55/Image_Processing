
// Image_ProcessingView.cpp : CImage_ProcessingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
#include "_Histogram.h"
#include "CplexNum.h"
#include "Fourier.h"

#include "Dlg_IdeaFilter.h"
#include "Dlg_ButterWorth.h"
#include "Dlg_GaussianFilter.h"
#include "Dlg_MedianFilter.h"
#include "Dlg_SaltPepper.h"
#include "Dlg_GaussNoisy.h"

#include <vector>
#include <math.h>


using namespace std;
//#include"opencv2/core/core.hpp"
//#include"opencv2/imgproc/imgproc.hpp"
//#include"opencv2/highgui/highgui.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace cv;
// CImage_ProcessingView

IMPLEMENT_DYNCREATE(CImage_ProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImage_ProcessingView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImage_ProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CImage_ProcessingView::OnFileOpen)
	ON_COMMAND(IDM_DRAWLINE, &CImage_ProcessingView::OnDrawline)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImage_ProcessingView::OnFileSaveAs)
	ON_COMMAND(IDM_SHOWRED, &CImage_ProcessingView::OnShowred)
	//	ON_COMMAND(ID_VIEW_TOOLBAR, &CImage_ProcessingView::OnViewToolbar)
	ON_COMMAND(ID_reduce_resolution, &CImage_ProcessingView::Onreduceresolution)
	ON_COMMAND(ID_intensity_level128, &CImage_ProcessingView::Onintensitylevel128)
	ON_COMMAND(ID_intensity_level64, &CImage_ProcessingView::Onintensitylevel64)
	ON_COMMAND(ID_intensity_level32, &CImage_ProcessingView::Onintensitylevel32)
	ON_COMMAND(ID_intensity_level16, &CImage_ProcessingView::Onintensitylevel16)
	ON_COMMAND(ID_intensity_level8, &CImage_ProcessingView::Onintensitylevel8)
	ON_COMMAND(ID_intensity_level4, &CImage_ProcessingView::Onintensitylevel4)
	ON_COMMAND(ID_intensity_level2, &CImage_ProcessingView::Onintensitylevel2)
	ON_COMMAND(ID_difference, &CImage_ProcessingView::Ondifference)
	ON_COMMAND(ID_Add_Noise_Elimination, &CImage_ProcessingView::OnAddNoiseElimination)
	ON_COMMAND(ID_Statistical_Histogram, &CImage_ProcessingView::OnStatisticalHistogram)
	ON_COMMAND(ID_Histogram_Equalization, &CImage_ProcessingView::OnHistogramEqualization)
	ON_COMMAND(ID_Histogram_Specification, &CImage_ProcessingView::OnHistogramSpecification)
	ON_COMMAND(ID_Fourier, &CImage_ProcessingView::OnFourier)
	ON_COMMAND(ID_IdealPass, &CImage_ProcessingView::OnIdealpass)
	ON_COMMAND(ID_ButterworthPass, &CImage_ProcessingView::OnButterworthpass)
	ON_COMMAND(ID_Ifft, &CImage_ProcessingView::OnIfft)
	ON_COMMAND(ID_GaussianFilter, &CImage_ProcessingView::OnGaussianfilter)
	ON_COMMAND(ID_Salt_Pepper, &CImage_ProcessingView::OnSaltPepper)
	ON_COMMAND(ID_MedianFilter, &CImage_ProcessingView::OnMedianfilter)
	ON_COMMAND(ID_AdaptiveMedianFilter, &CImage_ProcessingView::OnAdaptivemedianfilter)
	ON_COMMAND(ID_RGB_R, &CImage_ProcessingView::OnRgbR)
	ON_COMMAND(ID_RGB_G, &CImage_ProcessingView::OnRgbG)
	ON_COMMAND(ID_RGB_B, &CImage_ProcessingView::OnRgbB)
	ON_COMMAND(ID_HSI_H, &CImage_ProcessingView::OnHsiH)
	ON_COMMAND(ID_HSI_S, &CImage_ProcessingView::OnHsiS)
	ON_COMMAND(ID_HSI_I, &CImage_ProcessingView::OnHsiI)
	ON_COMMAND(ID_RGB_Equalization, &CImage_ProcessingView::OnRgbEqualization)
	ON_COMMAND(ID_I_Equalization, &CImage_ProcessingView::OnIEqualization)
	ON_COMMAND(ID_Color_Segmentation, &CImage_ProcessingView::OnColorSegmentation)
	ON_COMMAND(ID_Detect_Straightline, &CImage_ProcessingView::OnDetectStraightline)
	ON_COMMAND(ID_GaussNoisy, &CImage_ProcessingView::OnGaussnoisy)
	ON_COMMAND(ID_Rand_Point, &CImage_ProcessingView::OnRandPoint)
END_MESSAGE_MAP()



// CImage_ProcessingView ����/����

CImage_ProcessingView::CImage_ProcessingView()
{
	// TODO: �ڴ˴���ӹ������

	FTResult = NULL;
	FftTime = 0;
	addNoise = 0;


}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView ����

void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (!m_Image.IsNull())
	{
		m_Image.Draw(pDC->m_hDC, 0, 0);
	}
	return;
}

void CImage_ProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView ��ӡ


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CImage_ProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImage_ProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImage_ProcessingView ���

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView ��Ϣ�������


void CImage_ProcessingView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		m_Image.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		CSize sizeTotal;
		int w = m_Image.GetWidth();
		int h = m_Image.GetHeight();
		sizeTotal.cx = w;
		sizeTotal.cy = h;
		SetScrollSizes(MM_TEXT, sizeTotal);

		//Window_Image_w=m_Image.GetWidth();//���ͼƬ�ĳ�ʼ��С��Ϊ�Ŵ���С������׼��
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;

	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();

	for (int k = 0; k < w; k++)
	{
		m_Image.m_pBits[0][10][k] = 0;//B
		m_Image.m_pBits[1][10][k] = 0;//G
		m_Image.m_pBits[2][10][k] = 0;//R


	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW����



}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {
		MessageBox(_T("�㻹û�д�һ��Ҫ�����ͼ���ļ���"));
		return;
	}
	CString strFilter;
	//strFilter ="λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||";   //
	strFilter = "�����ļ�|*.*||";   //

	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if (IDOK != dlg.DoModal())
		return;
	// ����û�û��ָ���ļ���չ������Ϊ�����һ��
	CString strFileName;
	//CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  ����ļ���
	//if(dlg.m_ofn.nFileExtension == 0)     //����ļ���չ��
	//{
	//	switch (dlg.m_ofn.nFilterIndex)
	//	{
	//	case 1:
	//		strExtension = "bmp"; break;
	//	case 2:
	//		strExtension = "jpg"; break;
	//	case 3:
	//		strExtension = "gif"; break;
	//	case 4:
	//		strExtension = "png"; break;
	//	default:
	//		break;
	//	}
	//	strFileName = strFileName + _T(".") + strExtension;
	//	//strFileName="C:\\Users\\Lenovo\\Desktop\\QSanguosha-Qingming\\abc.bmp";
	//}
	// ͼ�񱣴�
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image.m_pBits[0][j][k] = 0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image.m_pBits[1][j][k] = 0;//G


		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


//void CImage_ProcessingView::OnViewToolbar()
//{
//	// TODO: �ڴ���������������
//}


void CImage_ProcessingView::Onreduceresolution()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i

	//for (int i = 0; i < w; ++i)
	//{
	//	for (int j = 0; j < h; ++j)
	//	{
	//		m_Image.m_pBits[0][j/2][i/2] = m_Image.m_pBits[0][j][i];//B
	//		m_Image.m_pBits[1][j/2][i/2] = m_Image.m_pBits[1][j][i];//G
	//		m_Image.m_pBits[2][j/2][i/2] = m_Image.m_pBits[2][j][i];//R
	//	}
	//}

	//for (int i = 0 ; i < w; ++i)
	//{
	//for (int j = 0; j < h; ++j)
	//{
	//if (i > w / 2 || j > h / 2)
	//	m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = 255;
	//}
	//}
	for (int i = 0; 2 * i <= w - 1; ++i)
	{
		for (int j = 0; 2 * j <= h - 1; ++j)
		{
			m_Image.m_pBits[0][j][i] = (m_Image.m_pBits[0][2 * j][2 * i] + m_Image.m_pBits[0][2 * j][2 * i + 1] + m_Image.m_pBits[0][2 * j + 1][2 * i] + m_Image.m_pBits[0][2 * j + 1][2 * i + 1]) / 4;

			m_Image.m_pBits[1][j][i] = (m_Image.m_pBits[1][2 * j][2 * i] + m_Image.m_pBits[1][2 * j][2 * i + 1] + m_Image.m_pBits[1][2 * j + 1][2 * i] + m_Image.m_pBits[1][2 * j + 1][2 * i + 1]) / 4;

			m_Image.m_pBits[2][j][i] = (m_Image.m_pBits[2][2 * j][2 * i] + m_Image.m_pBits[2][2 * j][2 * i + 1] + m_Image.m_pBits[2][2 * j + 1][2 * i] + m_Image.m_pBits[2][2 * j + 1][2 * i + 1]) / 4;


			m_Image.m_pBits[0][2 * j + 1][2 * i] = m_Image.m_pBits[1][2 * j + 1][2 * i] = m_Image.m_pBits[2][2 * j + 1][2 * i] = 255;
			m_Image.m_pBits[0][2 * j][2 * i + 1] = m_Image.m_pBits[1][2 * j][2 * i + 1] = m_Image.m_pBits[2][2 * j][2 * i + 1] = 255;
			m_Image.m_pBits[0][2 * j + 1][2 * i + 1] = m_Image.m_pBits[1][2 * j + 1][2 * i + 1] = m_Image.m_pBits[2][2 * j + 1][2 * i + 1] = 255;

			if (i > 0 || j > 0)
			{
				m_Image.m_pBits[0][2 * j][2 * i] = m_Image.m_pBits[1][2 * j][2 * i] = m_Image.m_pBits[2][2 * j][2 * i] = 255;
			}

		}

	}


	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}





void CImage_ProcessingView::Onintensitylevel128()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i
	int L = 128;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��

}


void CImage_ProcessingView::Onintensitylevel64()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i
	int L = 64;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::Onintensitylevel32()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i
	int L = 32;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::Onintensitylevel16()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i
	int L = 16;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::Onintensitylevel8()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i
	int L = 8;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::Onintensitylevel4()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�i
	int L = 4;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::Onintensitylevel2()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	int L = 2;
	int Q = 256 / L;

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			int n = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			for (int k = 0; k < Q; ++k)
			{
				if (k*Q < n&&n < (k + 1)*Q)
				{
					m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = k*Q;
				}
			}
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::Ondifference()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w1 = m_Image.GetWidth();//���ͼ����
	int h1 = m_Image.GetHeight();//���ͼ��߶�
	MyImage_ m_Image2;//����ڶ���ͼ
	CFileDialog dlg(TRUE);//�ļ���
	MessageBox(L"�򿪵ڶ���ͼ");//�����Ի���
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!m_Image2.IsNull()) m_Image2.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		m_Image2.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ
		int w2 = m_Image2.GetWidth();//���ͼ����
		int h2 = m_Image2.GetHeight();//���ͼ��߶�
		if (w1 != w2 || h1 != h2)
		{
			MessageBox(L"ͼ���С����");
			return;
		}
		for (int i = 0; i < w1; ++i)
		{
			for (int j = 0; j < h1; ++j)
			{
				//���
				m_Image.m_pBits[0][j][i] = abs(m_Image.m_pBits[0][j][i] - m_Image2.m_pBits[0][j][i]);//B  
				m_Image.m_pBits[1][j][i] = abs(m_Image.m_pBits[1][j][i] - m_Image2.m_pBits[1][j][i]);//G
				m_Image.m_pBits[2][j][i] = abs(m_Image.m_pBits[2][j][i] - m_Image2.m_pBits[2][j][i]);//R
			}
		}
		Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
	}
}





void CImage_ProcessingView::OnAddNoiseElimination()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w1 = m_Image.GetWidth();//���ͼ����
	int h1 = m_Image.GetHeight();//���ͼ��߶�
	MyImage_ m_Image2;//����ڶ���ͼ
	CFileDialog dlg(TRUE);//�ļ���
	MessageBox(L"�򿪵ڶ���ͼ");//�����Ի���
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!m_Image2.IsNull()) m_Image2.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		m_Image2.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ
		int w2 = m_Image2.GetWidth();//���ͼ����
		int h2 = m_Image2.GetHeight();//���ͼ��߶�
		if (w1 != w2 || h1 != h2)
		{
			MessageBox(L"ͼ���С����");
			return;
		}
		for (int i = 0; i < w1; ++i)
		{
			for (int j = 0; j < h1; ++j)
			{
				//���
				m_Image.m_pBits[0][j][i] = (m_Image.m_pBits[0][j][i] + m_Image2.m_pBits[0][j][i]) / 2;//B  
				m_Image.m_pBits[1][j][i] = (m_Image.m_pBits[1][j][i] + m_Image2.m_pBits[1][j][i]) / 2;//G
				m_Image.m_pBits[2][j][i] = (m_Image.m_pBits[2][j][i] + m_Image2.m_pBits[2][j][i]) / 2;//R
			}
		}
		Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
	}
}


void CImage_ProcessingView::OnStatisticalHistogram()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//���ͼ����
	int h = m_Image.GetHeight();//���ͼ��߶�
	int k = 0;
	int a[256] = { 0 };
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			k = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			a[k]++;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��

	_Histogram dlg;
	for (int i = 0; i < 256; i++)
	{
		dlg.Arry[i] = a[i];
	}
	if (IDOK == dlg.DoModal())
	{
		return;
	}
}


void CImage_ProcessingView::OnHistogramEqualization()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	const int L = 256;
	int k = 0;
	int a[256];
	float Sk[256];
	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			k = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			a[k]++;
		}
	}

	Sk[0] = (L - 1)*a[0] / (w*h);
	for (int i = 1; i < 256; ++i)
	{
		a[i] = a[i] + a[i - 1];
		Sk[i] = (L - 1)*a[i] / (w*h);
	}
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			k = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
			m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = int(Sk[k] + 0.5);
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::OnHistogramSpecification()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	MyImage_ m_Image2;
	CFileDialog dlg(TRUE);
	MessageBox(L"�򿪵ڶ���ͼ");
	const int L = 256;
	int k = 0;
	int a[256], b[256];
	float Sk1[256], Sk2[256];
	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if (!m_Image2.IsNull()) m_Image2.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		m_Image2.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ
		int w2 = m_Image2.GetWidth();//���ͼ��Ŀ��
		int h2 = m_Image2.GetHeight();//���ͼ��ĸ߶�


		for (int i = 0; i < w; ++i)
		{
			for (int j = 0; j < h; ++j)
			{
				k = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
				b[k]++;
			}
		}

		Sk1[0] = (L - 1)*a[0] / (w*h);
		for (int i = 1; i < 256; ++i)
		{
			b[i] = b[i] + b[i - 1];
			Sk1[i] = (L - 1)*b[i] / (w*h);
		}

		for (int i = 0; i < w2; ++i)
		{
			for (int j = 0; j < h2; ++j)
			{
				k = m_Image2.m_pBits[0][j][i] = m_Image2.m_pBits[1][j][i] = m_Image2.m_pBits[2][j][i];
				a[k]++;
			}
		}
		Sk2[0] = (L - 1)*a[0] / (w2*h2);
		for (int i = 1; i < 256; ++i)
		{
			a[i] = a[i] + a[i - 1];
			Sk2[i] = (L - 1)*a[i] / (w2*h2);
		}

		float Zk[256];

		//����ӳ���ϵ
		for (int i = 0; i < 256; i++)
		{
			int m = 0;
			float min_value = 1.0f;//float����С��ֵ
			for (int j = 0; j < 256; j++)
			{
				float now_value = 0.0f;
				if (Sk2[i] - Sk1[j] >= 0.0f)
				{
					now_value = Sk2[i] - Sk1[j];
				}
				else
				{
					now_value = Sk1[j] - Sk2[i];
				}
				if ((now_value / 255) < min_value)
				{
					m = j;//��¼��Сֵλ��
					min_value = now_value * 255;//���ϸ�����С��ֵ
				}
			}
			Zk[i] = Sk1[m];//�����Ҷ�ӳ���
		}

		//�Ը����ؽ���ֱ��ͼ�涨��ӳ�䴦��
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				k = m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i];
				m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = int(Zk[k] + 0.5);
			}
		}
		Invalidate(1);
	}


}







void CImage_ProcessingView::OnFourier()
{
	// TODO: �ڴ���������������

	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();


	long i, j;					//i:��ѭ������ ,j:��ѭ������
	double dTmp;				//��ʱ����
								//w��h��
	long wid = 1, hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor = 0, heipor = 0;		//wid hei :2���ݴ���

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��Ƶ���ָ������ڴ�


	//////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
	while (wid * 2 <= w)
	{
		wid *= 2;
		widpor++;
	}
	while (hei * 2 <= h)
	{
		hei *= 2;
		heipor++;
	}

	/////////��ʼ��pTd//////////////
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = 0;
			pTd[i*wid + j].im = 0;
		}
	}

	/////////ͼ����pTdָ��////////////////////////////
	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			pTd[j*wid + i].re = pow((double)-1, (double)(i + j))*m_Image.m_pBits[0][j][i];//��-1)^i+j�ƶ��任����
		}
	}
	++FftTime;



	if (FTResult)
	{
		delete[]FTResult;								//����任���ָ����Ч��ɾ���ڴ�
	}
	FTResult = new CplexNum[sizeof(CplexNum)*w*h];	//Ϊ�任������·����ڴ�
	//////////���ø���Ҷ�仯����Fourier////////////////////
	Fourier(pTd, w, h, pFd/*, this*/);

	/////////////������/////////////

	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			FTResult[wid *i + j] = pTd[wid *i + j];
		}
	}

	////////////�����任����ʾ���/////////////////////////
	int **Ftmp;			//�ݴ��ά����wid*hei -> ��i����j��
						//��ά����  ��hei*wid -> ��j����i��

						//////////////�����ڴ�/////////////////////
	Ftmp = new int *[wid];
	double maxF(1);//�任������ϵ��
	int s(1);	//�����任ϵ��
	for (i = 0; i < wid; i++)
	{
		Ftmp[i] = new int[hei];
	}

	//////////////�����ݴ��ά����///////////////
	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			dTmp = pTd[j*wid + i].re*pTd[j*wid + i].re + pTd[j*wid + i].im*pTd[j*wid + i].im;
			dTmp = sqrt(dTmp) / 100;
			if (maxF < dTmp)
			{
				maxF = dTmp;//�������ֵ
			}
			Ftmp[i][j] = dTmp;
		}
	}
	double maxx = 0;
	double v = 2;//����
				 ///////////////�����任///////////////////
	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			long double p = Ftmp[i][j];
			//p=p/maxF;
			//p=(log(1+v*p)/log(v));
			Ftmp[i][j] = (log(1 + p) / log(v));
			if (maxx < Ftmp[i][j])
			{
				maxx = Ftmp[i][j];
			}

		}
	}
	double pq = 255 / maxx;//ռ����
	///////////////////������Դͼ////////////////
	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			double p = pq* Ftmp[i][j];
			if (p > 255) {
				p = 255;
			}

			m_Image.m_pBits[2][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[0][j][i] = p;
			//m_Image.m_pBits[1][j][i]=min(pq*Ftmp[i][j],255);
			//m_Image.m_pBits[2][j][i]=min(pq*Ftmp[i][j],255);
		}
	}

	//////////////////�����ݴ�����ָ��////////////////
	for (i = 0; i < wid; i++)
	{
		delete[]Ftmp[i];
	}
	delete[]Ftmp;

	delete[]pTd;
	delete[]pFd;
	Invalidate(TRUE);
}


void CImage_ProcessingView::OnIfft()
{

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	if (!FftTime) //�ж�ͼ���Ƿ�Ϊ��
	{
		MessageBox(L"���ȸ���Ҷ�任��");
		return;
	}

	m_Image.Flag = 0;	//�ָ�FLAG
	--FftTime;

	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();


	double dTmp;				//��ʱ����
	long i, j;					//i:��ѭ������ ,j:��ѭ������
								//w��h��
	long wid = 1, hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor = 0, heipor = 0;		//wid hei :2���ݴ���

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��Ƶ���ָ������ڴ�

													   //////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
	while (wid * 2 <= w)
	{
		wid *= 2;
		widpor++;
	}
	while (hei * 2 <= h)
	{
		hei *= 2;
		heipor++;
	}

	/////////��ʼ��pTd//////////////
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = FTResult[i*wid + j].re;
			pTd[i*wid + j].im = -FTResult[i*wid + j].im;//����
		}
	}


	//////////���ø���Ҷ�仯����Fourier////////////////////
	Fourier(pTd, w, h, pFd);



	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			dTmp = pTd[i*wid + j].re;
			dTmp = pTd[i*wid + j].im;
			pTd[i*wid + j].re = pTd[i*wid + j].re / (double)(wid*hei);
			pTd[i*wid + j].im = -pTd[i*wid + j].im / (double)(wid*hei);//����
		}
	}




	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{

			m_Image.m_pBits[2][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[0][j][i] = pow((double)-1, (double)(i + j))*pTd[j*wid + i].re;
			//m_Image.m_pBits[1][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
			//m_Image.m_pBits[2][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
		}
	}

	///////////����ָ���ڴ�/////////////
	delete[]pTd;
	delete[]pFd;


	Invalidate(TRUE);
}


void CImage_ProcessingView::OnIdealpass()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(L"���Ƚ��и���Ҷ�任��");
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	int a, b;


	double **modul;
	modul = new double*[w];
	for (int i = 0; i < w; i++)
	{
		modul[i] = new double[h];
	}



	double D = 50;

	Dlg_IdeaFilter dlg;
	if (IDOK == dlg.DoModal()) {


		D = dlg.D;
	}
	else {

		return;
	}
	if (dlg.Idel_highPass == 1)
	{
		a = 0;
		b = 1;
	}
	else
	{
		a = 1;
		b = 0;
	}


	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if ((pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2)) <= D*D)
			{
				modul[i][j] = a;
			}
			else {
				modul[i][j] = b;
			}

		}
	}

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = modul[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = modul[j][i] * FTResult[w *i + j].re;
		}
	}


	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]modul[i];
	}
	delete[]modul;




	CImage_ProcessingView::OnIfft();
	Invalidate(1);
}


void CImage_ProcessingView::OnButterworthpass()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(L"���Ƚ��и���Ҷ�任��");
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	//����ģ��
	double **modul;
	modul = new double*[w];
	for (int i = 0; i < w; i++)
	{
		modul[i] = new double[h];
	}
	double D = 50;
	int N = 2;
	Dlg_ButterWorth dlg;
	if (IDOK == dlg.DoModal())
	{
		D = dlg.D;
		N = dlg.N;
	}
	else {

		return;
	}
	if (dlg.Butter_highPass == 1)
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				modul[i][j] = 1.0 / (pow((D / pow(pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2), 0.5)), (double)2 * N) + 1);

			}
		}
	}


	else
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				modul[i][j] = 1.0 / (pow((pow(pow((double)(i - w / 2), (double)2) + pow((double)(j - h / 2), (double)2), 0.5) / D), (double)2 * N) + 1);

			}
		}
	}

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = modul[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = modul[j][i] * FTResult[w *i + j].re;
		}



	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]modul[i];
	}
	delete[]modul;

	//����IFFT
	CImage_ProcessingView::OnIfft();

}



void CImage_ProcessingView::OnGaussianfilter()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(L"���Ƚ��и���Ҷ�任��");
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	//����ģ��
	double **modul;
	modul = new double*[w];
	for (int i = 0; i < w; i++)
	{
		modul[i] = new double[h];
	}
	double D;
	Dlg_GaussianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		D = dlg.D;
	}
	else
		return;


	//if (dlg.Gaussian_highPass == 1)
	//{
	//	for (int i = 0; i<w; i++)
	//	{
	//		for (int j = 0; j<h; j++)
	//		{
	//			modul[i][j] = 1.0 - exp(-((pow((double)(i - w / 2), 2) + pow((double)(j - h / 2), 2)) / 2 * pow((double)D, 2)));

	//		}
	//	}
	//}
	//else
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			modul[i][j] = exp(-((pow((double)(i - w / 2), 2) + pow((double)(j - h / 2), 2)) / 2 * pow((double)D, 2)));

		}
	}


	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			FTResult[w *i + j].im = modul[j][i] * FTResult[w *i + j].im;
			FTResult[w *i + j].re = modul[j][i] * FTResult[w *i + j].re;
		}



	//����ָ���ڴ�
	for (int i = 0; i < w; i++)
	{
		delete[]modul[i];
	}
	delete[]modul;

	//����IFFT
	CImage_ProcessingView::OnIfft();
}


void CImage_ProcessingView::OnSaltPepper()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	Dlg_SaltPepper dlg;//�����Ի������
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

									 //�ж��Ƿ�������Ч������
		while (dlg.pepper < 0 || dlg.pepper>1 || dlg.salt < 0 || dlg.salt>1 ||
			(dlg.salt + dlg.pepper) > 1)
		{
			MessageBox(L"	 ������Ч\n������������Ч����������");
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
		int h = m_Image.GetHeight();

		float p_a = dlg.salt;//��ȡ������ĸ���,p_a(��),p_b���ף�
		float p_b = dlg.pepper;


		float P_Sum = p_a + p_b;
		float xishu = 1 / P_Sum;
		float p_a_1 = p_a*xishu;
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				if (rand() / 32767.0 < P_Sum)//ָ������rand()��������Ľ���1-32767����
				{
					if (rand() / 32767.0 < p_a_1)
					{
						m_Image.m_pBits[0][j][i] = 0;         //�����ص���ʾΪ��ɫ
						m_Image.m_pBits[1][j][i] = 0;
						m_Image.m_pBits[2][j][i] = 0;

					}
					else
					{
						m_Image.m_pBits[0][j][i] = 255;         //�����ص���ʾΪ��ɫ
						m_Image.m_pBits[1][j][i] = 255;
						m_Image.m_pBits[2][j][i] = 255;
					}

				}
			}
		Invalidate(1);
	}
	addNoise++;
}


void CImage_ProcessingView::OnMedianfilter()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	Dlg_MedianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		while (dlg.size % 2 == 0 || dlg.size<0 || dlg.size>w || dlg.size > h)
		{
			MessageBox(L"   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}
	}

	//��������ά���飬�����ݴ���ͼ��
	BYTE *** NewPicture = nullptr;
	NewPicture = new  BYTE **[3];//3��ά�ȣ������ڴ�  
	for (int i = 0; i < 3; i++)
	{
		NewPicture[i] = new  BYTE*[h];   //��H
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			NewPicture[i][j] = new BYTE[w];   //��W
		}
	}

	//�ݴ����飬��ȡ��ֵ
	int *B, *G, *R;
	B = new int[dlg.size*dlg.size];
	G = new int[dlg.size*dlg.size];
	R = new int[dlg.size*dlg.size];

	int sz;//�����±�

	for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
	{
		for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
		{
			sz = 0;
			for (int k = -((dlg.size - 1) / 2); k < (((dlg.size - 1) / 2) + 1); k++)//ģ����ѭ��
			{
				for (int kk = -((dlg.size - 1) / 2); kk < (((dlg.size - 1) / 2) + 1); kk++)
				{
					B[sz] = m_Image.m_pBits[0][j + k][i + kk];
					G[sz] = m_Image.m_pBits[1][j + k][i + kk];
					R[sz] = m_Image.m_pBits[2][j + k][i + kk];
					sz++;
				}
			}
			std::sort(B, B + dlg.size*dlg.size);//sort����
			std::sort(G, G + dlg.size*dlg.size);
			std::sort(R, R + dlg.size*dlg.size);
			NewPicture[0][j][i] = B[(dlg.size*dlg.size - 1) / 2 + 1];
			NewPicture[1][j][i] = G[(dlg.size*dlg.size - 1) / 2 + 1];
			NewPicture[2][j][i] = R[(dlg.size*dlg.size - 1) / 2 + 1];
		}
		//double p;
		//p = (double)j / (double)(h - ((dlg.size - 1) / 2));
		//int k = p * 100;

		//((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
	}
	//((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

													  //����ͼ����Դͼ
	for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//��ͼ��û�г�ʼ����!
	{
		for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
		{
			m_Image.m_pBits[0][j][i] = NewPicture[0][j][i];
			m_Image.m_pBits[1][j][i] = NewPicture[1][j][i];
			m_Image.m_pBits[2][j][i] = NewPicture[2][j][i];
		}
	}

	//����ָ��
	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] NewPicture[i][j];//�����ڴ�
		}
	}
	for (int i = 0; i < 3; i++)
	{
		delete[] NewPicture[i];
	}
	delete[] NewPicture;

	//////////////////////////////////////////////////////////////////////////
	Invalidate(1);

}


void CImage_ProcessingView::OnAdaptivemedianfilter()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG

	if (addNoise < 2)
	{
		MessageBox(L"�������������");
		return;
	}

	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	Dlg_MedianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

									 //�ж��Ƿ�������Ч������
		while (dlg.size % 2 == 0 || dlg.size<0 || dlg.size>w || dlg.size > h)
		{
			MessageBox(L"   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//��������ά���飬�����ݴ���ͼ��
		BYTE *** NewPicture = nullptr;
		NewPicture = new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for (int i = 0; i < 3; i++)
		{
			NewPicture[i] = new  BYTE*[h];   //��H
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{
				NewPicture[i][j] = new BYTE[w];   //��W
			}
		}

		//�ݴ����飬��ȡ��ֵ
		int *B, *G, *R;
		B = new int[dlg.size*dlg.size];
		G = new int[dlg.size*dlg.size];
		R = new int[dlg.size*dlg.size];

		int sz;//�����±�


		for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
			{
				//B
				for (int FilterSize = 3; FilterSize <= dlg.size; FilterSize += 2)
				{
					sz = 0;
					for (int k = -((FilterSize - 1) / 2); k < (((FilterSize - 1) / 2) + 1); k++)//ģ����ѭ��
					{
						for (int kk = -((FilterSize - 1) / 2); kk < (((FilterSize - 1) / 2) + 1); kk++)
						{
							B[sz] = m_Image.m_pBits[0][j + k][i + kk];

							sz++;
						}
					}
					for (int i = 0; i < FilterSize*FilterSize; i++)
					{
						sz = B[i];
					}
					std::sort(B, B + FilterSize*FilterSize);//sort����,ע��ڶ�������������
					for (int i = 0; i < FilterSize*FilterSize; i++)
					{
						sz = B[i];
					}

					NewPicture[0][j][i] = B[(FilterSize*FilterSize - 1) / 2 + 1];


					sz = B[(FilterSize*FilterSize - 1) / 2 + 1];
					sz = B[FilterSize*FilterSize - 1];
					sz = B[0];
					if ((B[(FilterSize*FilterSize - 1) / 2 + 1] != B[FilterSize*FilterSize - 1]) && (B[(FilterSize*FilterSize - 1) / 2 + 1] != B[0]))//�����ֵ������
					{
						if ((m_Image.m_pBits[0][j][i] != B[FilterSize*FilterSize - 1]) && (m_Image.m_pBits[0][j][i] != B[0]))//������ķ�����
						{
							sz = m_Image.m_pBits[0][j][i];
							NewPicture[0][j][i] = m_Image.m_pBits[0][j][i];//���ԭֵ

						}
						else
						{
							sz = B[(FilterSize*FilterSize - 1) / 2 + 1];
							NewPicture[0][j][i] = B[(FilterSize*FilterSize - 1) / 2 + 1];//�����ֵ
						}
						break;
					}
				}

				//G
				for (int FilterSize = 3; FilterSize <= dlg.size; FilterSize += 2)
				{
					sz = 0;
					for (int k = -((FilterSize - 1) / 2); k < (((FilterSize - 1) / 2) + 1); k++)//ģ����ѭ��
					{
						for (int kk = -((FilterSize - 1) / 2); kk < (((FilterSize - 1) / 2) + 1); kk++)
						{
							G[sz] = m_Image.m_pBits[1][j + k][i + kk];
							sz++;
						}
					}
					std::sort(G, G + FilterSize*FilterSize);
					NewPicture[1][j][i] = G[(FilterSize*FilterSize - 1) / 2 + 1];
					if ((G[(FilterSize*FilterSize - 1) / 2 + 1] != G[FilterSize*FilterSize - 1]) && (G[(FilterSize*FilterSize - 1) / 2 + 1] != G[0]))//�����ֵ������
					{
						if ((m_Image.m_pBits[1][j][i] != G[FilterSize*FilterSize - 1]) && (m_Image.m_pBits[1][j][i] != G[0]))//������ķ�����
						{
							NewPicture[1][j][i] = m_Image.m_pBits[1][j][i];//���ԭֵ

						}
						else
						{
							NewPicture[1][j][i] = G[(FilterSize*FilterSize - 1) / 2 + 1];//�����ֵ
						}
						break;
					}
				}

				//R
				for (int FilterSize = 3; FilterSize <= dlg.size; FilterSize++)
				{
					sz = 0;
					for (int k = -((FilterSize - 1) / 2); k < (((FilterSize - 1) / 2) + 1); k++)//ģ����ѭ��
					{
						for (int kk = -((FilterSize - 1) / 2); kk < (((FilterSize - 1) / 2) + 1); kk++)
						{
							R[sz] = m_Image.m_pBits[2][j + k][i + kk];
							sz++;
						}
					}
					std::sort(R, R + FilterSize*FilterSize);
					NewPicture[2][j][i] = R[(FilterSize*FilterSize - 1) / 2 + 1];
					if ((R[(FilterSize*FilterSize - 1) / 2 + 1] != R[FilterSize*FilterSize - 1]) && (R[(FilterSize*FilterSize - 1) / 2 + 1] != R[0]))//�����ֵ������
					{
						if ((m_Image.m_pBits[2][j][i] != R[FilterSize*FilterSize - 1]) && (m_Image.m_pBits[2][j][i] != R[0]))//������ķ�����
						{
							NewPicture[2][j][i] = m_Image.m_pBits[2][j][i];//���ԭֵ

						}
						else
						{
							NewPicture[2][j][i] = R[(FilterSize*FilterSize - 1) / 2 + 1];//�����ֵ
						}
						break;
					}
				}



			}
		}


		//����ͼ����Դͼ
		for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//��ͼ��û�г�ʼ����!
		{
			for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
			{
				m_Image.m_pBits[0][j][i] = NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i] = NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i] = NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{
				delete[] NewPicture[i][j];//�����ڴ�
			}
		}
		for (int i = 0; i < 3; i++)
		{
			delete[] NewPicture[i];
		}
		delete[] NewPicture;

		//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}





void CImage_ProcessingView::OnRgbR()
{
	// TODO: �ڴ���������������

	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			//image.m_pBits[2][j][i] = m_Image.m_pBits[2][j][i];
			m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = 0;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnRgbG()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			//image.m_pBits[2][j][i] = m_Image.m_pBits[2][j][i];
			m_Image.m_pBits[0][j][i] = m_Image.m_pBits[2][j][i] = 0;
		}
	}
	Invalidate(1);
}



void CImage_ProcessingView::OnRgbB()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			//image.m_pBits[2][j][i] = m_Image.m_pBits[2][j][i];
			m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = 0;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnHsiH()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	vector<vector<int>> H;//H����
	for (int i = 0; i < w; i++)
	{
		vector<int> vec;
		H.push_back(vec);
		for (int j = 0; j < h; j++)
		{
			double tmpH;
			int R = m_Image.m_pBits[2][j][i];
			int G = m_Image.m_pBits[1][j][i];
			int B = m_Image.m_pBits[0][j][i];
			tmpH = acos((double)(2 * R - G - B) / (2 * sqrt((double)(R - G)*(R - G) + (double)(R - B)*(G - B))));

			if (B <= G)
			{
				tmpH = tmpH*(double)180 / (double)3.1415926;
			}
			else {
				tmpH = 360 - tmpH*(double)180 / (double)3.1415926;
			}
			H[i].push_back(tmpH);
		}
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			m_Image.m_pBits[0][j][i] = H[(int)(i)][(int)(j)] * (double)255 / (double)360;
			m_Image.m_pBits[1][j][i] = H[(int)(i)][(int)(j)] * (double)255 / (double)360;
			m_Image.m_pBits[2][j][i] = H[(int)(i)][(int)(j)] * (double)255 / (double)360;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnHsiS()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	vector<vector<int>> S;//S����
	for (int i = 0; i < w; i++)
	{
		vector<int> vec;
		S.push_back(vec);
		for (int j = 0; j < h; j++)
		{
			double tmpS;
			int R = m_Image.m_pBits[2][j][i];
			int G = m_Image.m_pBits[1][j][i];
			int B = m_Image.m_pBits[0][j][i];
			int temp;
			if (R <= G)
			{
				if (R <= B)
				{
					temp = R;
				}
				else
					temp = B;
			}
			else
			{
				if (G <= B)
				{
					temp = G;
				}
				else
					temp = B;
			}
			tmpS = (double)1 - ((double)3 * temp) / (double)(R + G + B);

			S[i].push_back(tmpS);
		}
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			m_Image.m_pBits[0][j][i] = S[(int)(i)][(int)(j)] * (double)255;
			m_Image.m_pBits[1][j][i] = S[(int)(i)][(int)(j)] * (double)255;
			m_Image.m_pBits[2][j][i] = S[(int)(i)][(int)(j)] * (double)255;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnHsiI()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	vector<vector<int>> I;//I����
	for (int i = 0; i < w; i++)
	{
		vector<int> vec;
		I.push_back(vec);
		for (int j = 0; j < h; j++)
		{
			double tmpI;
			int R = m_Image.m_pBits[2][j][i];
			int G = m_Image.m_pBits[1][j][i];
			int B = m_Image.m_pBits[0][j][i];
			tmpI = (double)(R + G + B) / (double)3;

			I[i].push_back(tmpI);
		}
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			m_Image.m_pBits[0][j][i] = I[(int)(i)][(int)(j)] * (double)255;
			m_Image.m_pBits[1][j][i] = I[(int)(i)][(int)(j)] * (double)255;
			m_Image.m_pBits[2][j][i] = I[(int)(i)][(int)(j)] * (double)255;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnRgbEqualization()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	const int L = 256;
	int k = 0;
	int a[3][256];
	float Sk[3][256];
	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			k = m_Image.m_pBits[0][j][i];
			a[0][k]++;
			k = m_Image.m_pBits[1][j][i];
			a[1][k]++;
			k = m_Image.m_pBits[2][j][i];
			a[2][k]++;
		}
	}

	Sk[0][0] = (L - 1)*a[0][0] / (w*h);
	Sk[1][0] = (L - 1)*a[1][0] / (w*h);
	Sk[1][0] = (L - 1)*a[2][0] / (w*h);
	for (int i = 1; i < 256; ++i)
	{
		a[0][i] = a[0][i] + a[0][i - 1];
		Sk[0][i] = (L - 1)*a[0][i] / (w*h);

		a[1][i] = a[1][i] + a[1][i - 1];
		Sk[1][i] = (L - 1)*a[1][i] / (w*h);

		a[2][i] = a[2][i] + a[2][i - 1];
		Sk[2][i] = (L - 1)*a[2][i] / (w*h);

	}
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			k = m_Image.m_pBits[0][j][i];
			m_Image.m_pBits[0][j][i] = int(Sk[0][k] + 0.5);
			k = m_Image.m_pBits[1][j][i];
			m_Image.m_pBits[1][j][i] = int(Sk[1][k] + 0.5);
			k = m_Image.m_pBits[2][j][i];
			m_Image.m_pBits[2][j][i] = int(Sk[2][k] + 0.5);
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}




void CImage_ProcessingView::OnIEqualization()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	vector<vector<vector<double>>> HSI;
	vector<vector<double>> vec;
	HSI.push_back(vec); HSI.push_back(vec); HSI.push_back(vec);
	//////////////////////////////////
	for (int i = 0; i < w; i++)
	{
		vector<double> vec;      //����vec
		HSI[0].push_back(vec);//H
		HSI[1].push_back(vec);//S
		HSI[2].push_back(vec);//I
		for (int j = 0; j < h; j++)
		{
			double tmp;
			int R = m_Image.m_pBits[2][j][i];
			int G = m_Image.m_pBits[1][j][i];
			int B = m_Image.m_pBits[0][j][i];

			tmp = acos((double)(2 * R - G - B) / (0.001 + 2 * sqrt((double)(R - G)*(R - G) + (double)(R - B)*(G - B))));//0.001��Ϊ��ӣ���ֹ����Ϊ��
			if (B <= G)
			{
				tmp = tmp;
			}
			else {
				tmp = 2 * 3.141592654 - tmp;
			}
			HSI[0][i].push_back(std::move(tmp));

			int min;
			if (R <= G)
			{
				if (R <= B)
				{
					min = R;
				}
				else
					min = B;
			}
			else
			{
				if (G <= B)
				{
					min = G;
				}
				else
					min = B;
			}
			tmp = (double)1 - ((double)3 * (double)min) / (double)(R + G + B);
			HSI[1][i].push_back(std::move(tmp));

			tmp = (R + G + B) / 3;
			HSI[2][i].push_back(std::move(tmp));
		}
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			m_Image.m_pBits[0][j][i] = HSI[2][i][j];//��vectorI������ֵͼƬ��һά��
		}
	}

	BYTE *lpSrc;	//ָ��Դͼ��ָ��
	int i, j;
	int gray[256];	//�Ҷȼ���
	float probability[256];
	//int nrow = m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
								   //float probability[256];
	BYTE pixel;		//����ֵ
					//BYTE *lpDIBBits=(BYTE *)m_CImage.GetBits();//���Դͼ����ʼλ��
	memset(gray, 0, sizeof(gray));//��ʼ��

	for (j = 0; j < h; j++)

	{
		for (i = 0; i < w; i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			gray[pixel]++;
		}
	}
	for (i = 0; i < 256; i++)
	{
		probability[i] = gray[i] / (w*h*1.0f);
	}
	BYTE *lpNewDIBBits;

	double temp[256];
	double   nRst[256];//ӳ���
	//int nrow = m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();
	CImage image3;			//����ͼ
	image3.Create(w, h, 24);	//Create����Ҫdelete
	lpNewDIBBits = (BYTE *)image3.GetBits();//���image3���һ�е����ص�ַ

	for (i = 0; i < 256; i++)
	{
		if (0 == i)
		{
			temp[0] = probability[0];
		}
		else
		{
			temp[i] = temp[i - 1] + probability[i];
		}
	}



	for (i = 0; i < 256; i++)
	{
		nRst[i] = (255.0f * temp[i] + 0.5f);
	}
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			HSI[2][i][j] = nRst[pixel];

		}
	}

	//////////////////////////////////////////////////////////////////////////
	//ת��ΪRGB
	double R, G, B;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			double tmp;
			double H = HSI[0][i][j];
			double S = HSI[1][i][j];
			double I = HSI[2][i][j];
			if (0 <= H*(double)180 / (double)3.1415926&&H*(double)180 / (double)3.1415926 < 120)
			{
				B = I*(1 - S);
				R = I*(1 + (S*cos(H)) / (cos(60 * (double)3.1415926 / (double)180 - H)));
				G = 3 * I - (R + B);
			}
			else if (120 <= H*(double)180 / (double)3.1415926&&H*(double)180 / (double)3.1415926 < 240)
			{
				H = H - 120.*(double)3.1415926 / (double)180;
				R = I*(1 - S);
				G = I*(1 + (S*cos(H)) / (cos(60 * (double)3.1415926 / (double)180 - H)));
				B = 3 * I - (R + G);

			}
			else if (240 <= H*(double)180 / (double)3.1415926&&H*(double)180 / (double)3.1415926 < 360)
			{
				H = H - 240.*(double)3.1415926 / (double)180;
				G = I*(1 - S);
				B = I*(1 + (S*cos(H)) / (cos(60 * (double)3.1415926 / (double)180 - H)));
				R = 3 * I - (B + G);
			}

			m_Image.m_pBits[2][j][i] = R > 255 ? 255 : R < 0 ? 0 : R;
			m_Image.m_pBits[1][j][i] = G > 255 ? 255 : G < 0 ? 0 : G;
			m_Image.m_pBits[0][j][i] = B > 255 ? 255 : B < 0 ? 0 : B;

		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::OnColorSegmentation()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	int i, j;
	int avg_r = 0, avg_g = 0, avg_b = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			avg_r += m_Image.m_pBits[0][j][i];
			avg_g += m_Image.m_pBits[1][j][i];
			avg_b += m_Image.m_pBits[2][j][i];

		}
	}
	avg_r = avg_r / 25;
	avg_g = avg_g / 25;
	avg_b = avg_b / 25;


	double D;
	double D0 = 100;
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			D = pow((pow(((double)avg_r - (double)m_Image.m_pBits[0][j][i]), 2) + pow(((double)avg_g - (double)m_Image.m_pBits[1][j][i]), 2) + pow(((double)avg_b - (double)m_Image.m_pBits[2][j][i]), 2)), double(0.5));
			if (D <= D0)
			{
				m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = 255;
			}
			else
				m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = 0;
		}
	}

	Invalidate(1);
}




void CImage_ProcessingView::OnDetectStraightline()
{
	//// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();
	int max_ro = (int)sqrt(w*w + h*h);
	int i, j;
	int **b;
	b = new int*[sizeof(int) * 180];
	for (int i = 0; i < 180; i++) {

		b[i] = new int[sizeof(int) * max_ro];
		memset(b[i], 0, sizeof(int)*max_ro);
	}

	//for (int i = 0; i < 180; i++) {

	//	for (int j = 0; j < max_ro; j++)
	//	{
	//		b[i][j] = 0;
	//	}
	//}

	////�����������������Ƚ�ͼ��ȫ������
	//for (int i = 0; i < h; i++)
	//{
	//	for (int j = 0; j < w; j++)
	//	{
	//		int x = rand() % h;
	//		int y = rand() % w;
	//		if ((rand() % 3000) > 1)    //����,�����һ��������
	//		{
	//			for (int k = 0; k < 3; k++)
	//			{

	//				m_Image.m_pBits[k][i][j] = 0;

	//			}

	//		}
	//		else  //��һ�����ʼ���һЩ����,�������ʽ�Ϊ1/3000
	//		{
	//			for (int k = 0; k < 3; k++)
	//			{

	//				m_Image.m_pBits[k][i][j] = 255;

	//			}

	//		}
	//	}
	//}

	//////��������������ֱ��
	//for (int k = 0; k < 3; k++) {
	//	for (int p = 10; p < int(h / 10); p += 3) {

	//		m_Image.m_pBits[k][1 * p][2 * p] = 255;

	//		m_Image.m_pBits[k][4 * p][2 * p] = 255;

	//		m_Image.m_pBits[k][7 * p][w - p - 10] = 255;//ע���Խ��

	//		m_Image.m_pBits[k][5 * p][w - 2 * p] = 255;//����һ��ע�Ⱑ,w-2*p��p��0��ʼ����ʱ,w-2*p =w,���Խ����

	//	}
	//}
	//Invalidate(TRUE);
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			int k = m_Image.m_pBits[0][y][x];// = m_Image.m_pBits[1][y][x] = m_Image.m_pBits[2][y][x];
			if (k == 255)
			{
				for (int i = 0; i < 180; i++)
				{
					int ro = int(x*sin(double(3.141592*i) / 180) + y*cos(double(3.141592*i) / 180));
					if (0 < ro &&ro < max_ro)
					{

						b[i][ro]++;

					}
				}
			}
		}
	}

	MessageBox(L"1234");
	//upouioikhsafkanf
	for (int i = 0; i < 180; i++)
	{
		for (int j = 0; j < max_ro; j++)
		{

			if (b[i][j] > 2)
			{
				for (int x = 0; x < w; x++)
				{
					for (int y = 0; y < h; y++)
					{
						if (j == int(x*sin(double(3.141592*i) / 180) + y*cos(double(3.141592*i) / 180)))
						{
							m_Image.m_pBits[0][y][x] = 255;
							m_Image.m_pBits[1][y][x] = 255;
							m_Image.m_pBits[2][y][x] = 255;
						}

					}
				}



			}

		}

	}

	for (int i = 0; i < 180; i++) 
	{
		delete[]b[i];
    }
	delete[]b;



	Invalidate(1);

}


void CImage_ProcessingView::OnGaussnoisy()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int z, avg_z;
	//Dlg_GaussNoisy *dlg = new Dlg_GaussNoisy;//�����Ի������
	//dlg->Create(IDD_GaussNosiy, this);
	//dlg->ShowWindow(SW_SHOW);
	Dlg_GaussNoisy dlg;
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������
		z = dlg.z;
		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ��

		int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
		int h = m_Image.GetHeight();
		int n = rand() % (z + 1);//ָ������rand()��������Ľ���0-z����

		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				if ((n + m_Image.m_pBits[0][j][i]) > 255)
				{
					m_Image.m_pBits[0][j][i] = 255;
				}
				else
					if ((n + m_Image.m_pBits[0][j][i]) < 0)
					{
						m_Image.m_pBits[0][j][i] = 0;
					}
					else
					{
						m_Image.m_pBits[0][j][i] += n;
					}


				if ((n + m_Image.m_pBits[1][j][i]) > 255)
				{
					m_Image.m_pBits[1][j][i] = 255;
				}
				else
					if ((n + m_Image.m_pBits[1][j][i]) < 0)
					{
						m_Image.m_pBits[1][j][i] = 0;
					}
					else {
						m_Image.m_pBits[1][j][i] += n;
					}

					if ((n + m_Image.m_pBits[2][j][i]) > 255)
					{
						m_Image.m_pBits[2][j][i] = 255;
					}
					else
						if ((n + m_Image.m_pBits[2][j][i]) < 0)
						{
							m_Image.m_pBits[2][j][i] = 0;
						}
						else {
							m_Image.m_pBits[2][j][i] += n;
						}
			}

		Invalidate(1);
	}
	addNoise++;

}


void CImage_ProcessingView::OnRandPoint()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull())
	{
		OnFileOpen();
	}
	m_Image.Flag = 0;	//�ָ�FLAG
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	//for (int i = 0; i < 40; i++)
	//{
	//	m_Image.m_pBits[0][rand() % (h+1)][rand() % 256] = m_Image.m_pBits[1][rand() % 256][rand() % 256] = m_Image.m_pBits[2][rand() % 256][rand() % 256] =255;
	//}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if ((rand() % 3000 == 0))
				m_Image.m_pBits[0][j][i] = m_Image.m_pBits[1][j][i] = m_Image.m_pBits[2][j][i] = 255;
		}
	}
	Invalidate(1);
}
