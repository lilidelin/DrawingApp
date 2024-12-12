#pragma once
#include<afx.h>
#include <afxwin.h>

class CShape :public CObject {
public:
	virtual void Draw(CDC* pDC) = 0;//����
	virtual bool HitTest(CPoint point) = 0;//�������
	virtual void Move(CPoint delta) = 0;//�ƶ�
	virtual void SetEndPoint(CPoint point) = 0;//�����յ�
	virtual CPoint GetStartPoint() = 0;//������ʼ��
	virtual CPoint GetEndPoint() = 0;//�����յ�
	virtual CPoint CaculateOffset(CPoint point) = 0;//����delta��ֵ
	virtual CString GetType() const = 0;     // ����ͼ������
};