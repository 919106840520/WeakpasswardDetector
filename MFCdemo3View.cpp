
// MFCdemo3View.cpp: CMFCdemo3View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCdemo3.h"
#endif

#include "MFCdemo3Doc.h"
#include "MFCdemo3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCdemo3View

IMPLEMENT_DYNCREATE(CMFCdemo3View, CView)

BEGIN_MESSAGE_MAP(CMFCdemo3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCdemo3View 构造/析构

CMFCdemo3View::CMFCdemo3View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCdemo3View::~CMFCdemo3View()
{
}

BOOL CMFCdemo3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCdemo3View 绘图

void CMFCdemo3View::OnDraw(CDC* /*pDC*/)
{
	CMFCdemo3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCdemo3View 打印

BOOL CMFCdemo3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCdemo3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCdemo3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCdemo3View 诊断

#ifdef _DEBUG
void CMFCdemo3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCdemo3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCdemo3Doc* CMFCdemo3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCdemo3Doc)));
	return (CMFCdemo3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCdemo3View 消息处理程序
