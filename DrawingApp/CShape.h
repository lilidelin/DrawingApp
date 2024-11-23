#pragma once
#include<afx.h>
#include <afxwin.h>

class CShape :public CObject {
public:

	virtual void Draw(CDC* pDC) = 0;//ªÊ÷∆
	virtual bool HitTest(CPoint point) = 0;//µ„ª˜≤‚ ‘
	virtual void Move(CPoint delta) = 0;//“∆∂Ø
};