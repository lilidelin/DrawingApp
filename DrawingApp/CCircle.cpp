#include"pch.h"
#include"CCircle.h"
#include"math.h"
IMPLEMENT_SERIAL(CCircle, CShape, 1)

void CCircle::Draw(CDC* pDC) {
	pDC->Ellipse(m_center.x - m_radius, m_center.y - m_radius
		, m_center.x + m_radius, m_center.y + m_radius);
}

bool CCircle::HitTest(CPoint point) {
	int dx = point.x - m_center.x;
	int dy = point.y - m_center.y;
	return dx * dx + dy * dy <= m_radius * m_radius;
}

void CCircle::Move(CPoint delta)
{
	m_center += delta;
}

void CCircle::SetEndPoint(CPoint point)
{
	m_radius = static_cast<int>(sqrt(pow(point.x - m_center.x, 2)
		+ pow(point.y - m_center.y, 2)));
}

CPoint CCircle::GetStartPoint()
{
	return m_center;
}

CPoint CCircle::GetEndPoint()
{
	return m_center;
}

CPoint CCircle::CaculateOffset(CPoint point)
{
	return CPoint();
}
