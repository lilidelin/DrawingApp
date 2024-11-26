#pragma once
#include"CShape.h"
class CRectangle :public CShape {
public:
	DECLARE_SERIAL(CRectangle)

	CRectangle() = default;
	CRectangle(CPoint start,CPoint end):m_startPoint(start),m_endPoint(end){}

	void Draw(CDC* pDC)override;
	bool HitTest(CPoint point)override;
	void Move(CPoint delta)override;
	void Serialize(CArchive& ar)override;
	void SetEndPoint(CPoint point) override;
	CPoint GetStartPoint()override;
	CPoint GetEndPoint()override;
	CPoint CaculateOffset(CPoint point)override;
	virtual CString GetType() const override { return _T("Rectangle"); }
private:
	CPoint m_startPoint, m_endPoint;

};