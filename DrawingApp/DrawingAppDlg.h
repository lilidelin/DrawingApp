
// DrawingAppDlg.h: 头文件
//

#pragma once
#include"CLine.h"
#include"CCircle.h"
#include"CRectangle.h"
#include<vector>


// CDrawingAppDlg 对话框
class CDrawingAppDlg : public CDialogEx
{
// 构造
public:
	CDrawingAppDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWINGAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
	std::vector<CShape*> m_shapes;//储存所有图形
	CShape* m_currentShape;  //当前正在绘制的图形
	CShape* m_currentDrag;//当前正在拖动的图形
	CRect m_drawArea;   //绘图区域
	CPoint dragOffset;  //相对起点偏移量
	enum Mode { None, DrawLine, DrawRectangle, DrawCircle } m_mode = None; // 当前模式
	bool m_isDrawing;  //是否正在绘制
	bool m_isDragging;//是否正在拖动
public:
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLine();
	afx_msg void OnBnClickedButtonCircle();
	afx_msg void OnBnClickedButtonRectangle();
};
