#pragma once
#include<afx.h>
#include <afxwin.h>

class CShape :public CObject {
public:
	virtual void Draw(CDC* pDC) = 0;//绘制
	virtual bool HitTest(CPoint point) = 0;//点击测试
	virtual void Move(CPoint delta) = 0;//移动
	virtual void SetEndPoint(CPoint point) = 0;//设置终点
	virtual CPoint GetStartPoint() = 0;//返回起始点
	virtual CPoint GetEndPoint() = 0;//返回终点
	virtual CPoint CaculateOffset(CPoint point) = 0;//计算delta的值
	virtual CString GetType() const = 0;     // 返回图形类型
};