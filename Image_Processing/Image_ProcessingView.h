
// Image_ProcessingView.h : CImage_ProcessingView ��Ľӿ�
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
private: // �������л�����
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView);

// ����
public:
	CImage_ProcessingDoc* GetDocument() const;
	int w;
	int h;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	CplexNum *FTResult ;//����Ҷ�任���
	//void SetProgress(int);//���ý�����
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

#ifndef _DEBUG  // Image_ProcessingView.cpp �еĵ��԰汾
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

