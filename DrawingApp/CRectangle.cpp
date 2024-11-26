#include"pch.h"
#include"CRectangle.h"

IMPLEMENT_SERIAL(CRectangle, CShape, 1)
void CRectangle::Draw(CDC* pDC)
{
	CRect rect(m_startPoint, m_endPoint);
	pDC->Rectangle(rect);
}

bool CRectangle::HitTest(CPoint point)
{
	CRect rect(m_startPoint, m_endPoint);
	rect.NormalizeRect();
	return rect.PtInRect(point);
}

void CRectangle::Move(CPoint delta)
{
	m_startPoint += delta;
	m_endPoint += delta;
}

void CRectangle::Serialize(CArchive& ar)
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

void CRectangle::SetEndPoint(CPoint point)
{
	m_endPoint = point;
}

CPoint CRectangle::GetStartPoint()
{
	return m_startPoint;
}

CPoint CRectangle::GetEndPoint()
{
	return m_endPoint;
}

CPoint CRectangle::CaculateOffset(CPoint point)
{
	return CPoint();
}
