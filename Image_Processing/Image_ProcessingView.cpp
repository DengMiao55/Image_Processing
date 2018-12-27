
// Image_ProcessingView.cpp : CImage_ProcessingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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



// CImage_ProcessingView 构造/析构

CImage_ProcessingView::CImage_ProcessingView()
{
	// TODO: 在此处添加构造代码

	FTResult = NULL;
	FftTime = 0;
	addNoise = 0;


}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView 绘制

void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView 打印


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CImage_ProcessingView 诊断

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView 消息处理程序


void CImage_ProcessingView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		m_Image.Load(dlg.GetPathName());//获得图片的地址，并且加载图片

		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		CSize sizeTotal;
		int w = m_Image.GetWidth();
		int h = m_Image.GetHeight();
		sizeTotal.cx = w;
		sizeTotal.cy = h;
		SetScrollSizes(MM_TEXT, sizeTotal);

		//Window_Image_w=m_Image.GetWidth();//获得图片的初始大小，为放大缩小功能做准备
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //强制调用ONDRAW函数
	}
}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;

	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();

	for (int k = 0; k < w; k++)
	{
		m_Image.m_pBits[0][10][k] = 0;//B
		m_Image.m_pBits[1][10][k] = 0;//G
		m_Image.m_pBits[2][10][k] = 0;//R


	}

	Invalidate(1); //强制调用ONDRAW函数



}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {
		MessageBox(_T("你还没有打开一个要保存的图像文件！"));
		return;
	}
	CString strFilter;
	//strFilter ="位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";   //
	strFilter = "所有文件|*.*||";   //

	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if (IDOK != dlg.DoModal())
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	//CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  获得文件名
	//if(dlg.m_ofn.nFileExtension == 0)     //获得文件扩展名
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
	// 图像保存
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image.m_pBits[0][j][k] = 0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image.m_pBits[1][j][k] = 0;//G


		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


//void CImage_ProcessingView::OnViewToolbar()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CImage_ProcessingView::Onreduceresolution()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i

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


	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}





void CImage_ProcessingView::Onintensitylevel128()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像

}


void CImage_ProcessingView::Onintensitylevel64()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::Onintensitylevel32()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::Onintensitylevel16()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::Onintensitylevel8()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::Onintensitylevel4()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度i
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::Onintensitylevel2()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::Ondifference()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w1 = m_Image.GetWidth();//获得图像宽度
	int h1 = m_Image.GetHeight();//获得图像高度
	MyImage_ m_Image2;//定义第二张图
	CFileDialog dlg(TRUE);//文件打开
	MessageBox(L"打开第二张图");//弹出对话框
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!m_Image2.IsNull()) m_Image2.Destroy();//判断是否已经有图片，有的话进行清除
		m_Image2.Load(dlg.GetPathName());//获得图片的地址，并且加载图片
		int w2 = m_Image2.GetWidth();//获得图像宽度
		int h2 = m_Image2.GetHeight();//获得图像高度
		if (w1 != w2 || h1 != h2)
		{
			MessageBox(L"图像大小不符");
			return;
		}
		for (int i = 0; i < w1; ++i)
		{
			for (int j = 0; j < h1; ++j)
			{
				//差分
				m_Image.m_pBits[0][j][i] = abs(m_Image.m_pBits[0][j][i] - m_Image2.m_pBits[0][j][i]);//B  
				m_Image.m_pBits[1][j][i] = abs(m_Image.m_pBits[1][j][i] - m_Image2.m_pBits[1][j][i]);//G
				m_Image.m_pBits[2][j][i] = abs(m_Image.m_pBits[2][j][i] - m_Image2.m_pBits[2][j][i]);//R
			}
		}
		Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
	}
}





void CImage_ProcessingView::OnAddNoiseElimination()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w1 = m_Image.GetWidth();//获得图像宽度
	int h1 = m_Image.GetHeight();//获得图像高度
	MyImage_ m_Image2;//定义第二张图
	CFileDialog dlg(TRUE);//文件打开
	MessageBox(L"打开第二张图");//弹出对话框
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!m_Image2.IsNull()) m_Image2.Destroy();//判断是否已经有图片，有的话进行清除
		m_Image2.Load(dlg.GetPathName());//获得图片的地址，并且加载图片
		int w2 = m_Image2.GetWidth();//获得图像宽度
		int h2 = m_Image2.GetHeight();//获得图像高度
		if (w1 != w2 || h1 != h2)
		{
			MessageBox(L"图像大小不符");
			return;
		}
		for (int i = 0; i < w1; ++i)
		{
			for (int j = 0; j < h1; ++j)
			{
				//差分
				m_Image.m_pBits[0][j][i] = (m_Image.m_pBits[0][j][i] + m_Image2.m_pBits[0][j][i]) / 2;//B  
				m_Image.m_pBits[1][j][i] = (m_Image.m_pBits[1][j][i] + m_Image2.m_pBits[1][j][i]) / 2;//G
				m_Image.m_pBits[2][j][i] = (m_Image.m_pBits[2][j][i] + m_Image2.m_pBits[2][j][i]) / 2;//R
			}
		}
		Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
	}
}


void CImage_ProcessingView::OnStatisticalHistogram()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获得图像宽度
	int h = m_Image.GetHeight();//获得图像高度
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

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像

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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	const int L = 256;
	int k = 0;
	int a[256];
	float Sk[256];
	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::OnHistogramSpecification()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	MyImage_ m_Image2;
	CFileDialog dlg(TRUE);
	MessageBox(L"打开第二张图");
	const int L = 256;
	int k = 0;
	int a[256], b[256];
	float Sk1[256], Sk2[256];
	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if (!m_Image2.IsNull()) m_Image2.Destroy();//判断是否已经有图片，有的话进行清除
		m_Image2.Load(dlg.GetPathName());//获得图片的地址，并且加载图片
		int w2 = m_Image2.GetWidth();//获得图像的宽度
		int h2 = m_Image2.GetHeight();//获得图像的高度


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

		//建立映射关系
		for (int i = 0; i < 256; i++)
		{
			int m = 0;
			float min_value = 1.0f;//float型最小差值
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
					m = j;//记录最小值位置
					min_value = now_value * 255;//不断更新最小差值
				}
			}
			Zk[i] = Sk1[m];//建立灰度映射表
		}

		//对个像素进行直方图规定化映射处理
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
	// TODO: 在此添加命令处理程序代码

	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();


	long i, j;					//i:行循环变量 ,j:列循环变量
	double dTmp;				//临时变量
								//w宽；h高
	long wid = 1, hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor = 0, heipor = 0;		//wid hei :2的幂次数

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//为指向时域的指针分配内存
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//为指向频域的指针分配内存


	//////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
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

	/////////初始化pTd//////////////
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = 0;
			pTd[i*wid + j].im = 0;
		}
	}

	/////////图像赋予pTd指针////////////////////////////
	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			pTd[j*wid + i].re = pow((double)-1, (double)(i + j))*m_Image.m_pBits[0][j][i];//（-1)^i+j移动变换中心
		}
	}
	++FftTime;



	if (FTResult)
	{
		delete[]FTResult;								//如果变换结果指针有效，删除内存
	}
	FTResult = new CplexNum[sizeof(CplexNum)*w*h];	//为变换结果重新分配内存
	//////////调用傅立叶变化函数Fourier////////////////////
	Fourier(pTd, w, h, pFd/*, this*/);

	/////////////保存结果/////////////

	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			FTResult[wid *i + j] = pTd[wid *i + j];
		}
	}

	////////////对数变换后显示结果/////////////////////////
	int **Ftmp;			//暂存二维数组wid*hei -> 【i】【j】
						//三维数组  是hei*wid -> 【j】【i】

						//////////////分配内存/////////////////////
	Ftmp = new int *[wid];
	double maxF(1);//变换后最大的系数
	int s(1);	//对数变换系数
	for (i = 0; i < wid; i++)
	{
		Ftmp[i] = new int[hei];
	}

	//////////////导入暂存二维数组///////////////
	for (int j = 0; j < hei; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			dTmp = pTd[j*wid + i].re*pTd[j*wid + i].re + pTd[j*wid + i].im*pTd[j*wid + i].im;
			dTmp = sqrt(dTmp) / 100;
			if (maxF < dTmp)
			{
				maxF = dTmp;//保存最大值
			}
			Ftmp[i][j] = dTmp;
		}
	}
	double maxx = 0;
	double v = 2;//底数
				 ///////////////对数变换///////////////////
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
	double pq = 255 / maxx;//占比例
	///////////////////返回至源图////////////////
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

	//////////////////回收暂存数组指针////////////////
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

	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	if (!FftTime) //判断图像是否为空
	{
		MessageBox(L"请先傅立叶变换！");
		return;
	}

	m_Image.Flag = 0;	//恢复FLAG
	--FftTime;

	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();


	double dTmp;				//临时变量
	long i, j;					//i:行循环变量 ,j:列循环变量
								//w宽；h高
	long wid = 1, hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor = 0, heipor = 0;		//wid hei :2的幂次数

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//为指向时域的指针分配内存
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//为指向频域的指针分配内存

													   //////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
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

	/////////初始化pTd//////////////
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = FTResult[i*wid + j].re;
			pTd[i*wid + j].im = -FTResult[i*wid + j].im;//共轭
		}
	}


	//////////调用傅立叶变化函数Fourier////////////////////
	Fourier(pTd, w, h, pFd);



	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			dTmp = pTd[i*wid + j].re;
			dTmp = pTd[i*wid + j].im;
			pTd[i*wid + j].re = pTd[i*wid + j].re / (double)(wid*hei);
			pTd[i*wid + j].im = -pTd[i*wid + j].im / (double)(wid*hei);//共轭
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

	///////////回收指针内存/////////////
	delete[]pTd;
	delete[]pFd;


	Invalidate(TRUE);
}


void CImage_ProcessingView::OnIdealpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(L"请先进行傅立叶变换！");
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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


	//回收指针内存
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(L"请先进行傅立叶变换！");
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	//制作模板
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



	//回收指针内存
	for (int i = 0; i < w; i++)
	{
		delete[]modul[i];
	}
	delete[]modul;

	//调用IFFT
	CImage_ProcessingView::OnIfft();

}



void CImage_ProcessingView::OnGaussianfilter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox(L"请先进行傅立叶变换！");
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	//制作模板
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



	//回收指针内存
	for (int i = 0; i < w; i++)
	{
		delete[]modul[i];
	}
	delete[]modul;

	//调用IFFT
	CImage_ProcessingView::OnIfft();
}


void CImage_ProcessingView::OnSaltPepper()
{
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	Dlg_SaltPepper dlg;//建立对话框对象
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

									 //判断是否输入有效的数字
		while (dlg.pepper < 0 || dlg.pepper>1 || dlg.salt < 0 || dlg.salt>1 ||
			(dlg.salt + dlg.pepper) > 1)
		{
			MessageBox(L"	 输入无效\n请重新输入有效的噪声概率");
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		int w = m_Image.GetWidth();//获取高度和宽度
		int h = m_Image.GetHeight();

		float p_a = dlg.salt;//获取噪声点的概率,p_a(黑),p_b（白）
		float p_b = dlg.pepper;


		float P_Sum = p_a + p_b;
		float xishu = 1 / P_Sum;
		float p_a_1 = p_a*xishu;
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				if (rand() / 32767.0 < P_Sum)//指定概率rand()产生随机的介于1-32767的数
				{
					if (rand() / 32767.0 < p_a_1)
					{
						m_Image.m_pBits[0][j][i] = 0;         //该像素点显示为黑色
						m_Image.m_pBits[1][j][i] = 0;
						m_Image.m_pBits[2][j][i] = 0;

					}
					else
					{
						m_Image.m_pBits[0][j][i] = 255;         //该像素点显示为白色
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
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();

	Dlg_MedianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		while (dlg.size % 2 == 0 || dlg.size<0 || dlg.size>w || dlg.size > h)
		{
			MessageBox(L"   输入模板尺寸无效\n请重新输入合适的正奇数值");
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

	//创建新三维数组，用于暂存新图！
	BYTE *** NewPicture = nullptr;
	NewPicture = new  BYTE **[3];//3个维度；分配内存  
	for (int i = 0; i < 3; i++)
	{
		NewPicture[i] = new  BYTE*[h];   //先H
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			NewPicture[i][j] = new BYTE[w];   //后W
		}
	}

	//暂存数组，求取中值
	int *B, *G, *R;
	B = new int[dlg.size*dlg.size];
	G = new int[dlg.size*dlg.size];
	R = new int[dlg.size*dlg.size];

	int sz;//数组下标

	for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//设定i，j合理的取值范围，防止超出图片范围
	{
		for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
		{
			sz = 0;
			for (int k = -((dlg.size - 1) / 2); k < (((dlg.size - 1) / 2) + 1); k++)//模板内循环
			{
				for (int kk = -((dlg.size - 1) / 2); kk < (((dlg.size - 1) / 2) + 1); kk++)
				{
					B[sz] = m_Image.m_pBits[0][j + k][i + kk];
					G[sz] = m_Image.m_pBits[1][j + k][i + kk];
					R[sz] = m_Image.m_pBits[2][j + k][i + kk];
					sz++;
				}
			}
			std::sort(B, B + dlg.size*dlg.size);//sort排序
			std::sort(G, G + dlg.size*dlg.size);
			std::sort(R, R + dlg.size*dlg.size);
			NewPicture[0][j][i] = B[(dlg.size*dlg.size - 1) / 2 + 1];
			NewPicture[1][j][i] = G[(dlg.size*dlg.size - 1) / 2 + 1];
			NewPicture[2][j][i] = R[(dlg.size*dlg.size - 1) / 2 + 1];
		}
		//double p;
		//p = (double)j / (double)(h - ((dlg.size - 1) / 2));
		//int k = p * 100;

		//((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
	}
	//((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

													  //将新图赋予源图
	for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//新图是没有初始化的!
	{
		for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
		{
			m_Image.m_pBits[0][j][i] = NewPicture[0][j][i];
			m_Image.m_pBits[1][j][i] = NewPicture[1][j][i];
			m_Image.m_pBits[2][j][i] = NewPicture[2][j][i];
		}
	}

	//回收指针
	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete[] NewPicture[i][j];//回收内存
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
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG

	if (addNoise < 2)
	{
		MessageBox(L"请先添加噪声！");
		return;
	}

	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();

	Dlg_MedianFilter dlg;
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

									 //判断是否输入有效的数字
		while (dlg.size % 2 == 0 || dlg.size<0 || dlg.size>w || dlg.size > h)
		{
			MessageBox(L"   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK == dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//创建新三维数组，用于暂存新图！
		BYTE *** NewPicture = nullptr;
		NewPicture = new  BYTE **[3];//3个维度；分配内存  
		for (int i = 0; i < 3; i++)
		{
			NewPicture[i] = new  BYTE*[h];   //先H
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{
				NewPicture[i][j] = new BYTE[w];   //后W
			}
		}

		//暂存数组，求取中值
		int *B, *G, *R;
		B = new int[dlg.size*dlg.size];
		G = new int[dlg.size*dlg.size];
		R = new int[dlg.size*dlg.size];

		int sz;//数组下标


		for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
			{
				//B
				for (int FilterSize = 3; FilterSize <= dlg.size; FilterSize += 2)
				{
					sz = 0;
					for (int k = -((FilterSize - 1) / 2); k < (((FilterSize - 1) / 2) + 1); k++)//模板内循环
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
					std::sort(B, B + FilterSize*FilterSize);//sort排序,注意第二个参数！！！
					for (int i = 0; i < FilterSize*FilterSize; i++)
					{
						sz = B[i];
					}

					NewPicture[0][j][i] = B[(FilterSize*FilterSize - 1) / 2 + 1];


					sz = B[(FilterSize*FilterSize - 1) / 2 + 1];
					sz = B[FilterSize*FilterSize - 1];
					sz = B[0];
					if ((B[(FilterSize*FilterSize - 1) / 2 + 1] != B[FilterSize*FilterSize - 1]) && (B[(FilterSize*FilterSize - 1) / 2 + 1] != B[0]))//如果中值非噪声
					{
						if ((m_Image.m_pBits[0][j][i] != B[FilterSize*FilterSize - 1]) && (m_Image.m_pBits[0][j][i] != B[0]))//如果中心非噪声
						{
							sz = m_Image.m_pBits[0][j][i];
							NewPicture[0][j][i] = m_Image.m_pBits[0][j][i];//输出原值

						}
						else
						{
							sz = B[(FilterSize*FilterSize - 1) / 2 + 1];
							NewPicture[0][j][i] = B[(FilterSize*FilterSize - 1) / 2 + 1];//输出中值
						}
						break;
					}
				}

				//G
				for (int FilterSize = 3; FilterSize <= dlg.size; FilterSize += 2)
				{
					sz = 0;
					for (int k = -((FilterSize - 1) / 2); k < (((FilterSize - 1) / 2) + 1); k++)//模板内循环
					{
						for (int kk = -((FilterSize - 1) / 2); kk < (((FilterSize - 1) / 2) + 1); kk++)
						{
							G[sz] = m_Image.m_pBits[1][j + k][i + kk];
							sz++;
						}
					}
					std::sort(G, G + FilterSize*FilterSize);
					NewPicture[1][j][i] = G[(FilterSize*FilterSize - 1) / 2 + 1];
					if ((G[(FilterSize*FilterSize - 1) / 2 + 1] != G[FilterSize*FilterSize - 1]) && (G[(FilterSize*FilterSize - 1) / 2 + 1] != G[0]))//如果中值非噪声
					{
						if ((m_Image.m_pBits[1][j][i] != G[FilterSize*FilterSize - 1]) && (m_Image.m_pBits[1][j][i] != G[0]))//如果中心非噪声
						{
							NewPicture[1][j][i] = m_Image.m_pBits[1][j][i];//输出原值

						}
						else
						{
							NewPicture[1][j][i] = G[(FilterSize*FilterSize - 1) / 2 + 1];//输出中值
						}
						break;
					}
				}

				//R
				for (int FilterSize = 3; FilterSize <= dlg.size; FilterSize++)
				{
					sz = 0;
					for (int k = -((FilterSize - 1) / 2); k < (((FilterSize - 1) / 2) + 1); k++)//模板内循环
					{
						for (int kk = -((FilterSize - 1) / 2); kk < (((FilterSize - 1) / 2) + 1); kk++)
						{
							R[sz] = m_Image.m_pBits[2][j + k][i + kk];
							sz++;
						}
					}
					std::sort(R, R + FilterSize*FilterSize);
					NewPicture[2][j][i] = R[(FilterSize*FilterSize - 1) / 2 + 1];
					if ((R[(FilterSize*FilterSize - 1) / 2 + 1] != R[FilterSize*FilterSize - 1]) && (R[(FilterSize*FilterSize - 1) / 2 + 1] != R[0]))//如果中值非噪声
					{
						if ((m_Image.m_pBits[2][j][i] != R[FilterSize*FilterSize - 1]) && (m_Image.m_pBits[2][j][i] != R[0]))//如果中心非噪声
						{
							NewPicture[2][j][i] = m_Image.m_pBits[2][j][i];//输出原值

						}
						else
						{
							NewPicture[2][j][i] = R[(FilterSize*FilterSize - 1) / 2 + 1];//输出中值
						}
						break;
					}
				}



			}
		}


		//将新图赋予源图
		for (int j = ((dlg.size - 1) / 2); j < h - ((dlg.size - 1) / 2); j++)//新图是没有初始化的!
		{
			for (int i = ((dlg.size - 1) / 2); i < w - ((dlg.size - 1) / 2); i++)
			{
				m_Image.m_pBits[0][j][i] = NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i] = NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i] = NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < h; j++)
			{
				delete[] NewPicture[i][j];//回收内存
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
	// TODO: 在此添加命令处理程序代码

	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	vector<vector<int>> H;//H分量
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	vector<vector<int>> S;//S分量
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	vector<vector<int>> I;//I分量
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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	const int L = 256;
	int k = 0;
	int a[3][256];
	float Sk[3][256];
	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}




void CImage_ProcessingView::OnIEqualization()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();

	vector<vector<vector<double>>> HSI;
	vector<vector<double>> vec;
	HSI.push_back(vec); HSI.push_back(vec); HSI.push_back(vec);
	//////////////////////////////////
	for (int i = 0; i < w; i++)
	{
		vector<double> vec;      //覆盖vec
		HSI[0].push_back(vec);//H
		HSI[1].push_back(vec);//S
		HSI[2].push_back(vec);//I
		for (int j = 0; j < h; j++)
		{
			double tmp;
			int R = m_Image.m_pBits[2][j][i];
			int G = m_Image.m_pBits[1][j][i];
			int B = m_Image.m_pBits[0][j][i];

			tmp = acos((double)(2 * R - G - B) / (0.001 + 2 * sqrt((double)(R - G)*(R - G) + (double)(R - B)*(G - B))));//0.001人为添加，防止除数为零
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
			m_Image.m_pBits[0][j][i] = HSI[2][i][j];//将vectorI分量赋值图片第一维度
		}
	}

	BYTE *lpSrc;	//指向源图的指针
	int i, j;
	int gray[256];	//灰度计数
	float probability[256];
	//int nrow = m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
								   //float probability[256];
	BYTE pixel;		//像素值
					//BYTE *lpDIBBits=(BYTE *)m_CImage.GetBits();//获得源图像起始位置
	memset(gray, 0, sizeof(gray));//初始化

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
	double   nRst[256];//映射表
	//int nrow = m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小

	w = m_Image.GetWidth();
	h = m_Image.GetHeight();
	CImage image3;			//缓存图
	image3.Create(w, h, 24);	//Create后需要delete
	lpNewDIBBits = (BYTE *)image3.GetBits();//获得image3最后一行的像素地址

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
	//转化为RGB
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
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::OnColorSegmentation()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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
	//// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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

	////考虑最理想的情况，先将图像全部置零
	//for (int i = 0; i < h; i++)
	//{
	//	for (int j = 0; j < w; j++)
	//	{
	//		int x = rand() % h;
	//		int y = rand() % w;
	//		if ((rand() % 3000) > 1)    //置零,但添加一定的噪声
	//		{
	//			for (int k = 0; k < 3; k++)
	//			{

	//				m_Image.m_pBits[k][i][j] = 0;

	//			}

	//		}
	//		else  //以一定概率加以一些噪声,噪声概率仅为1/3000
	//		{
	//			for (int k = 0; k < 3; k++)
	//			{

	//				m_Image.m_pBits[k][i][j] = 255;

	//			}

	//		}
	//	}
	//}

	//////给出四条待检测的直线
	//for (int k = 0; k < 3; k++) {
	//	for (int p = 10; p < int(h / 10); p += 3) {

	//		m_Image.m_pBits[k][1 * p][2 * p] = 255;

	//		m_Image.m_pBits[k][4 * p][2 * p] = 255;

	//		m_Image.m_pBits[k][7 * p][w - p - 10] = 255;//注意别越界

	//		m_Image.m_pBits[k][5 * p][w - 2 * p] = 255;//这里一定注意啊,w-2*p当p从0开始增加时,w-2*p =w,这就越界了

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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag = 0;	//恢复FLAG
	int z, avg_z;
	//Dlg_GaussNoisy *dlg = new Dlg_GaussNoisy;//建立对话框对象
	//dlg->Create(IDD_GaussNosiy, this);
	//dlg->ShowWindow(SW_SHOW);
	Dlg_GaussNoisy dlg;
	if (IDOK == dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据
		z = dlg.z;
		if (m_Image.IsNull()) return;//判断图像是否为空

		int w = m_Image.GetWidth();//获取高度和宽度
		int h = m_Image.GetHeight();
		int n = rand() % (z + 1);//指定概率rand()产生随机的介于0-z的数

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
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull())
	{
		OnFileOpen();
	}
	m_Image.Flag = 0;	//恢复FLAG
	int w = m_Image.GetWidth();//获取高度和宽度
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
