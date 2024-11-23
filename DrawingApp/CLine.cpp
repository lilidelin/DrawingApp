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
	rect.InflateRect(5, 5);
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
		ar << m_startPoint << m_endPoint;
	}
	else {
		ar >> m_startPoint >> m_endPoint;
	}
}