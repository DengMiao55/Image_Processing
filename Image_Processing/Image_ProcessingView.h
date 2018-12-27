
// Image_ProcessingView.h : CImage_ProcessingView 类的接口
//

#pragma once
#include "MyImage_.h"
#include "atlimage.h"
#include "Image_ProcessingDoc.h"
#include "CplexNum.h"
#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "gdiplus.h"

using namespace cv;
using namespace Gdiplus;

class CImage_ProcessingView : public CScrollView
{
private: // 仅从序列化创建
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView);

// 特性
public:
	CImage_ProcessingDoc* GetDocument() const;
	int w;
	int h;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:
	MyImage_ m_Image;
	MyImage_ image,image2;
	Mat img;
	afx_msg void OnDrawline();
	afx_msg void OnFileSaveAs();
	afx_msg void OnShowred();
//	afx_msg void OnViewToolbar();
	afx_msg void Onreduceresolution();
	afx_msg void Onintensitylevel128();
	afx_msg void Onintensitylevel64();
	afx_msg void Onintensitylevel32();
	afx_msg void Onintensitylevel16();
	afx_msg void Onintensitylevel8();
	afx_msg void Onintensitylevel4();
	afx_msg void Onintensitylevel2();
	afx_msg void Ondifference();
	afx_msg void OnAddNoiseElimination();
	afx_msg void OnStatisticalHistogram();
	afx_msg void OnHistogramEqualization();
	afx_msg void OnHistogramSpecification();
	int FftTime ;
	CplexNum *FTResult ;//傅立叶变换结果
	//void SetProgress(int);//设置进度条
	afx_msg void OnFourier();
	afx_msg void OnIdealpass();
	
	afx_msg void OnButterworthpass();
	afx_msg void OnIfft();
	afx_msg void OnGaussianfilter();
	afx_msg void OnSaltPepper();
	int addNoise;
	afx_msg void OnMedianfilter();
	afx_msg void OnAdaptivemedianfilter();
	afx_msg void OnRgbR();
	afx_msg void OnRgbG();
	afx_msg void OnRgbB();
	afx_msg void OnHsiH();
	afx_msg void OnHsiS();
	afx_msg void OnHsiI();
	afx_msg void OnRgbEqualization();
	afx_msg void OnIEqualization();
	afx_msg void OnColorSegmentation();
	int MouseX, MouseY, MouseX2, MouseY2;
	afx_msg void OnDetectStraightline();
	afx_msg void OnGaussnoisy();
	afx_msg void OnRandPoint();
};

#ifndef _DEBUG  // Image_ProcessingView.cpp 中的调试版本
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

