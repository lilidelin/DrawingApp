#include"pch.h"
#include"CLine.h"

IMPLEMENT_SERIAL(CLine, CShape, 1)

void CLine::Draw(CDC* pDC) {
	pDC->MoveTo(m_startPoint);
	pDC->LineTo(m_endPoint);
}

bool CLine::HitTest(CPoint point) {
	CRect rect(m_startPoint, m_endPoint);
	rect.NormalizeRect();
	rect.InflateRect(2, 2);
	return rect.PtInRect(point);
}

void CLine::Move(CPoint delta)
{
	m_startPoint += delta;
	m_endPoint += delta;
}

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CString type = GetType();
		ar << type;
		ar << m_startPoint << m_endPoint;
	}
	else {
		ar >> m_startPoint >> m_endPoint;
	}
}

void CLine::SetEndPoint(CPoint point)
{
	m_endPoint = point;
}

CPoint CLine::GetStartPoint()
{
	return m_startPoint;
}

CPoint CLine::GetEndPoint()
{
	return m_endPoint;
}

CPoint CLine::CaculateOffset(CPoint point) {
	return CPoint(point.x - m_startPoint.x, point.y - m_startPoint.y);
}

