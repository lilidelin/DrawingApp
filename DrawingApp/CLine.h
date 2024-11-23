#pragma once
#include"CShape.h"
class CLine :public CShape {
public:
	DECLARE_SERIAL(CLine)

public:
	CPoint m_startPoint, m_endPoint;

	CLine() = default;
	CLine(CPoint start, CPoint end) :m_startPoint(start), m_endPoint(end) {}
	void Draw(CDC* pDC)override;
	bool HitTest(CPoint point)override;
	void Move(CPoint delta)override;
	void Serialize(CArchive& ar)override;
};