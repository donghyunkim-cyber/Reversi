#pragma once
struct POS
{
	int m_x;
	int m_y;
};

class CStack
{
private:
	POS* m_data[20];
	int m_size;

public:
	CStack()
	{
		m_size = 0;
	}

	void Push(POS* _data)
	{
		m_data[m_size] = _data;
		m_size++;
	}

	POS* Pop()
	{
		POS* temp = 0;

		m_size--;

		temp = m_data[m_size];

		m_data[m_size] = nullptr;

		return temp;
	}

	int GetSize()
	{
		return m_size;
	}

	POS* GetData(int _i)
	{
		return m_data[_i];
	}

	void Reset()
	{
		for (int i = 0; i < 20; i++)
		{
			m_data[i] = nullptr;
		}
	}

	~CStack()
	{

	}
};