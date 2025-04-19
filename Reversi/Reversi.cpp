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

// 윈도우 클래스 이름
TCHAR szWindowClass[] = _T("DesktopAPP");

// 타이틀
TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 윈도우 클래스 정의 , 등록
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

	// 윈도우를 생성하고 윈도우 핸들에 저장한다
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

	// 윈도우를 보여주고, 윈도우를 업데이트한다
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// 메세지 큐에서 메세지를 얻는다
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // 얻은 메세지를 변환한다
		DispatchMessage(&msg); // 메세지를 보낸다 -> 프로시저를 호출한다
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
	// 중심점 x , y
	int c_x = 0;
	int c_y = 0;

	int gap = 80;

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			c_x = (gap * x) + 40;
			c_y = (gap * y) + 40;

			// 새로운 check(돌이 놓여질 사각형 하나) 를 만든다
			CCheck* check = new CCheck(c_x, c_y);

			// 만든 check를 g_board 에 넣는다
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

	// 3 , 3 위치에 흰돌을 놓는다
	// 4 , 4 위치에 흰돌을 놓는다
	// 3 , 4 위치에 검은돌을 놓는다
	// 4 , 3 위치에 검은돌을 놓는다


	// 놓는다 ( 3, 3, 흰돌 ) ;
	g_board.GetData(3, 3)->SetStone(new CStone(3 * 80 + 40, 3 * 80 + 40, 1));
	// 놓는다 ( 4, 4, 흰돌 ) ;
	g_board.GetData(4, 4)->SetStone(new CStone(4 * 80 + 40, 4 * 80 + 40, 1));
	// 놓는다 ( 3, 4, 검은돌 ) ;
	g_board.GetData(3, 4)->SetStone(new CStone(3 * 80 + 40, 4 * 80 + 40, 0));
	// 놓는다 ( 4, 3, 검은돌 ) ;
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

			// 돌을 하나 만든다
			CStone* stone = new CStone(c_x, c_y, color);

			// 만든 돌을 check 에 set한다 (만든 돌을 게임판에 있는 사각형에 놓는다)
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

// 판을 그린다
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

// 돌을 그린다
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

			// 돌의 색이 검은색이면
			if (color == 0)
			{
				// 검은돌을 그린다
				stone->Render(_hdc, _black);
			}
			else
			{
				// 돌의 색이 흰색이면
				if (color == 1)
				{
					// 흰색돌을 그린다
					stone->Render(_hdc, _white);
				}
			}
		}
	}
}

// 클릭한 check가 어떤체크인지 알려줌
CCheck* GetCheck(int _x, int _y)
{
	return g_board.GetData(_x, _y);
}

// 어떤 좌표인지 알려준다
int GetX(int _m_x)
{
	return _m_x / 80;
}

int GetY(int _m_y)
{
	return _m_y / 80;
}

// _x , _y 자리에 돌이 있는지 체크한다
bool BlankConfirm(int _x, int _y)
{
	CStone* stone = 0;

	// check _x , _y 자리에 있는 돌이 stone 이다
	stone = g_board.GetData(_x, _y)->GetStone();

	if (stone == nullptr) // 돌이 없으면
		return false;
	else // 돌이 있으면
		return true;
}

// 이 방향을 확인해 ( 현재 위치 , 현재 위치 2 , 방향 , 지금 놓을 돌의 색깔 , 다른색의 돌을 찾다 or 못찾다)
// 방향
// 클릭한 위치 기준으로 8개의 방향
// 
// 방향이 0이면 왼쪽위대각방향 , 1이면 위쪽 , 2이면 오른쪽위대각 , 3이면 왼쪽 , 4이면 오른쪽
// 5이면 
// CheckDirection

// 5 , 4 , 3
// 
// -1 , 0
int CheckTerms(int _x , int _y , int _dx , int _dy , int _color , bool _other)
{
	// 지금 나의 위치
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

	if (!stone) // 돌이없으면
		return 0;
	else
	{
		if (stone->GetColor() == _color) // 돌의 색깔이 같으면
		{
			find_same = true;
		}
		else // 돌의 색깔이 다르면
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
// 판단은 여기서 한다
// 돌을 놓으려고 하는 곳 주변을 확인한다
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

// 돌을 놓는다
CCheck* PutStone(CCheck* _check)
{
	CStone* stone = 0;
	int c_x = 0;
	int c_y = 0;
	int color = 0;

	c_x = _check->GetX();
	c_y = _check->GetY();

	// 해당 체크가 비어있을때만 돌을 만들고 놓는다
	if (_check->GetStone() == nullptr)
	{
		// 검은색 돌을 놓을 차례면
		if (g_board.GetBlackPlayer()->GetTurn())
		{
			color = 0;
			g_board.GetBlackPlayer()->ChangeTurn(false);
			g_board.GetWhitePlayer()->ChangeTurn(true);
		}
		else // 흰색돌을 놓을 차례면
		{
			color = 1;
			g_board.GetBlackPlayer()->ChangeTurn(true);
			g_board.GetWhitePlayer()->ChangeTurn(false);
		}

		// 돌을 하나 만든다 ( 보드 check위 x, y에 놓은 돌을 올린다 )
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

	if (now_stone) // 돌이 있으면
	{
		if (now_stone->GetColor() == _color) 
		{
			find_same = true;
		}
		else // 색깔이 다르면
		{
			//POS* pos = new POS();
			//pos->m_x = now_x;
			//pos->m_y = now_y;

			//g_stack.Push(pos);

			pass = ConfirmThisDir(now_x , now_y , _dx , _dy , _color , true);
		}
	}
	else // 돌이 없으면
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
	int color = _stone->GetColor(); // 놓은 돌의 색

	int dx[BOARD_SIZE] = { -1 , 0 , 1 , -1 , 1 , -1 , 0 , 1 };
	int dy[BOARD_SIZE] = { -1 , -1 , -1 , 0 , 0 , 1 , 1 , 1 };

	int dir = 0;

	while (dir != 8)
	{
		// 이방향을 확인한다
		ConfirmThisDir(_x , _y , dx[dir] , dy[dir] , color , false);

		//if (change) // 스택에 있는것들을 색깔을 바꾼다
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
	
	// 흰색돌 검은색돌 둘다 확인한다
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
	// 흰색돌 , 검은돌 둘다 놓을 수 없으면
	if (!check[0] && !check[1])
	{
		return true;
	}
	else
	{
		if (g_board.GetBlackPlayer()->GetTurn())
		{
			if (check[0] == 0) // 검은돌을 놓을 수 없을때
			{
				g_board.GetBlackPlayer()->ChangeTurn(false);
				g_board.GetWhitePlayer()->ChangeTurn(true);
				MessageBox(NULL, _T("검은돌을 놓을 수 없어서 흰색돌의 턴으로 바꿉니다"),
					_T("Windows Desktop Guided Tour"), NULL);
			}
		}

		if (g_board.GetWhitePlayer()->GetTurn())
		{
			if (check[1] == 0) // 흰색돌을 놓을 수 없을때
			{
				g_board.GetBlackPlayer()->ChangeTurn(true);
				g_board.GetWhitePlayer()->ChangeTurn(false);
				MessageBox(NULL, _T("흰색돌을 놓을 수 없어서 검은색돌의 턴으로 바꿉니다"),
					_T("Windows Desktop Guided Tour"), NULL);
			}
		}
	}
	return false;
}

// check 판에 돌을 센다
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

// 검은돌의 개수와 흰돌의 개수 그리고 누구차례인지 알려준다
void ShowStatement(HDC _hdc)
{
	int black = g_board.GetBlackPlayer()->GetStoneNum();
	int white = g_board.GetWhitePlayer()->GetStoneNum();

	swprintf_s(g_text, 50, L"검정 : %d  ,  흰색 : %d", black, white);
	TextOut(_hdc, 20, 660, g_text, wcslen(g_text));

	if (g_board.GetBlackPlayer()->GetTurn() == true)
	{
		swprintf_s(g_turn, 50, L"검정색 차례입니다.");
		TextOut(_hdc, 20, 680, g_turn, wcslen(g_turn));
	}
	if (g_board.GetWhitePlayer()->GetTurn() == true)
	{
		swprintf_s(g_turn, 50, L"흰색 차례입니다.");
		TextOut(_hdc, 20, 680, g_turn, wcslen(g_turn));
	}
}

void ShowWinner(HDC _hdc , bool _end)
{
	int black = g_board.GetBlackPlayer()->GetStoneNum();
	int white = g_board.GetWhitePlayer()->GetStoneNum();

	if (_end)
	{
		if (black > white) // 검정이 이겻으면
		{
			swprintf_s(g_txt, 50, L"검정 승입니다!");
			TextOut(_hdc, 20, 700, g_txt, wcslen(g_txt));
		}
		else
		{
			swprintf_s(g_txt, 50, L"흰색 승입니다!");
			TextOut(_hdc, 20, 700, g_txt, wcslen(g_txt));
		}
	}
}

// 메뉴 게임 새로 시작하기를 클릭하면
// 맨 처음 화면과 동일하게 만든다
// 각 칸에 있는 돌들을 모두 없애고,
// 3 , 3 에 흰돌을 놓고
// 4 , 4 에 흰돌을 놓고
// 3 , 4 에 검은돌을 놓고
// 4 , 3 에 검은돌을 놓는다
void ReStart()
{
	// 각 칸에 있는 모든 돌을 없앤다
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			g_board.GetData(j , i)->SetStone(nullptr);
		}
	}
	
	// 놓는다 ( 3, 3, 흰돌 ) ;
	g_board.GetData(3, 3)->SetStone(new CStone(3 * 80 + 40, 3 * 80 + 40, 1));
	// 놓는다 ( 4, 4, 흰돌 ) ;
	g_board.GetData(4, 4)->SetStone(new CStone(4 * 80 + 40, 4 * 80 + 40, 1));
	// 놓는다 ( 3, 4, 검은돌 ) ;
	g_board.GetData(3, 4)->SetStone(new CStone(3 * 80 + 40, 4 * 80 + 40, 0));
	// 놓는다 ( 4, 3, 검은돌 ) ;
	g_board.GetData(4, 3)->SetStone(new CStone(4 * 80 + 40, 3 * 80 + 40, 0));

	g_board.GetBlackPlayer()->MyTurn();
	g_board.GetWhitePlayer()->YourTurn();

}

// 경기 시간이 정규시간 (90분) 이후의 추가시간이 다 지나고 심판이 끝내자고 판단햇을때 끝난다
// 골수가 더 많은 팀이 승 , 골수가 적은 팀이 패 , 골수가 같으면 무승부이다

// 전반 45분, 후반 45분 총 90분으로 경기는 진행된다. 
// 심판은 경기가 중단되는 시간을 감안해서 추가 시간을 경기 종료 5분에 통지할 수 있다. 
// 승패는 골이 들어간 숫자를 기준으로 정해진다. 
// 경기 종료는 심판의 휘슬로 종료한다. 
// 리그 경기의 규칙은 위와 같다
// 토너먼트에서는 전,후반을 걸쳐 동점인 경우 연장 전반 15분, 후반 15분을 부여한다. 
// 연장에서도 승부가 나지 않는 경우 승부차기로 승패를 가린다

// 흰색돌을 놓을 차례인데 
//		검은돌을 놓을 자리가 없을때 (  why : 검은돌 체크? ) 
//			검은돌에서 흰돌로 넘긴다고 메세지 박스가 나옴
// 검은돌을 놓을 차례인데 
//		흰돌을 놓을 자리가 없을때 
//			흰돌에서 검은돌로 넘긴다고 메세지 박스가 나옴

// 메시지가 들어오면 호출된다
// 들어온 메시지에 따라 switch 문이 처리된다
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

		// 8 x 8 게임판을 만든다
		MakeBlank();

		// 처음 돌 4개를 놓는다
		InitStone();

		// 검은돌을 놓을 플레이어와 흰돌을 놓을 플레이어를 만든다
		InitPlayer();

		g_blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		g_whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// 판을 그린다
		RenderBoard(hdc);

		// 돌을 그린다
		RenderStone(hdc, g_whiteBrush, g_blackBrush);

		// 돌의 갯수를 센다
		CountStone();

		end = CheckAll();

		ShowWinner(hdc , end);

		// 현재 스코어와 누구차례 인지를 보여준다
		ShowStatement(hdc);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(g_blackBrush);
		DeleteObject(g_whiteBrush);
		PostQuitMessage(0);
		break;

		// 마우스 왼쪽버튼에서 떼졋을때
	case WM_LBUTTONUP:

		m_x = LOWORD(lParam);
		m_y = HIWORD(lParam);

		// 어떤 좌표인지 좌표번호를 알려준다
		x = GetX(m_x);
		y = GetY(m_y);

		// 바둑판 밖에 마우스를 두고 클릭할때 오류가 나는것을 막아주는 곳
		if (x > BOARD_SIZE - 1 || y > BOARD_SIZE - 1)
		{
			break;
		}
		if (x < 0 || y < 0)
		{
			break;
		}

		// x , y check 자리에 돌이 있는지 확인한다
		// blank = 빈칸
		// confirm = 확인한다
		// 빈칸을 확인해서 돌이라는 결과를 얻는다
		if (BlankConfirm(x, y))
			break; // 돌이 있으면 돌을 놓지못하게한다 -> case문을 빠져나온다

		// 돌이없으면
		// 주변을 체크하고 체크가 됬으면 놓을수 있다
		if (CheckArounds(x, y , GetColor()))
		{
			CCheck* check = 0;
			CStone* stone = 0;

			// 돌을 놓는다
			check = PutStone(GetCheck(x , y));

			// 돌을 놓고 놓은 돌을 가져온다
			stone = check->GetStone();
			//stone = TakeStone(check);

			// 돌의 색깔을 바꿔준다
			// 놓은 돌을 기준으로 주변의 돌을 뒤집는다
			//ChangeColor()
			FlipAroundStone(stone , x , y);
		}

		InvalidateRgn(hWnd, NULL, TRUE);

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_FILEGAMERESTART:

			// 모든 돌을 처음 시작화면과 같게 설정한다
			ReStart();

			// restart 에서 초기화 후 새로 그려준다
			InvalidateRgn(hWnd, NULL, TRUE); 
			MessageBox(hWnd, _T("게임을 새로시작합니다"), _T("새게임 시작 선택"), MB_OK);
			break;

		case ID_FILEEXIT:
			MessageBox(hWnd, _T("게임을 종료합니다"), _T("게임 종료"), MB_OK);
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