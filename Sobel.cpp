// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"

#include "kingimageDoc.h"
#include "kingimageView.h"
#include <ctgmath>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKingimageView

IMPLEMENT_DYNCREATE(CKingimageView, CScrollView)

BEGIN_MESSAGE_MAP(CKingimageView, CScrollView)
	//{{AFX_MSG_MAP(CKingimageView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PROCESS, OnProcess)
	ON_COMMAND(ID_any, Onany)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_SOBEL, &CKingimageView::OnSobel)
	ON_COMMAND(ID_USHARPMASKING, &CKingimageView::OnUnsharpmasking)
	ON_COMMAND(ID_LOGMASK7, &CKingimageView::OnLogmask7)
	ON_COMMAND(ID_LOGMASK11, &CKingimageView::OnLogmask11)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKingimageView construction/destruction

CKingimageView::CKingimageView()
{
	// TODO: add construction code here

}

CKingimageView::~CKingimageView()
{
}

BOOL CKingimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView drawing

void CKingimageView::OnDraw(CDC* pDC)
{
	CKingimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//	pDC->SetStretchBltMode(COLORONCOLOR);
	//	int x,y,bytes;
	if (pDoc->imagetype == PCX)
		(pDoc->_pcx)->draw(pDC);
	if (pDoc->imagetype == BMP)
		(pDoc->_bmp)->draw(pDC);
	if (pDoc->imagetype == GIF)
		(pDoc->_gif)->draw(pDC);
	if (pDoc->imagetype == JPG)
		(pDoc->_jpg)->draw(pDC);

}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView printing

BOOL CKingimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKingimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKingimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView diagnostics

#ifdef _DEBUG
void CKingimageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKingimageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKingimageDoc* CKingimageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKingimageDoc)));
	return (CKingimageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKingimageView message handlers



void CKingimageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CSize totalSize = CSize(::GetSystemMetrics(SM_CXSCREEN),
		::GetSystemMetrics(SM_CYSCREEN));
	CSize pageSize = CSize(totalSize.cx / 2, totalSize.cy / 2);
	CSize lineSize = CSize(totalSize.cx / 10, totalSize.cy / 10);

	SetScrollSizes(MM_TEXT, totalSize, pageSize, lineSize);
}

void CKingimageView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
}


void CKingimageView::OnProcess()
{

}

void CKingimageView::Onany()
{

}

void CKingimageView::OnSobel()
{
	CKingimageDoc* pDoc = GetDocument();

	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;


		double *Sx = new double[Wp *iHeight];
		double *Sy = new double[Wp*iHeight];
		double *Sobel = new double[Wp*iHeight];
		int Sobel_x[] = { -1,0,1,-2,0,2,-1,0,1 };
		int Sobel_y[] = { -1,-2,-1,0,0,0,1,2,1 };

		for (int i = 1; i < iHeight - 1; i++)
			for (int j = 1; j < iWidth - 1; j++)
			{
				Sx[i*Wp + j] = (pImg[(i - 1)*Wp + (j - 1)] * Sobel_x[0] + pImg[(i - 1)*Wp + j] * Sobel_x[1] + pImg[(i - 1)*Wp + (j + 1)] * Sobel_x[2] + pImg[i*Wp + (j - 1)] * Sobel_x[3] + pImg[i*Wp + j] * Sobel_x[4] + pImg[i*Wp + (j + 1)] * Sobel_x[5] + pImg[(i + 1)*Wp + (j - 1)] * Sobel_x[6] + pImg[(i + 1)*Wp + j] * Sobel_x[7] + pImg[(i + 1)*Wp + (j + 1)] * Sobel_x[8]);
				Sy[i*Wp + j] = (pImg[(i - 1)*Wp + (j - 1)] * Sobel_y[0] + pImg[(i - 1)*Wp + j] * Sobel_y[1] + pImg[(i - 1)*Wp + (j + 1)] * Sobel_y[2] + pImg[i*Wp + (j - 1)] * Sobel_y[3] + pImg[i*Wp + j] * Sobel_y[4] + pImg[i*Wp + (j + 1)] * Sobel_y[5] + pImg[(i + 1)*Wp + (j - 1)] * Sobel_y[6] + pImg[(i + 1)*Wp + j] * Sobel_y[7] + pImg[(i + 1)*Wp + (j + 1)] * Sobel_y[8]);
				Sobel[i*Wp + j] = (sqrt(Sx[i*Wp + j] * Sx[i*Wp + j] + Sy[i*Wp + j] * Sy[i*Wp + j]));
			}

		for (int i = 1; i < iHeight - 1; i++)
			for (int j = 1; j < iWidth - 1; j++)
			{
				if (Sobel[i*Wp + j] > 255)
					pImg[i*Wp + j] = 255;
				else
					pImg[i*Wp + j] = Sobel[i*Wp + j];
			}
	}
	OnDraw(GetDC());

}
