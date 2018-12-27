#include "StdAfx.h"
#include "Fourier.h"
#include "FastFourierTran.h"
#include "MainFrm.h"

void Fourier(CplexNum *pTd, int wi, int he, CplexNum * pFd)
{
	int i, j;					//ѭ�����Ʊ���
	int wid = 1, hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor = 0, heipor = 0;		//wid hei :2���ݴ���

    //////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
	while (wid * 2 <= wi)
	{
		wid *= 2;
		widpor++;
	}
	while (hei * 2 <= he)
	{
		hei *= 2;
		heipor++;
	}

	/////////////X����FFT////////////////
	for (i = 0; i<hei; i++)
	{
		FastFourierTran(&pTd[wid*i], &pFd[wid*i], widpor);
	}

	///////////////����ת��///////////
	for (i = 0; i<hei; i++)
		for (j = 0; j<wid; j++)
			pTd[hei * j + i] = pFd[wid *i + j];

	/////////////Y����һάFFT////////////////
	for (j = 0; j<wid; j++)
	{
		FastFourierTran(&pTd[j*hei], &pFd[hei*j], heipor);

	}

	////////////pFd�洢�˶���Ϊ����Ҷ�任�Ľ��������Ҫת�û�������pTd/////////
	for (i = 0; i<hei; i++)
		for (j = 0; j<wid; j++)
			pTd[wid *i + j] = pFd[hei *j + i];

	memcpy(pTd, pFd, sizeof(CplexNum)*hei*wid);//���任���ݴ��ԭ�ڴ�ռ�
}