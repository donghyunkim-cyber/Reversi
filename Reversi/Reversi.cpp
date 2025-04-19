#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "board.h"
#include <math.h>
#include "CStructure.h"
#include "resource.h"


#define BOARD_SIZE 8 
#define WIDTH 8
#define HEIGHT 8
#define WHITE 1
#define BLACK 0
#define STONE 64

// ������ Ŭ���� �̸�
TCHAR szWindowClass[] = _T("DesktopAPP");

// Ÿ��Ʋ
TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ������ Ŭ���� ���� , ���
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&wcex))
	{
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"), NULL);

		return 1;
	}

	hInst = hInstance;

	// �����츦 �����ϰ� ������ �ڵ鿡 �����Ѵ�
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		800,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"), NULL);

		return 1;
	}

	// �����츦 �����ְ�, �����츦 ������Ʈ�Ѵ�
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// �޼��� ť���� �޼����� ��´�
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // ���� �޼����� ��ȯ�Ѵ�
		DispatchMessage(&msg); // �޼����� ������ -> ���ν����� ȣ���Ѵ�
	}
	return (int)msg.wParam;
}

CBoard g_board;

CStack g_stack;

HBRUSH g_blackBrush, g_whiteBrush;

CCheck* g_check = 0;
wchar_t g_text[50] = { 0 };
wchar_t g_turn[50] = { 0 };
wchar_t g_txt[50] = { 0 };

void MakeBlank()
{
	// �߽��� x , y
	int c_x = 0;
	int c_y = 0;

	int gap = 80;

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			c_x = (gap * x) + 40;
			c_y = (gap * y) + 40;

			// ���ο� check(���� ������ �簢�� �ϳ�) �� �����
			CCheck* check = new CCheck(c_x, c_y);

			// ���� check�� g_board �� �ִ´�
			g_board.PutCheck(check);
		}
	}
}

void InitStone()
{
	CCheck* check = 0;

	int width = 3;
	int height = 3;

	int c_x = 0;
	int c_y = 0;
	int color = 0;

	// 3 , 3 ��ġ�� ���� ���´�
	// 4 , 4 ��ġ�� ���� ���´�
	// 3 , 4 ��ġ�� �������� ���´�
	// 4 , 3 ��ġ�� �������� ���´�


	// ���´� ( 3, 3, �� ) ;
	g_board.GetData(3, 3)->SetStone(new CStone(3 * 80 + 40, 3 * 80 + 40, 1));
	// ���´� ( 4, 4, �� ) ;
	g_board.GetData(4, 4)->SetStone(new CStone(4 * 80 + 40, 4 * 80 + 40, 1));
	// ���´� ( 3, 4, ������ ) ;
	g_board.GetData(3, 4)->SetStone(new CStone(3 * 80 + 40, 4 * 80 + 40, 0));
	// ���´� ( 4, 3, ������ ) ;
	g_board.GetData(4, 3)->SetStone(new CStone(4 * 80 + 40, 3 * 80 + 40, 0));

	/*
	//      
	while (height != 5)
	{
		while (width != 5)
		{
			c_x = g_board.GetData(width, height)->GetX();
			c_y = g_board.GetData(width, height)->GetY();
			width++;
		}
		height++;
	}

	c_x = g_board.GetData(3 , 3)->GetX();
	c_y = g_board.GetData(3 , 3)->GetY();

	// 3 , 3 = 250 , 250
	check = g_board.GetData(3 , 3);

	c_x = check->GetX();
	c_y = check->GetY();

	CStone* stone = new CStone(c_x , c_y , 1);

	check->SetStone(stone);






	for (int y = 3; y < 5; y++)
	{
		for (int x = 3; x < 5; x++)
		{
			check = g_board.GetData(x, y);

			c_x = check->GetX();
			c_y = check->GetY();

			if ((x == 4 && y == 3) || (x == 3 && y == 4))
			{
				color = 0;
			}
			else
			{
				color = 1;
			}

			// ���� �ϳ� �����
			CStone* stone = new CStone(c_x, c_y, color);

			// ���� ���� check �� set�Ѵ� (���� ���� �����ǿ� �ִ� �簢���� ���´�)
			check->SetStone(stone);

		}
	}
	*/
}

void InitPlayer()
{
	CPlayerBlack* black = new CPlayerBlack(true);
	CPlayerWhite* white = new CPlayerWhite(false);

	g_board.SetBlackPlayer(black);
	g_board.SetWhitePlayer(white);
}

// ���� �׸���
void RenderBoard(HDC _hdc)
{
	CCheck* check = 0;

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			check = g_board.GetData(x, y);

			check->Render(_hdc);
		}
	}
}

// ���� �׸���
void RenderStone(HDC _hdc, HBRUSH _white, HBRUSH _black)
{
	CStone* stone = 0;
	CCheck* check = 0;
	int color = 0;

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			check = g_board.GetData(x, y);
			stone = check->GetStone();

			if (stone == nullptr)
				continue;

			color = stone->GetColor();

			// ���� ���� �������̸�
			if (color == 0)
			{
				// �������� �׸���
				stone->Render(_hdc, _black);
			}
			else
			{
				// ���� ���� ����̸�
				if (color == 1)
				{
					// ������� �׸���
					stone->Render(_hdc, _white);
				}
			}
		}
	}
}

// Ŭ���� check�� �üũ���� �˷���
CCheck* GetCheck(int _x, int _y)
{
	return g_board.GetData(_x, _y);
}

// � ��ǥ���� �˷��ش�
int GetX(int _m_x)
{
	return _m_x / 80;
}

int GetY(int _m_y)
{
	return _m_y / 80;
}

// _x , _y �ڸ��� ���� �ִ��� üũ�Ѵ�
bool BlankConfirm(int _x, int _y)
{
	CStone* stone = 0;

	// check _x , _y �ڸ��� �ִ� ���� stone �̴�
	stone = g_board.GetData(_x, _y)->GetStone();

	if (stone == nullptr) // ���� ������
		return false;
	else // ���� ������
		return true;
}

// �� ������ Ȯ���� ( ���� ��ġ , ���� ��ġ 2 , ���� , ���� ���� ���� ���� , �ٸ����� ���� ã�� or ��ã��)
// ����
// Ŭ���� ��ġ �������� 8���� ����
// 
// ������ 0�̸� �������밢���� , 1�̸� ���� , 2�̸� ���������밢 , 3�̸� ���� , 4�̸� ������
// 5�̸� 
// CheckDirection

// 5 , 4 , 3
// 
// -1 , 0
int CheckTerms(int _x , int _y , int _dx , int _dy , int _color , bool _other)
{
	// ���� ���� ��ġ
	// _x , _y
	int next_x = _x + _dx;
	int next_y = _y + _dy;
	bool pass = false;
	bool find_same = false;

	if (next_x > 7 || next_y > 7)
		return 0;

	if (next_x < 0 || next_y < 0)
		return 0;

	CStone* stone = g_board.GetData(next_x, next_y)->GetStone();

	if (!stone) // ���̾�����
		return 0;
	else
	{
		if (stone->GetColor() == _color) // ���� ������ ������
		{
			find_same = true;
		}
		else // ���� ������ �ٸ���
		{
			pass = CheckTerms(next_x, next_y, _dx, _dy, _color , true);
		}
	}

	if (find_same && _other)
		return true;

	if (pass)
		return true;

	return false;
}

int SetColor(int _color)
{
	return _color;
}

int GetColor()
{
	int color = 0;

	if (g_board.GetBlackPlayer()->GetTurn())
		color = 0;
	else
		color = 1;
	return color;
}

#define DIR_MAX 8
// �Ǵ��� ���⼭ �Ѵ�
// ���� �������� �ϴ� �� �ֺ��� Ȯ���Ѵ�
bool CheckArounds(int _x , int _y , int _color)
{
	int dx[DIR_MAX] = { -1 , 0 , 1 , -1 , 1 , -1 , 0 , 1 };
	int dy[DIR_MAX] = { -1 , -1 , -1 , 0 , 0 , 1 , 1 , 1 };

	int dir = 0;
	int pass = 0;
	
	while (dir != DIR_MAX)
	{
		pass = pass + CheckTerms(_x, _y, dx[dir], dy[dir], _color , 0);
		dir++;
	}

	if (pass != 0)
		return pass;

	return false;
}

// ���� ���´�
CCheck* PutStone(CCheck* _check)
{
	CStone* stone = 0;
	int c_x = 0;
	int c_y = 0;
	int color = 0;

	c_x = _check->GetX();
	c_y = _check->GetY();

	// �ش� üũ�� ����������� ���� ����� ���´�
	if (_check->GetStone() == nullptr)
	{
		// ������ ���� ���� ���ʸ�
		if (g_board.GetBlackPlayer()->GetTurn())
		{
			color = 0;
			g_board.GetBlackPlayer()->ChangeTurn(false);
			g_board.GetWhitePlayer()->ChangeTurn(true);
		}
		else // ������� ���� ���ʸ�
		{
			color = 1;
			g_board.GetBlackPlayer()->ChangeTurn(true);
			g_board.GetWhitePlayer()->ChangeTurn(false);
		}

		// ���� �ϳ� ����� ( ���� check�� x, y�� ���� ���� �ø��� )
		stone = new CStone(c_x, c_y, color);

		_check->SetStone(stone);
	}
	return _check;
}

CStone* TakeStone(CCheck* _check)
{
	int x = _check->GetX() / 80;
	int y = _check->GetY() / 80;

	return g_board.GetData(x, y)->GetStone();
}

bool ConfirmThisDir(int _x, int _y , int _dx , int _dy , int _color , bool _other)
{
	CStone* now_stone = 0;
	bool pass = false;
	bool find_same = false;

	int now_x = _x + _dx;
	int now_y = _y + _dy;

	if (now_x > BOARD_SIZE - 1 || now_y > BOARD_SIZE - 1)
		return false;
	if (now_x < 0 || now_y < 0)
		return false;

	now_stone = g_board.GetData(now_x, now_y)->GetStone();

	if (now_stone) // ���� ������
	{
		if (now_stone->GetColor() == _color) 
		{
			find_same = true;
		}
		else // ������ �ٸ���
		{
			//POS* pos = new POS();
			//pos->m_x = now_x;
			//pos->m_y = now_y;

			//g_stack.Push(pos);

			pass = ConfirmThisDir(now_x , now_y , _dx , _dy , _color , true);
		}
	}
	else // ���� ������
	{
		return false;
	}

	if (_other && find_same)
		return true;

	if (pass)
	{
		g_board.GetData(now_x, now_y)->GetStone()->ChangeColor(_color);
		return true;
	}
		

	return false;
}

void FlipAroundStone(CStone* _stone , int _x , int _y)
{
	int color = _stone->GetColor(); // ���� ���� ��

	int dx[BOARD_SIZE] = { -1 , 0 , 1 , -1 , 1 , -1 , 0 , 1 };
	int dy[BOARD_SIZE] = { -1 , -1 , -1 , 0 , 0 , 1 , 1 , 1 };

	int dir = 0;

	while (dir != 8)
	{
		// �̹����� Ȯ���Ѵ�
		ConfirmThisDir(_x , _y , dx[dir] , dy[dir] , color , false);

		//if (change) // ���ÿ� �ִ°͵��� ������ �ٲ۴�
		//{
		//	int count = g_stack.GetSize();
		//	for (int i = 0; i < count; i++ )
		//	{
		//		POS* pos = 0;
		//		pos = g_stack.Pop();
		//		g_board.GetData(pos->m_x, pos->m_y)->GetStone()->ChangeColor(color);
		//	}
		//}
		//else
		//{
		//	for (int i = 0; i < g_stack.GetSize(); i++)
		//	{
		//		g_stack.Pop();
		//	}
		//}
		dir++;
	}
}



bool CheckAll()
{
	CStone* stone = 0;
	int check[2] = {0};
	int count = 0;
	
	// ����� �������� �Ѵ� Ȯ���Ѵ�
	while (count != 2)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				stone = g_board.GetData(i , j)->GetStone();

				if (!stone)
				{
					check[count] += CheckArounds(i , j , count);
				}
			}
		}
		count++;
	}
	// ����� , ������ �Ѵ� ���� �� ������
	if (!check[0] && !check[1])
	{
		return true;
	}
	else
	{
		if (g_board.GetBlackPlayer()->GetTurn())
		{
			if (check[0] == 0) // �������� ���� �� ������
			{
				g_board.GetBlackPlayer()->ChangeTurn(false);
				g_board.GetWhitePlayer()->ChangeTurn(true);
				MessageBox(NULL, _T("�������� ���� �� ��� ������� ������ �ٲߴϴ�"),
					_T("Windows Desktop Guided Tour"), NULL);
			}
		}

		if (g_board.GetWhitePlayer()->GetTurn())
		{
			if (check[1] == 0) // ������� ���� �� ������
			{
				g_board.GetBlackPlayer()->ChangeTurn(true);
				g_board.GetWhitePlayer()->ChangeTurn(false);
				MessageBox(NULL, _T("������� ���� �� ��� ���������� ������ �ٲߴϴ�"),
					_T("Windows Desktop Guided Tour"), NULL);
			}
		}
	}
	return false;
}

// check �ǿ� ���� ����
void CountStone()
{
	CCheck* check = 0;
	int black_count = 0;
	int white_count = 0;

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			check = g_board.GetData(x, y);

			if (check->GetStone() == nullptr)
				continue;

			if (check->GetStone()->GetColor() == 0)
			{
				black_count = black_count + 1;
			}
			else
			{
				if (check->GetStone()->GetColor() == 1)
				{
					white_count = white_count + 1;
				}
			}
		}
	}
	g_board.GetBlackPlayer()->AddStoneNum(black_count);
	g_board.GetWhitePlayer()->AddStoneNum(white_count);
}

// �������� ������ ���� ���� �׸��� ������������ �˷��ش�
void ShowStatement(HDC _hdc)
{
	int black = g_board.GetBlackPlayer()->GetStoneNum();
	int white = g_board.GetWhitePlayer()->GetStoneNum();

	swprintf_s(g_text, 50, L"���� : %d  ,  ��� : %d", black, white);
	TextOut(_hdc, 20, 660, g_text, wcslen(g_text));

	if (g_board.GetBlackPlayer()->GetTurn() == true)
	{
		swprintf_s(g_turn, 50, L"������ �����Դϴ�.");
		TextOut(_hdc, 20, 680, g_turn, wcslen(g_turn));
	}
	if (g_board.GetWhitePlayer()->GetTurn() == true)
	{
		swprintf_s(g_turn, 50, L"��� �����Դϴ�.");
		TextOut(_hdc, 20, 680, g_turn, wcslen(g_turn));
	}
}

void ShowWinner(HDC _hdc , bool _end)
{
	int black = g_board.GetBlackPlayer()->GetStoneNum();
	int white = g_board.GetWhitePlayer()->GetStoneNum();

	if (_end)
	{
		if (black > white) // ������ �̰�����
		{
			swprintf_s(g_txt, 50, L"���� ���Դϴ�!");
			TextOut(_hdc, 20, 700, g_txt, wcslen(g_txt));
		}
		else
		{
			swprintf_s(g_txt, 50, L"��� ���Դϴ�!");
			TextOut(_hdc, 20, 700, g_txt, wcslen(g_txt));
		}
	}
}

// �޴� ���� ���� �����ϱ⸦ Ŭ���ϸ�
// �� ó�� ȭ��� �����ϰ� �����
// �� ĭ�� �ִ� ������ ��� ���ְ�,
// 3 , 3 �� ���� ����
// 4 , 4 �� ���� ����
// 3 , 4 �� �������� ����
// 4 , 3 �� �������� ���´�
void ReStart()
{
	// �� ĭ�� �ִ� ��� ���� ���ش�
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			g_board.GetData(j , i)->SetStone(nullptr);
		}
	}
	
	// ���´� ( 3, 3, �� ) ;
	g_board.GetData(3, 3)->SetStone(new CStone(3 * 80 + 40, 3 * 80 + 40, 1));
	// ���´� ( 4, 4, �� ) ;
	g_board.GetData(4, 4)->SetStone(new CStone(4 * 80 + 40, 4 * 80 + 40, 1));
	// ���´� ( 3, 4, ������ ) ;
	g_board.GetData(3, 4)->SetStone(new CStone(3 * 80 + 40, 4 * 80 + 40, 0));
	// ���´� ( 4, 3, ������ ) ;
	g_board.GetData(4, 3)->SetStone(new CStone(4 * 80 + 40, 3 * 80 + 40, 0));

	g_board.GetBlackPlayer()->MyTurn();
	g_board.GetWhitePlayer()->YourTurn();

}

// ��� �ð��� ���Խð� (90��) ������ �߰��ð��� �� ������ ������ �����ڰ� �Ǵ������� ������
// ����� �� ���� ���� �� , ����� ���� ���� �� , ����� ������ ���º��̴�

// ���� 45��, �Ĺ� 45�� �� 90������ ���� ����ȴ�. 
// ������ ��Ⱑ �ߴܵǴ� �ð��� �����ؼ� �߰� �ð��� ��� ���� 5�п� ������ �� �ִ�. 
// ���д� ���� �� ���ڸ� �������� ��������. 
// ��� ����� ������ �ֽ��� �����Ѵ�. 
// ���� ����� ��Ģ�� ���� ����
// ��ʸ�Ʈ������ ��,�Ĺ��� ���� ������ ��� ���� ���� 15��, �Ĺ� 15���� �ο��Ѵ�. 
// ���忡���� �ºΰ� ���� �ʴ� ��� �º������ ���и� ������

// ������� ���� �����ε� 
//		�������� ���� �ڸ��� ������ (  why : ������ üũ? ) 
//			���������� �򵹷� �ѱ�ٰ� �޼��� �ڽ��� ����
// �������� ���� �����ε� 
//		���� ���� �ڸ��� ������ 
//			�򵹿��� �������� �ѱ�ٰ� �޼��� �ڽ��� ����

// �޽����� ������ ȣ��ȴ�
// ���� �޽����� ���� switch ���� ó���ȴ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int x;
	int y;

	int m_x;
	int m_y;

	bool end = false;
	bool checkBlack = false;
	bool checkwhite = false;

	switch (message)
	{
	case WM_CREATE:

		// 8 x 8 �������� �����
		MakeBlank();

		// ó�� �� 4���� ���´�
		InitStone();

		// �������� ���� �÷��̾�� ���� ���� �÷��̾ �����
		InitPlayer();

		g_blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		g_whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// ���� �׸���
		RenderBoard(hdc);

		// ���� �׸���
		RenderStone(hdc, g_whiteBrush, g_blackBrush);

		// ���� ������ ����
		CountStone();

		end = CheckAll();

		ShowWinner(hdc , end);

		// ���� ���ھ�� �������� ������ �����ش�
		ShowStatement(hdc);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(g_blackBrush);
		DeleteObject(g_whiteBrush);
		PostQuitMessage(0);
		break;

		// ���콺 ���ʹ�ư���� ��������
	case WM_LBUTTONUP:

		m_x = LOWORD(lParam);
		m_y = HIWORD(lParam);

		// � ��ǥ���� ��ǥ��ȣ�� �˷��ش�
		x = GetX(m_x);
		y = GetY(m_y);

		// �ٵ��� �ۿ� ���콺�� �ΰ� Ŭ���Ҷ� ������ ���°��� �����ִ� ��
		if (x > BOARD_SIZE - 1 || y > BOARD_SIZE - 1)
		{
			break;
		}
		if (x < 0 || y < 0)
		{
			break;
		}

		// x , y check �ڸ��� ���� �ִ��� Ȯ���Ѵ�
		// blank = ��ĭ
		// confirm = Ȯ���Ѵ�
		// ��ĭ�� Ȯ���ؼ� ���̶�� ����� ��´�
		if (BlankConfirm(x, y))
			break; // ���� ������ ���� �������ϰ��Ѵ� -> case���� �������´�

		// ���̾�����
		// �ֺ��� üũ�ϰ� üũ�� ������ ������ �ִ�
		if (CheckArounds(x, y , GetColor()))
		{
			CCheck* check = 0;
			CStone* stone = 0;

			// ���� ���´�
			check = PutStone(GetCheck(x , y));

			// ���� ���� ���� ���� �����´�
			stone = check->GetStone();
			//stone = TakeStone(check);

			// ���� ������ �ٲ��ش�
			// ���� ���� �������� �ֺ��� ���� �����´�
			//ChangeColor()
			FlipAroundStone(stone , x , y);
		}

		InvalidateRgn(hWnd, NULL, TRUE);

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_FILEGAMERESTART:

			// ��� ���� ó�� ����ȭ��� ���� �����Ѵ�
			ReStart();

			// restart ���� �ʱ�ȭ �� ���� �׷��ش�
			InvalidateRgn(hWnd, NULL, TRUE); 
			MessageBox(hWnd, _T("������ ���ν����մϴ�"), _T("������ ���� ����"), MB_OK);
			break;

		case ID_FILEEXIT:
			MessageBox(hWnd, _T("������ �����մϴ�"), _T("���� ����"), MB_OK);
			PostQuitMessage(0);
			break;
		default:
			break;
		}

		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}