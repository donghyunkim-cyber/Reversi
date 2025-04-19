#pragma once
class CPlayerWhite
{
private:
	int m_stonenum;
	bool m_turn;

public:
	CPlayerWhite(bool _turn)
	{
		m_stonenum = 0;
		m_turn = _turn;
	}

	int GetStoneNum()
	{
		return m_stonenum;
	}

	bool GetTurn()
	{
		return m_turn;
	}

	void ChangeTurn(bool _turn)
	{
		m_turn = _turn;
	}

	void MyTurn()
	{
		m_turn = true;
	}

	void YourTurn()
	{
		m_turn = false;
	}

	void AddStoneNum(int _num)
	{
		m_stonenum = _num;
	}

	~CPlayerWhite()
	{

	}
};