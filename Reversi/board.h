#pragma once
#include "stone.h"
#include "check.h"
#include "player_black.h"
#include "player_white.h"

class CBoard
{
private:
	CCheck* check[8][8];
	CPlayerWhite* player_white;
	CPlayerBlack* player_black;

	int m_size_x;
	int m_size_y;

public:
	CBoard()
	{
		m_size_x = 0;
		m_size_y = 0;
	}

	void PutCheck(CCheck* _check)
	{
		if (m_size_x != 8)
		{
			check[m_size_x][m_size_y] = _check;
			m_size_x++;
		}

		if (m_size_x == 8)
		{
			m_size_x = 0;
			m_size_y++;
		}

	}

	void SetBlackPlayer(CPlayerBlack* _black)
	{
		player_black = _black;
	}

	void SetWhitePlayer(CPlayerWhite* _white)
	{
		player_white = _white;
	}

	CPlayerBlack* GetBlackPlayer()
	{
		return player_black;
	}

	CPlayerWhite* GetWhitePlayer()
	{
		return player_white;
	}

	CCheck* GetData(int _x, int _y)
	{
		return check[_x][_y];
	}

	void SetTurn(int _color)
	{
		if (_color == 1)
		{
			player_white->MyTurn();
			player_black->YourTurn();
		}
		else
		{
			player_white->YourTurn();
			player_black->MyTurn();
		}
	}

	~CBoard()
	{

	}
};