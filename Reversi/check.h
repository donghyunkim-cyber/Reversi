#pragma once
class CCheck
{
private:
	CStone* m_stone;

	int m_x;
	int m_y;
	int m_r;

	bool m_hint;

public:
	CCheck(int _x , int _y)
	{
		m_x = _x;
		m_y = _y;
		m_r = 40;
		m_hint = false;
	}

	void Render(HDC _hdc)
	{
		Rectangle(_hdc, m_x - m_r, m_y - m_r, m_x + m_r, m_y + m_r);
	}

	void PutHint(bool _hint)
	{
		m_hint = _hint;
	}

	bool GetHint()
	{
		return m_hint;
	}

	int GetX()
	{
		return m_x;
	}

	int GetY()
	{
		return m_y;
	}

	int GetR()
	{
		return m_r;
	}

	void SetStone(CStone* _stone)
	{
		m_stone = _stone;
	}

	CStone* GetStone()
	{
		return m_stone;
	}

	~CCheck()
	{

	}


};