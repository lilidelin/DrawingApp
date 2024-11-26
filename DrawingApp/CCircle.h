#pragma once
#include"CShape.h"
class CCircle:public CShape {
	void Draw(CDC* pDC) override;
	bool HitTest(CPoint point) override;
	void Move(CPoint point) override;
	void SetEndPoint(CPoint point) override;
	CPoint GetStartPoint() override;
	CPoint GetEndPoint() override;
	CPoint CaculateOffset(CPoint point) override;
};