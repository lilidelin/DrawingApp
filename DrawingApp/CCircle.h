#pragma once
#include"CShape.h"
class CCircle:public CShape {
public:
	DECLARE_SERIAL(CCircle)
public:
	CCircle() = default;
	CCircle(CPoint center,int radius):m_center(center),m_radius(radius){}

	void Draw(CDC* pDC) override;
	bool HitTest(CPoint point) override;
	void Move(CPoint point) override;
	void SetEndPoint(CPoint point) override;
	CPoint GetStartPoint() override;
	CPoint GetEndPoint() override;
	CPoint CaculateOffset(CPoint point) override;
private:
	CPoint m_center;
	int m_radius;
};