
// DrawingAppDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DrawingApp.h"
#include "DrawingAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDrawingAppDlg 对话框



CDrawingAppDlg::CDrawingAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWINGAPP_DIALOG, pParent),m_currentShape(nullptr),m_isDrawing(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawingAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawingAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDrawingAppDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDrawingAppDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDE_BUTTON_Line, &CDrawingAppDlg::OnBnClickedButtonLine)
	ON_BN_CLICKED(IDC_BUTTON_Circle, &CDrawingAppDlg::OnBnClickedButtonCircle)
END_MESSAGE_MAP()


// CDrawingAppDlg 消息处理程序

BOOL CDrawingAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CWnd* pDrawArea = GetDlgItem(IDC_DRAW_AREA);
	if (pDrawArea)
	{
		pDrawArea->GetWindowRect(&m_drawArea);
		ScreenToClient(&m_drawArea);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrawingAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


BOOL CDrawingAppDlg::OnEraseBkgnd(CDC* pDC)
{
	return FALSE; // 阻止擦除背景
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrawingAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawingAppDlg::OnPaint()
{
	CClientDC dc(this); // 用于绘制的设备上下文
	
	// 遍历所有图形并绘制
	for (CShape* shape : m_shapes)
	{
		shape->Draw(&dc);
	}

	// 如果正在绘制，绘制临时图形
	if (m_currentShape)
	{
		m_currentShape->Draw(&dc);
	}
}
void CDrawingAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_mode == None)return;
	if (m_drawArea.PtInRect(point))
	{
		m_isDrawing = true;//开始绘制
		switch (m_mode)
		{
		case None:
			break;
		case DrawLine:
			m_currentShape = new CLine(point, point);
			break;
		case DrawRectangle:
			break;
		case DrawCircle:
			m_currentShape = new CCircle(point, 0);//创建圆形
			break;
		default:
			break;
		}
		InvalidateRect(m_drawArea);
		UpdateWindow();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDrawingAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isDrawing && m_currentShape)
	{
		if (m_drawArea.PtInRect(point))
		{
			m_currentShape->SetEndPoint(point);
			InvalidateRect(m_drawArea);//触发重绘
			UpdateWindow();
		}
	}
	else if (m_isDragging&&m_currentDrag)
	{
		if (m_drawArea.PtInRect(point)) {
			CPoint delat(point.x - dragOffset.x, point.y - dragOffset.y);
			dragOffset = point;
			m_currentDrag->Move(delat);
			InvalidateRect(m_drawArea);
			UpdateWindow();
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CDrawingAppDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isDrawing)
	{
		m_isDrawing = false;//结束绘制

		if (m_drawArea.PtInRect(point))
		{
			m_currentShape->SetEndPoint(point);
			m_shapes.push_back(m_currentShape);
		}
		else {
			delete m_currentShape;//如果不在绘图区域，释放内存
		}
		m_currentShape = nullptr;//清空当前图形
		InvalidateRect(m_drawArea);
		UpdateWindow();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDrawingAppDlg::OnRButtonDown(UINT nFlags, CPoint point) {
	for (CShape* shape : m_shapes)
	{
		if (shape->HitTest(point)) {
			m_isDragging = true;
			m_currentDrag = shape;
			dragOffset = point;
			break;
		}
	}
	//InvalidateRect(m_drawArea);
	CDialogEx::OnRButtonDown(nFlags,point);
}

void CDrawingAppDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_isDragging = false;
	if (m_drawArea.PtInRect(point)) {
		CPoint delta(point.x - dragOffset.x, point.y - dragOffset.y);
		m_currentDrag->Move(delta);
		InvalidateRect(m_drawArea);
		UpdateWindow();
	}
	m_currentDrag = nullptr;
}

void CDrawingAppDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("dat"), nullptr, OFN_FILEMUSTEXIST, _T("Shape Files (*.dat)|*.dat|All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		CFile file(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		for (CShape* shape : m_shapes)
		{
			delete shape;
		}
		m_shapes.clear();//清空当前图形
		int shapeCount = 0;
		ar >> shapeCount;//加载文件中的图形数量
		for (int i = 0; i < shapeCount; ++i)
		{
			CShape* shape = new CLine(); // 假设只有 CLine 类型
			shape->Serialize(ar);
			m_shapes.push_back(shape);
		}
		ar.Close();
		file.Close();
		InvalidateRect(m_drawArea);
		AfxMessageBox(_T("Shapes loaded successfully!"));
	}
}

void CDrawingAppDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE, _T("dat"), _T("shapes.dat"), OFN_OVERWRITEPROMPT, _T("Shape Files (*.dat)|*.dat|All Files (*.*)|*.*||"));
	//创建保存文件对话框
	if (dlg.DoModal() == IDOK)
	{
		CFile file(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		int shapeCount = static_cast<int>(m_shapes.size());
		ar << shapeCount;
		for (CShape* shape : m_shapes)
		{
			shape->Serialize(ar);
		}
		ar.Close();
		file.Close();
		AfxMessageBox(_T("Shapes saved successfully!"));
	}
}

void CDrawingAppDlg::OnBnClickedButtonLine()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mode = DrawLine;
}


void CDrawingAppDlg::OnBnClickedButtonCircle()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mode = DrawCircle;
}
