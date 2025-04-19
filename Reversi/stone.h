#pragma once
class CStone
{

private:
	int m_x;
	int m_y;
	int m_r;
	int m_color;

public:
	CStone(int _x , int _y , int _color)
	{
		m_x = _x;
		m_y = _y;
		m_r = 40;
		m_color = _color;
	}

	int GetColor()
	{
		return m_color;
	}

	void Render(HDC _hdc, HBRUSH _brush)
	{
		HBRUSH hBrush = (HBRUSH)SelectObject(_hdc, _brush);
		Ellipse(_hdc, m_x - m_r, m_y - m_r, m_x + m_r, m_y + m_r);
		SelectObject(_hdc, hBrush);
	}

	void ChangeColor(int _color)
	{
		m_color = _color;
	}

	~CStone()
	{

	}
};