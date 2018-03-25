/*
source code description

Gomoku AI implement

*/

/*

*/


#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<stack>
#include<numeric>
#include<limits.h>
#include<float.h>
#include<cmath>


using namespace std;

#define moveMAX 7


typedef struct MOVE {
	int x; int y;//coordinates
	MOVE() {
		x = 14;
		y = 14;
	}
	MOVE(int tx, int ty) {
		x = tx;
		y = ty;
	}
};

typedef struct LINE {
	int cmove;              // Number of moves in the line.
	MOVE argmove[moveMAX];  // The line.
}   LINE;

struct MoveValue {

	double returnValue;
	MOVE returnMove;

	MoveValue() {
		returnValue = 0;
	}

	MoveValue(double returnValuepara) {
		returnValue = returnValuepara;
	}

	MoveValue(double returnValuepara, MOVE returnMovepara) {
		returnValue = returnValuepara;
		returnMove = returnMovepara;
	}

	bool operator ==(MoveValue& t) {
		if (t.returnValue == returnValue && t.returnMove.x == returnMove.x&&t.returnMove.y == returnMove.y) return true;
		else return false;
	}

};




class Node {
public:

	Node() {
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				board[i][j] = 0;

		evl_val = 0;
	}
	Node(int a[15][15], double t) {
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				board[i][j] = a[i][j];

		evl_val = t;
	}

	void print_node() {
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (board[i][j] == 0) cout << 'o';
				if (board[i][j] == 1) cout << '*';
				if (board[i][j] == 2) cout << '+';
				cout << " ";
			}
			cout << endl;
		}
		cout << "eval=" << evl_val << endl;
	}




	int board[15][15];
	double evl_val;

};



class Gomoku
{
public:
	Gomoku();
	Gomoku(int setAIcolor);
	~Gomoku();
	bool VaildMove(int x, int y);
	void SetMove(int x, int y, int color);
	void applyMove(MOVE newMove);
	//void undoLastMove();

	int WinOrLose();
	bool WhetherWin(int x, int y, int color);
	bool canContinue();
	bool isGameOver();

	void Print();

	void StartGame(int color);
	void StartAIGame(int color, int depth);
	void StartAIGame2(int color, int depth);
	void StartAIGame3(int color, int depth);

	vector<vector<int>> GenerateLegalMove();
	vector<vector<int>> GenerateNeighbourMove();
	vector<MOVE> GenerateLegalMoves();

	int WinFive(int x, int y, int color);
	int  AliveFour(int x, int y, int color);
	int  DeadFourA(int x, int y, int color);
	int  DeadFourB(int x, int y, int color);
	int  DeadFourC(int x, int y, int color);
	int AliveThree(int x, int y, int color);
	int DeadThressA(int x, int y, int color);
	int DeadThressB(int x, int y, int color);
	int DeadThressC(int x, int y, int color);
	int DeadThressD(int x, int y, int color);
	int AliveTwo(int x, int y, int color);
	int DeadTwoA(int x, int y, int color);
	int DeadTwoB(int x, int y, int color);
	int DeadTwoC(int x, int y, int color);


	double EvaluatePoint(int i, int j);
	double EvaluateState();
	double EvaluateSmallSituation(int a[5], int color);

	MoveValue minMax(double alpha, double beta, int maxDepth, int player);
	MoveValue negaMax(int depth, int color);

	//double Minimax_alphabeta(int depth, double alpha, double beta, bool maximizingPlayer);
	//friend double Minimax_alphabeta(int A[15][15], int depth, double alpha, double beta, bool maximizingPlayer,MOVE & decisionMove);

	int AlphaBeta(int depth, int alpha, int beta, LINE * pline) {

		//int res = WinOrLose();
		//if (res == AIColor) return INT_MAX - 1;
		//else if (res == AIColor % 2 + 1) return INT_MIN + 1;


		LINE line;
		if (depth == 0 || isGameOver()) {
			pline->cmove = 0;

			//if (WinOrLose(game)) {
			//return new Result(score(game, depth), null);
			//}
			//else
			{
				double res = EvaluateState();

				// begin test
				//	Node t(Grid,res);
				//	t.print_node();
				//end test

				return res;
			}

		}



		//vector<vector<int>>LegalMoves(GenerateNeighbourMove());
		vector<MOVE>LegalMoves = GenerateLegalMoves();
		vector<MOVE>::iterator movesIterator = LegalMoves.begin();
		//	int TotalMoves = LegalMoves.size(); int CurrentMove = 0;


		while (movesIterator != LegalMoves.end()) {
			//if(depth%2==0) Grid[LegalMoves[CurrentMove][0]][LegalMoves[CurrentMove][1]] = CurrentColor;
			//else if(depth%2!=0) Grid[LegalMoves[CurrentMove][0]][LegalMoves[CurrentMove][1]] = CurrentColor%2+1;
			//Grid[LegalMoves[CurrentMove][0]][LegalMoves[CurrentMove][1]] = CurrentColor;
			//MOVE newMove = { LegalMoves[CurrentMove][0] ,LegalMoves[CurrentMove][1] };
			MOVE currentMove = *movesIterator;
			MOVE newMove = currentMove;
			movesIterator++;
			applyMove(currentMove);

			//CurrentColor = CurrentColor % 2 + 1;//???


			//MakeNextMove();
			int val = -AlphaBeta(depth - 1, -beta, -alpha, &line);

			//Grid[LegalMoves[CurrentMove][0]][LegalMoves[CurrentMove][1]] = 0;
			//CurrentColor = CurrentColor % 2 + 1;
			//CurrentMove++; TotalMoves--;
			Grid[currentMove.x][currentMove.y] = 0;
			CurrentColor = CurrentColor % 2 + 1;
			//UnmakeMove();

			if (val >= beta) return val;
			if (val > alpha) {
				alpha = val;
				pline->argmove[0] = newMove;
				//memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(MOVE));
				for (int i = 0; i < pline->cmove + 1; i++) pline->argmove[i + 1] = pline->argmove[i];
				pline->cmove = line.cmove + 1;
			}

		}
		return alpha;
	}


private:
	int Grid[15][15];
	int CurrentColor;
	int AIColor;
	double mark;

};

Gomoku::Gomoku()
{
	mark = 0;
	AIColor = 1;//default : the AI takes the black
	CurrentColor = 1;//black takes the first step
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			Grid[i][j] = 0;
}

Gomoku::Gomoku(int setAIcolor)
{
	mark = 0;
	AIColor = setAIcolor;
	CurrentColor = 1;//black takes the first step
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			Grid[i][j] = 0;
}

Gomoku::~Gomoku()
{

}

bool Gomoku::VaildMove(int x, int y)
{
	if (Grid[x][y] == 0 && x >= 0 && x<15 && y >= 0 && y<15) return true;
	else	return false;
}

void Gomoku::SetMove(int x, int y, int color)
{
	if (color == 1) Grid[x][y] = 1;
	if (color == 2) Grid[x][y] = 2;

}

void Gomoku::applyMove(MOVE newMove)
{
	Grid[newMove.x][newMove.y] = CurrentColor;
	CurrentColor = CurrentColor % 2 + 1;
}

int Gomoku::WinOrLose()
{
	int i, j, k; int numberofblack = 0; int numberofwhite = 0;
	//horizontal
	for (i = 0; i < 15; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = 0; j < 15; j++)
		{
			if (Grid[i][j] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[i][j] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}

	//vertical
	for (i = 0; i < 15; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = 0; j < 15; j++)
		{
			if (Grid[j][i] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][i] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}
	//upper_right
	for (i = 0; i <= 10; i++)
	{
		numberofblack = 0; numberofwhite = 0;

		for (j = 0; j <= 14 - i; j++)
		{
			if (Grid[j][j + i] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][j + i] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}

	//lower_left
	for (i = 0; i <= 10; i++)
	{
		numberofblack = 0; numberofwhite = 0;

		for (j = i; j <= 14; j++)
		{
			if (Grid[j][j - i] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][j - i] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}

	//upper_left
	for (i = 4; i <= 14; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = 0; j <= i; j++)
		{
			if (Grid[j][i - j] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][i - j] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}

	//lower_right
	for (i = 0; i <= 10; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = i; j <= 14; j++)
		{
			if (Grid[j][14 + i - j] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][14 + i - j] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}


	return 0;
}

bool Gomoku::WhetherWin(int x, int y, int color)
{
	int tx = x; int ty = y;
	if (color == 1) {
		int count = 0;
		while (x >= 0 && x<15 && Grid[x][y] == 1) { x++; count++; if (count == 5) return true; }
		x = tx - 1; y = ty;
		while (x >= 0 && x<15 && Grid[x][y] == 1) { x--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while (y >= 0 && y<15 && Grid[x][y] == 1) { y++; count++; if (count == 5) return true; }
		x = tx; y = ty - 1;
		while (y >= 0 && y<15 && Grid[x][y] == 1) { y--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 1) { x++; y++; count++; if (count == 5) return true; }
		x = tx - 1; y = ty - 1;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 1) { x--; y--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 1) { x++; y--; count++; if (count == 5) return true; }
		x = tx - 1; y = ty + 1;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 1) { x--; y++; count++; if (count == 5) return true; }

	}


	if (color == 2) {
		int count = 0; x = tx; y = ty;
		while (x >= 0 && x<15 && Grid[x][y] == 2) { x++; count++; if (count == 5) return true; }
		x = tx - 1; y = ty;
		while (x >= 0 && x<15 && Grid[x][y] == 2) { x--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while (y >= 0 && y<15 && Grid[x][y] == 2) { y++; count++; if (count == 5) return true; }
		x = tx; y = ty - 1;
		while (y >= 0 && y<15 && Grid[x][y] == 2) { y--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 2) { x++; y++; count++; if (count == 5) return true; }
		x = tx - 1; y = ty - 1;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 2) { x--; y--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 2) { x++; y--; count++; if (count == 5) return true; }
		x = tx - 1; y = ty + 1;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == 2) { x--; y++; count++; if (count == 5) return true; }

	}
	return false;
}

bool Gomoku::canContinue()
{
	if (WinOrLose() == 0) return true;
	else return false;
}

bool Gomoku::isGameOver()
{
	if (WinOrLose() != 0)
		return true;
	else return false;
}

void Gomoku::Print()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			switch (Grid[i][j])
			{
			case 0:cout << 'o' << ' '; break;
			case 1:cout << '*' << ' '; break;
			case 2:cout << '+' << ' '; break;
			default:
				break;
			}
		}
		cout << endl;
	}


}

void Gomoku::StartGame(int color)
{
	int x; int y;
	Print();
	while (1) {
		if (color == 1) cout << "please input the coordinate of black: ";
		if (color == 2) cout << "please input the coordinate of white: ";
		cin >> x >> y;
		while (!VaildMove(x, y)) cin >> x >> y;
		SetMove(x, y, color);
		system("cls");
		Print();
		if (WhetherWin(x, y, 1)) { cout << "Black Win!\n"; break; }
		if (WhetherWin(x, y, 2)) { cout << "White Win!\n"; break; }
		color = color % 2 + 1;

	}
}

void Gomoku::StartAIGame(int color, int depth)
{
	int x; int y;
	Print();
	stack<MOVE> MoveStack; int step = 0;
	while (1) {
		if (color == AIColor)
		{
			if (step == 0) {
				SetMove(7, 7, AIColor);
				x = 7; y = 7;
				cout << "AI takes the coordinate: " << x << ", " << y << endl;
				step++;
			}
			else {
				LINE *pline = new LINE; int alpha = INT_MIN; int beta = INT_MAX;
				AlphaBeta(depth, alpha, beta, pline);

				MOVE DecideMove = pline->argmove[0];
				x = DecideMove.x; y = DecideMove.y;
				cout << x << ' ' << y;

				system("pause");
				if (VaildMove(x, y)) {
					SetMove(x, y, AIColor);
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					cout << EvaluateState();
					system("pause");
				}
				else cout << "Invaild Coordinate!\n";
			}
		}

		if (color == AIColor % 2 + 1)
		{
			cout << "please input the coordinate of white: ";
			cin >> x >> y;
			while (!VaildMove(x, y)) cin >> x >> y;
			SetMove(x, y, color);
		}
		system("cls");
		Print();
		if (WhetherWin(x, y, 1)) { cout << "Black Win!\n"; break; }
		if (WhetherWin(x, y, 2)) { cout << "White Win!\n"; break; }
		color = color % 2 + 1;

	}
}

void Gomoku::StartAIGame2(int color, int depth)
{
	int x; int y;
	Print();
	stack<MOVE> MoveStack; int step = 0;
	while (1) {
		if (color == AIColor)
		{
			if (step == 0) {
				SetMove(7, 7, AIColor);
				x = 7; y = 7;
				cout << "AI takes the coordinate: " << x << ", " << y << endl;
				step++;
			}
			else {
				//int alpha = INT_MIN; int beta = INT_MAX;
				double alpha = -DBL_MAX; double beta = DBL_MAX;
				MoveValue res = minMax(alpha, beta, depth, (AIColor));

				MOVE DecideMove = res.returnMove;
				x = DecideMove.x; y = DecideMove.y;
				cout << x << ' ' << y;

				system("pause");
				if (VaildMove(x, y)) {
					SetMove(x, y, AIColor);
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					cout << EvaluateState() << endl;
					cout << res.returnValue;
					system("pause");
				}
				else cout << "Invaild Coordinate!\n";
			}
		}

		if (color == AIColor % 2 + 1)
		{
			cout << "please input the coordinate of white: ";
			cin >> x >> y;
			while (!VaildMove(x, y)) cin >> x >> y;
			SetMove(x, y, color);
		}
		system("cls");
		Print();
		if (WhetherWin(x, y, 1)) { cout << "Black Win!\n"; break; }
		if (WhetherWin(x, y, 2)) { cout << "White Win!\n"; break; }
		color = color % 2 + 1;

	}
}

void Gomoku::StartAIGame3(int color, int depth)
{
	int x; int y;
	Print();
	stack<MOVE> MoveStack; int step = 0;
	while (1) {
		if (color == AIColor)
		{
			if (step == 0) {
				SetMove(7, 7, AIColor);
				x = 7; y = 7;
				cout << "AI takes the coordinate: " << x << ", " << y << endl;
				step++;
			}
			else {
				//int alpha = INT_MIN; int beta = INT_MAX;
				double alpha = -DBL_MAX; double beta = DBL_MAX;
				MoveValue res = negaMax(2,AIColor);

				MOVE DecideMove = res.returnMove;
				x = DecideMove.x; y = DecideMove.y;
				cout << x << ' ' << y;

				system("pause");
				if (VaildMove(x, y)) {
					SetMove(x, y, AIColor);
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					cout << EvaluateState() << endl;
					cout << res.returnValue;
					system("pause");
				}
				else cout << "Invaild Coordinate!\n";
			}
		}

		if (color == AIColor % 2 + 1)
		{
			cout << "please input the coordinate of white: ";
			cin >> x >> y;
			while (!VaildMove(x, y)) cin >> x >> y;
			SetMove(x, y, color);
		}
		system("cls");
		Print();
		if (WhetherWin(x, y, 1)) { cout << "Black Win!\n"; break; }
		if (WhetherWin(x, y, 2)) { cout << "White Win!\n"; break; }
		color = color % 2 + 1;

	}

}

vector<vector<int>> Gomoku::GenerateLegalMove()
{
	vector<int> oneMove;
	vector<vector<int>> res;
	for (int i = 0; i<15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (Grid[i][j] == 0) {
				oneMove[0] = i; oneMove[1] = j;
				res.push_back(oneMove);
			}

		}
	return res;
}

vector<vector<int>> Gomoku::GenerateNeighbourMove()
{
	vector<int> oneMove;
	//vector<int>()
	vector<vector<int>> res;
	int i, j;

	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++)
		{
			if (Grid[i][j] != 0) {
				if (Grid[i - 1][j - 1] == 0) { oneMove[0] = i - 1; oneMove[1] = j - 1; res.push_back(oneMove); }
				if (Grid[i - 1][j] == 0) { oneMove[0] = i - 1; oneMove[1] = j; res.push_back(oneMove); }
				if (Grid[i - 1][j + 1] == 0) { oneMove[0] = i - 1; oneMove[1] = j + 1; res.push_back(oneMove); }
				if (Grid[i][j - 1] == 0) { oneMove[0] = i; oneMove[1] = j - 1; res.push_back(oneMove); }
				if (Grid[i][j + 1] == 0) { oneMove[0] = i; oneMove[1] = j + 1; res.push_back(oneMove); }
				if (Grid[i + 1][j - 1] == 0) { oneMove[0] = i + 1; oneMove[1] = j - 1; res.push_back(oneMove); }
				if (Grid[i + 1][j] == 0) { oneMove[0] = i + 1; oneMove[1] = j; res.push_back(oneMove); }
				if (Grid[i + 1][j + 1] == 0) { oneMove[0] = i + 1; oneMove[1] = j + 1; res.push_back(oneMove); }

			}
		}
	return res;
}

vector<MOVE> Gomoku::GenerateLegalMoves()
{

	vector<MOVE> res;
	int i, j;

	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++)
		{
			if (Grid[i][j] != 0) {
				if (Grid[i - 1][j - 1] == 0) { MOVE newMove(i - 1, j - 1); res.push_back(newMove); }
				if (Grid[i - 1][j] == 0) { MOVE newMove(i - 1, j); res.push_back(newMove); }
				if (Grid[i - 1][j + 1] == 0) { MOVE newMove(i - 1, j + 1); res.push_back(newMove); }
				if (Grid[i][j - 1] == 0) { MOVE newMove(i, j - 1); res.push_back(newMove); }
				if (Grid[i][j + 1] == 0) { MOVE newMove(i, j + 1); res.push_back(newMove); }
				if (Grid[i + 1][j - 1] == 0) { MOVE newMove(i + 1, j - 1); res.push_back(newMove); }
				if (Grid[i + 1][j] == 0) { MOVE newMove(i + 1, j); res.push_back(newMove); }
				if (Grid[i + 1][j + 1] == 0) { MOVE newMove(i + 1, j + 1); res.push_back(newMove); }

			}
		}
	return res;
}


int Gomoku::WinFive(int x, int y, int color)
{
	int tx = x; int ty = y;
	//if (color == 1)
	{
		int count = 0;
		while (x >= 0 && x<15 && Grid[x][y] == color) { x++; count++; if (count == 5) return 1; }
		x = tx - 1; y = ty;
		while (x >= 0 && x<15 && Grid[x][y] == color) { x--; count++; if (count == 5) return 1; }

		count = 0; x = tx; y = ty;
		while (y >= 0 && y<15 && Grid[x][y] == color) { y++; count++; if (count == 5) return 1; }
		x = tx; y = ty - 1;
		while (y >= 0 && y<15 && Grid[x][y] == color) { y--; count++; if (count == 5) return 1; }

		count = 0; x = tx; y = ty;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == color) { x++; y++; count++; if (count == 5) return 1; }
		x = tx - 1; y = ty - 1;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == color) { x--; y--; count++; if (count == 5) return 1; }

		count = 0; x = tx; y = ty;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == color) { x++; y--; count++; if (count == 5) return 1; }
		x = tx - 1; y = ty + 1;
		while (x >= 0 && x < 15 && y >= 0 && y < 15 && Grid[x][y] == color) { x--; y++; count++; if (count == 5) return 1; }

	}
	return 0;
}

int Gomoku::AliveFour(int x, int y, int color)
{
	/*
	int count = 0;
	vector<int> temp;//vertical
	while (x >= 0 && x < 15 && Grid[x][y] == color) { temp.push_back(color); x++; }
	if (x >= 0 && x < 15) temp.push_back(Grid[x][y]);
	while (x >= 0 && x < 15 && Grid[x][y] == color) { temp.insert(temp.begin(), color); x--; }
	if (x >= 0 && x < 15) temp.insert(temp.begin(), Grid[x][y]);
	if (accumulate(temp.begin(), temp.end(), 0) == 4 * color) count++;

	temp.clear();//horizontal
	while(y >= 0 && y < 15 && Grid[x][y] == color){ temp.push_back(color); y++; }
	if(y >= 0 && y < 15) temp.push_back(Grid[x][y]);
	while (y >= 0 && y < 15 && Grid[x][y] == color) { temp.insert(temp.begin(), color);  y--; }
	if (y >= 0 && y < 15) temp.insert(temp.begin(), Grid[x][y]);
	if (accumulate(temp.begin(), temp.end(), 0) == 4 * color) count++;


	temp.clear();
	while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == color) { temp.push_back(color); y++; x++; }
	if(y >= 0 && y < 15&& x >= 0 && x < 15)  temp.push_back(Grid[x][y]);
	while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == color) { temp.insert(temp.begin(), color); y--; x--; }
	if (y >= 0 && y < 15 && x >= 0 && x < 15)  temp.insert(temp.begin(), Grid[x][y]);
	if (accumulate(temp.begin(), temp.end(), 0) == 4 * color) count++;

	temp.clear();
	while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == color) { temp.push_back(color); y++; x--; }
	if (y >= 0 && y < 15 && x >= 0 && x < 15)  temp.push_back(Grid[x][y]);
	while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == color) { temp.insert(temp.begin(),color); y--; x++; }
	if (y >= 0 && y < 15 && x >= 0 && x < 15)  temp.insert(temp.begin(), Grid[x][y]);
	if (accumulate(temp.begin(), temp.end(), 0) == 4 * color) count++;

	return count;
	*/
	int count = 0;
	//vertical
	if (x < 14 && x>3 && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x - 4][y] == 0) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x + 1][y] == 0) count++;
	if (x<13 && x>2 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == 0) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == 0 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x + 2][y] == 0) count++;
	if (x<12 && x>1 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0) count++;
	if (x<12 && x>1 && Grid[x - 2][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x + 3][y] == 0) count++;
	if (x<11 && x>0 && Grid[x + 4][y] == 0 && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0) count++;
	if (x<11 && x>0 && Grid[x - 1][y] == 0 && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x + 4][y] == 0) count++;

	//horizontal
	if (y<14 && y>3 && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == color && Grid[x][y - 4] == 0) count++;
	if (y<14 && y>3 && Grid[x][y - 4] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == color && Grid[x][y + 1] == 0)count++;
	if (y<13 && y>2 && Grid[x][y + 2] == 0 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == 0)count++;
	if (y<13 && y>2 && Grid[x][y - 3] == 0 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y + 2] == 0)count++;
	if (y<12 && y>1 && Grid[x][y + 3] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0) count++;
	if (y<12 && y>1 && Grid[x][y - 2] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y + 3] == 0)count++;
	if (y<11 && y>0 && Grid[x][y + 4] == 0 && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0) count++;
	if (y<11 && y>0 && Grid[x][y - 1] == 0 && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y + 4] == 0) count++;


	//diagnal1
	if (x<14 && x>3 && y<14 && y>3 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == 0) count++;
	if (x<14 && x>3 && y<14 && y>3 && Grid[x - 4][y - 4] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == color && Grid[x + 1][y + 1] == 0) count++;
	if (x<13 && x>2 && y<13 && y>2 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == 0) count++;
	if (x<13 && x>2 && y<13 && y>2 && Grid[x - 3][y - 3] == 0 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x + 2][y + 2] == 0) count++;
	if (x<12 && x>1 && y<12 && y>1 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0)count++;
	if (x<12 && x>1 && y<12 && y>1 && Grid[x - 2][y - 2] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x + 3][y + 3] == 0) count++;
	if (x<11 && x>0 && y<11 && y>0 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0) count++;
	if (x<11 && x>0 && y<11 && y>0 && Grid[x - 1][y - 1] == 0 && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x + 4][y + 4] == 0) count++;


	//diagnal2
	if (x<14 && x>3 && y<11 && y>0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == color && Grid[x - 4][y + 4] == 0) count++;
	if (x<14 && x>3 && y<11 && y>0 && Grid[x - 4][y + 4] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == color && Grid[x + 1][y - 1] == 0) count++;
	if (x<13 && x>2 && y<12 && y>1 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == 0) count++;
	if (x<13 && x>2 && y<12 && y>1 && Grid[x - 3][y + 3] == 0 && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x + 2][y - 2] == 0) count++;
	if (x<12 && x>1 && y<13 && y>2 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == 0) count++;
	if (x<12 && x>1 && y<13 && y>2 && Grid[x - 2][y + 2] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x + 3][y - 3] == 0) count++;
	if (x<11 && x>0 && y<14 && y>3 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == 0) count++;
	if (x<11 && x>0 && y<14 && y>3 && Grid[x - 1][y + 1] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x + 4][y - 4] == 0) count++;

	return count;


}

int  Gomoku::DeadFourA(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 14 && x>3 && Grid[x + 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x - 4][y] == 0) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x + 1][y] == 0) count++;
	if (x<13 && x>2 && Grid[x + 2][y] == ((color) % 2 + 1) && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == 0) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == ((color) % 2 + 1) && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x + 2][y] == 0) count++;
	if (x<12 && x>1 && Grid[x + 3][y] == ((color) % 2 + 1) && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0) count++;
	if (x<12 && x>1 && Grid[x - 2][y] == ((color) % 2 + 1) && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x + 3][y] == 0) count++;
	if (x<11 && x>0 && Grid[x + 4][y] == ((color) % 2 + 1) && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0) count++;
	if (x<11 && x>0 && Grid[x - 1][y] == ((color) % 2 + 1) && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x + 4][y] == 0) count++;

	//horizontal
	if (y<14 && y>3 && Grid[x][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == color && Grid[x][y - 4] == 0) count++;
	if (y<14 && y>3 && Grid[x][y - 4] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == color && Grid[x][y + 1] == 0)count++;
	if (y<13 && y>2 && Grid[x][y + 2] == ((color) % 2 + 1) && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == 0)count++;
	if (y<13 && y>2 && Grid[x][y - 3] == ((color) % 2 + 1) && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y + 2] == 0)count++;
	if (y<12 && y>1 && Grid[x][y + 3] == ((color) % 2 + 1) && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0) count++;
	if (y<12 && y>1 && Grid[x][y - 2] == ((color) % 2 + 1) && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y + 3] == 0)count++;
	if (y<11 && y>0 && Grid[x][y + 4] == ((color) % 2 + 1) && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0) count++;
	if (y<11 && y>0 && Grid[x][y - 1] == ((color) % 2 + 1) && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y + 4] == 0) count++;


	//diagnal1
	if (x<14 && x>3 && y<14 && y>3 && Grid[x + 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == 0) count++;
	if (x<14 && x>3 && y<14 && y>3 && Grid[x - 4][y - 4] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == color && Grid[x + 1][y + 1] == 0) count++;
	if (x<13 && x>2 && y<13 && y>2 && Grid[x + 2][y + 2] == ((color) % 2 + 1) && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == 0) count++;
	if (x<13 && x>2 && y<13 && y>2 && Grid[x - 3][y - 3] == ((color) % 2 + 1) && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x + 2][y + 2] == 0) count++;
	if (x<12 && x>1 && y<12 && y>1 && Grid[x + 3][y + 3] == ((color) % 2 + 1) && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0)count++;
	if (x<12 && x>1 && y<12 && y>1 && Grid[x - 2][y - 2] == ((color) % 2 + 1) && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x + 3][y + 3] == 0) count++;
	if (x<11 && x>0 && y<11 && y>0 && Grid[x + 4][y + 4] == ((color) % 2 + 1) && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0) count++;
	if (x<11 && x>0 && y<11 && y>0 && Grid[x - 1][y - 1] == ((color) % 2 + 1) && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x + 4][y + 4] == 0) count++;


	//diagnal2
	if (x<14 && x>3 && y<11 && y>0 && Grid[x + 1][y - 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == color && Grid[x - 4][y + 4] == 0) count++;
	if (x<14 && x>3 && y<11 && y>0 && Grid[x - 4][y + 4] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == color && Grid[x + 1][y - 1] == 0) count++;
	if (x<13 && x>2 && y<12 && y>1 && Grid[x + 2][y - 2] == ((color) % 2 + 1) && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == 0) count++;
	if (x<13 && x>2 && y<12 && y>1 && Grid[x - 3][y + 3] == ((color) % 2 + 1) && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x + 2][y - 2] == 0) count++;
	if (x<12 && x>1 && y<13 && y>2 && Grid[x + 3][y - 3] == ((color) % 2 + 1) && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == 0) count++;
	if (x<12 && x>1 && y<13 && y>2 && Grid[x - 2][y + 2] == ((color) % 2 + 1) && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x + 3][y - 3] == 0) count++;
	if (x<11 && x>0 && y<14 && y>3 && Grid[x + 4][y - 4] == ((color) % 2 + 1) && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == 0) count++;
	if (x<11 && x>0 && y<14 && y>3 && Grid[x - 1][y + 1] == ((color) % 2 + 1) && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x + 4][y - 4] == 0) count++;

	return count;
}

int  Gomoku::DeadFourB(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x<14 && x>4 && Grid[x + 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x - 4][y] == color && Grid[x - 5][y] == ((color) % 2 + 1)) count++;
	if (x<14 && x>4 && Grid[x + 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == 0 && Grid[x - 4][y] == color && Grid[x - 5][y] == ((color) % 2 + 1)) count++;
	if (x<13 && x>3 && Grid[x + 2][y] == ((color) % 2 + 1) && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0 && Grid[x - 3][y] == color && Grid[x - 4][y] == ((color) % 2 + 1))count++;
	if (x<12 && x>2 && Grid[x + 3][y] == ((color) % 2 + 1) && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == ((color) % 2 + 1)) count++;
	if (x<12 && x>2 && Grid[x + 3][y] == ((color) % 2 + 1) && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == color && Grid[x - 3][y] == ((color) % 2 + 1)) count++;
	if (x<11 && x>1 && Grid[x + 4][y] == ((color) % 2 + 1) && Grid[x + 3][y] == color && Grid[x + 2][y] == 0 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == ((color) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((color) % 2 + 1) && Grid[x + 4][y] == color && Grid[x + 3][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == ((color) % 2 + 1))count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((color) % 2 + 1) && Grid[x + 4][y] == color && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == ((color) % 2 + 1)) count++;

	//horizontal
	if (y<14 && y>4 && Grid[x][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == color && Grid[x][y - 2] == color && Grid[x][y - 4] == color && Grid[x][y - 5] == ((color) % 2 + 1)) count++;
	if (y<14 && y>4 && Grid[x][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == 0 && Grid[x][y - 4] == color && Grid[x][y - 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && Grid[x][y + 2] == ((color) % 2 + 1) && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0 && Grid[x][y - 3] == color && Grid[x][y - 4] == ((color) % 2 + 1)) count++;
	if (y<12 && y>2 && Grid[x][y + 3] == ((color) % 2 + 1) && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == ((color) % 2 + 1)) count++;
	if (y<12 && y>2 && Grid[x][y + 3] == ((color) % 2 + 1) && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == color && Grid[x][y - 3] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && Grid[x][y + 4] == ((color) % 2 + 1) && Grid[x][y + 3] == color && Grid[x][y + 2] == 0 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y + 5] == ((color) % 2 + 1) && Grid[x][y + 4] == color && Grid[x][y + 3] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y + 5] == ((color) % 2 + 1) && Grid[x][y + 4] == color && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == ((color) % 2 + 1)) count++;


	//diagnal1
	if (x<14 && x>4 && y<14 && y>4 && Grid[x + 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 2] == color && Grid[x - 4][y - 4] == color && Grid[x - 5][y - 5] == ((color) % 2 + 1)) count++;
	if (x<14 && x>4 && y<14 && y>4 && Grid[x + 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == color && Grid[x - 5][y - 5] == ((color) % 2 + 1)) count++;
	if (x<13 && x>3 && y<13 && y>3 && Grid[x + 2][y + 2] == ((color) % 2 + 1) && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == ((color) % 2 + 1)) count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x + 3][y + 3] == ((color) % 2 + 1) && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == ((color) % 2 + 1)) count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x + 3][y + 3] == ((color) % 2 + 1) && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == ((color) % 2 + 1)) count++;
	if (x<11 && x>1 && y<11 && y>1 && Grid[x + 4][y + 4] == ((color) % 2 + 1) && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == ((color) % 2 + 1)) count++;
	if (x<10 && x>0 && y<10 && y>0 && Grid[x + 5][y + 5] == ((color) % 2 + 1) && Grid[x + 4][y + 4] == color && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == ((color) % 2 + 1)) count++;
	if (x<10 && x>0 && y<10 && y>0 && Grid[x + 5][y + 5] == ((color) % 2 + 1) && Grid[x + 4][y + 4] == color && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == ((color) % 2 + 1)) count++;


	//diagnal2
	if (x<10 && x>0 && y<14 && y>4 && Grid[x - 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 2] == color && Grid[x + 4][y - 4] == color && Grid[x + 5][y - 5] == ((color) % 2 + 1))count++;
	if (x<10 && x>0 && y<14 && y>4 && Grid[x - 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == color && Grid[x + 5][y - 5] == ((color) % 2 + 1))count++;
	if (x<11 && x>1 && y<13 && y>3 && Grid[x - 2][y + 2] == ((color) % 2 + 1) && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 4][y - 4] == ((color) % 2 + 1))count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x - 3][y + 3] == ((color) % 2 + 1) && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == ((color) % 2 + 1)) count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x - 3][y + 3] == ((color) % 2 + 1) && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == ((color) % 2 + 1)) count++;
	if (x<13 && x>3 && y<11 && y>1 && Grid[x - 4][y + 4] == ((color) % 2 + 1) && Grid[x - 3][y + 3] == color && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == ((color) % 2 + 1)) count++;
	if (x<14 && x>4 && y<10 && y>0 && Grid[x - 5][y + 5] == ((color) % 2 + 1) && Grid[x - 4][y + 4] == color && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == ((color) % 2 + 1)) count++;
	if (x<14 && x>4 && y<10 && y>0 && Grid[x - 5][y + 5] == ((color) % 2 + 1) && Grid[x - 4][y + 4] == color && Grid[x - 3][y + 3] == color && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == ((color) % 2 + 1)) count++;

	return count;
}

int Gomoku::DeadFourC(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x<14 && x>4 && Grid[x + 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0 && Grid[x - 3][y] == color && Grid[x - 4][y] == color && Grid[x - 5][y] == ((color) % 2 + 1))count++;
	if (x<13 && x>3 && Grid[x + 2][y] == ((color) % 2 + 1) && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x - 4][y] == ((color) % 2 + 1))count++;
	if (x<11 && x>1 && Grid[x + 4][y] == ((color) % 2 + 1) && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == ((color) % 2 + 1))count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((color) % 2 + 1) && Grid[x + 4][y] == color && Grid[x + 3][y] == color && Grid[x + 2][y] == 0 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == ((color) % 2 + 1))count++;

	//horizontal
	if (y<14 && y>4 && Grid[x][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0 && Grid[x][y - 3] == color && Grid[x][y - 4] == color && Grid[x][y - 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && Grid[x][y + 2] == ((color) % 2 + 1) && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == color && Grid[x][y - 3] == color && Grid[x][y - 4] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && Grid[x][y + 4] == ((color) % 2 + 1) && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y + 5] == ((color) % 2 + 1) && Grid[x][y + 4] == color && Grid[x][y + 3] == color && Grid[x][y + 2] == 0 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == ((color) % 2 + 1)) count++;


	//diagnal1
	if (y<14 && y>4 && x<14 && x>4 && Grid[x + 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == color && Grid[x - 5][y - 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && x<13 && x>3 && Grid[x + 2][y + 2] == ((color) % 2 + 1) && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && x<11 && x>1 && Grid[x + 4][y + 4] == ((color) % 2 + 1) && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == ((color) % 2 + 1))count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x + 5][y + 5] == ((color) % 2 + 1) && Grid[x + 4][y + 4] == color && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == ((color) % 2 + 1)) count++;


	//diagnal2
	if (y<14 && y>4 && x<10 && x>0 && Grid[x - 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 4][y - 4] == color && Grid[x + 5][y - 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && x<11 && x>1 && Grid[x - 2][y + 2] == ((color) % 2 + 1) && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == color && Grid[x + 4][y - 4] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && x<13 && x>3 && Grid[x - 4][y + 4] == ((color) % 2 + 1) && Grid[x - 3][y + 3] == color && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x - 5][y + 5] == ((color) % 2 + 1) && Grid[x - 4][y + 4] == color && Grid[x - 3][y + 3] == color && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == ((color) % 2 + 1)) count++;

	return count;
}

int Gomoku::AliveThree(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 13 && x>3 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == 0 && Grid[x - 4][y] == 0) count++;
	if (x<12 && x>2 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0) count++;
	if (x<11 && x>1 && Grid[x + 4][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == 0) count++;

	//horizontal
	if (y<13 && y>3 && Grid[x][y + 2] == 0 && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == 0 && Grid[x][y - 4] == 0) count++;
	if (y<12 && y>2 && Grid[x][y + 3] == 0 && Grid[x][y + 2] == 0 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0 && Grid[x][y - 3] == 0) count++;
	if (y<11 && y>1 && Grid[x][y + 4] == 0 && Grid[x][y + 3] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == 0) count++;


	//diagnal1
	if (y<13 && y>3 && x<13 && x>3 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == 0) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0) count++;
	if (y<11 && y>1 && x<11 && x>1 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == 0) count++;


	//diagnal2
	if (y<13 && y>3 && x<11 && x>1 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == 0) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0) count++;
	if (y<11 && y>1 && x<13 && x>3 && Grid[x - 4][y + 4] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == 0) count++;

	return count;
}

int Gomoku::DeadThressA(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 13 && x>2 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == color && Grid[x - 3][y] == (color % 2 + 1)) count++;
	if (x < 12 && x>1 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == color && Grid[x + 2][y] == color && Grid[x + 3][y] == (color % 2 + 1)) count++;
	if (x<12 && x>1 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == (color % 2 + 1)) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == color && Grid[x][y] == color && Grid[x + 1][y] == color && Grid[x + 2][y] == (color % 2 + 1)) count++;
	if (x<11 && x>0 && Grid[x + 4][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == (color % 2 + 1)) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == color && Grid[x - 1][y] == color && Grid[x][y] == color && Grid[x + 1][y] == (color % 2 + 1)) count++;

	//horizontal
	if (y < 13 && y>2 && Grid[x][y + 2] == 0 && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == color && Grid[x][y - 3] == (color % 2 + 1)) count++;
	if (y < 12 && y>1 && Grid[x][y - 2] == 0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == color && Grid[x][y + 2] == color && Grid[x][y + 3] == (color % 2 + 1)) count++;
	if (y<12 && y>1 && Grid[x][y + 3] == 0 && Grid[x][y + 2] == 0 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == (color % 2 + 1)) count++;
	if (y<13 && y>2 && Grid[x][y - 3] == 0 && Grid[x][y - 2] == 0 && Grid[x][y - 1] == color && Grid[x][y] == color && Grid[x][y + 1] == color && Grid[x][y + 2] == (color % 2 + 1)) count++;
	if (y<11 && y>0 && Grid[x][y + 4] == 0 && Grid[x][y + 3] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == (color % 2 + 1)) count++;
	if (y<14 && y>3 && Grid[x][y - 4] == 0 && Grid[x][y - 3] == 0 && Grid[x][y - 2] == color && Grid[x][y - 1] == color && Grid[x][y] == color && Grid[x][y + 1] == (color % 2 + 1)) count++;

	//diagnal1
	if (y < 13 && y>2 && x < 13 && x>2 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == (color % 2 + 1)) count++;
	if (y < 12 && y>1 && x < 12 && x>1 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == color && Grid[x + 2][y + 2] == color && Grid[x + 3][y + 3] == (color % 2 + 1)) count++;
	if (y < 12 && y>1 && x<12 && x>1 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == (color % 2 + 1)) count++;
	if (y < 13 && y>2 && x<13 && x>2 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == color && Grid[x][y] == color && Grid[x + 1][y + 1] == color && Grid[x + 2][y + 2] == (color % 2 + 1)) count++;
	if (y < 11 && y>0 && x<11 && x>0 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == (color % 2 + 1)) count++;
	if (y < 14 && y>3 && x<14 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 1][y - 1] == color && Grid[x][y] == color && Grid[x + 1][y + 1] == (color % 2 + 1)) count++;


	//diagnal2
	if (y < 13 && y>2 && x < 12 && x>1 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == (color % 2 + 1)) count++;
	if (y < 12 && y>1 && x < 13 && x>2 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == (color % 2 + 1)) count++;
	if (y < 12 && y>1 && x<13 && x>2 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == (color % 2 + 1)) count++;
	if (y < 13 && y>2 && x<12 && x>1 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == (color % 2 + 1)) count++;
	if (y < 11 && y>0 && x<14 && x>3 && Grid[x - 4][y + 4] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == (color % 2 + 1)) count++;
	if (y < 14 && y>3 && x<11 && x>0 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == (color % 2 + 1)) count++;

	return count;
}

int Gomoku::DeadThressB(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 14 && x>3 && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == color && Grid[x - 3][y] == color && Grid[x - 4][y] == 0) count++;
	if (x < 11 && x>0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == color && Grid[x + 3][y] == color && Grid[x + 4][y] == 0) count++;

	if (x<12 && x>1 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == color && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == color && Grid[x + 2][y] == 0) count++;

	if (x<11 && x>0 && Grid[x + 4][y] == 0 && Grid[x + 3][y] == color && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == 0) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == color && Grid[x - 2][y] == 0 && Grid[x - 1][y] == color && Grid[x][y] == color && Grid[x + 1][y] == 0) count++;

	//horizontal
	if (y < 14 && y>3 && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == color && Grid[x][y - 3] == color && Grid[x][y - 4] == 0) count++;
	if (y < 11 && y>0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == color && Grid[x][y + 3] == color && Grid[x][y + 4] == 0) count++;

	if (y<12 && y>1 && Grid[x][y + 3] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0) count++;
	if (y<13 && y>2 && Grid[x][y - 3] == 0 && Grid[x][y - 2] == color && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == color && Grid[x][y + 2] == 0) count++;

	if (y<11 && y>0 && Grid[x][y + 4] == 0 && Grid[x][y + 3] == color && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == 0) count++;
	if (y<14 && y>3 && Grid[x][y - 4] == 0 && Grid[x][y - 3] == color && Grid[x][y - 2] == 0 && Grid[x][y - 1] == color && Grid[x][y] == color && Grid[x][y + 1] == 0) count++;

	//diagnal1
	if (y < 14 && y>3 && x < 14 && x>3 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == 0) count++;
	if (y < 11 && y>0 && x < 11 && x>0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 3][y + 3] == color && Grid[x + 4][y + 4] == 0) count++;

	if (y < 12 && y>1 && x<12 && x>1 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0) count++;
	if (y < 13 && y>2 && x<13 && x>2 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == color && Grid[x + 2][y + 2] == 0) count++;

	if (y < 11 && y>0 && x<11 && x>0 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == 0) count++;
	if (y< 14 && y>3 && x<14 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == color && Grid[x][y] == color && Grid[x + 1][y + 1] == 0) count++;


	//diagnal2
	if (y < 14 && y>3 && x < 11 && x>0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == color && Grid[x + 4][y - 4] == 0) count++;
	if (y < 11 && y>0 && x < 14 && x>3 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == color && Grid[x - 4][y + 4] == 0) count++;

	if (y < 12 && y>1 && x<13 && x>2 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == 0) count++;
	if (y < 13 && y>2 && x<12 && x>1 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == 0) count++;

	if (y < 11 && y>0 && x<14 && x>3 && Grid[x - 4][y + 4] == 0 && Grid[x - 3][y + 3] == color && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == 0) count++;
	if (y< 14 && y>3 && x<11 && x> 0 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == 0) count++;

	return count;
}

int Gomoku::DeadThressC(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 14 && x>4 && Grid[x + 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 4][y] == color && Grid[x - 5][y] == ((color) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x - 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y] == color && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 4][y] == color && Grid[x + 5][y] == ((color) % 2 + 1)) count++;
	if (x<13 && x>3 && Grid[x + 2][y] == ((color) % 2 + 1) && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 3][y] == color && Grid[x - 4][y] == ((color) % 2 + 1)) count++;
	if (x<11 && x>1 && Grid[x - 2][y] == ((color) % 2 + 1) && Grid[x - 1][y] == color && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == color && Grid[x + 4][y] == ((color) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((color) % 2 + 1) && Grid[x + 4][y] == color && Grid[x + 3][y] == color && Grid[x + 2][y] == 0 && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == ((color) % 2 + 1)) count++;
	if (x<14 && x>4 && Grid[x - 5][y] == ((color) % 2 + 1) && Grid[x - 4][y] == color && Grid[x - 3][y] == color && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == ((color) % 2 + 1)) count++;

	//horizontal
	if (y < 14 && y>4 && Grid[x][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0 && Grid[x][y - 3] == 0 && Grid[x][y - 4] == color && Grid[x][y - 5] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y - 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y + 1] == color && Grid[x][y + 2] == 0 && Grid[x][y + 3] == 0 && Grid[x][y + 4] == color && Grid[x][y + 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && Grid[x][y + 2] == ((color) % 2 + 1) && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == 0 && Grid[x][y - 3] == color && Grid[x][y - 4] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && Grid[x][y - 2] == ((color) % 2 + 1) && Grid[x][y - 1] == color && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == 0 && Grid[x][y + 3] == color && Grid[x][y + 4] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y + 5] == ((color) % 2 + 1) && Grid[x][y + 4] == color && Grid[x][y + 3] == color && Grid[x][y + 2] == 0 && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == ((color) % 2 + 1)) count++;
	if (y<14 && y>4 && Grid[x][y - 5] == ((color) % 2 + 1) && Grid[x][y - 4] == color && Grid[x][y - 3] == color && Grid[x][y - 2] == 0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == ((color) % 2 + 1)) count++;


	//diagnal1
	if (y < 14 && y>4 && x < 14 && x>4 && Grid[x + 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == color && Grid[x - 5][y - 5] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x - 1][y - 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y + 1] == color && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == color && Grid[x + 5][y + 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && x<13 && x>3 && Grid[x + 2][y + 2] == ((color) % 2 + 1) && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == color && Grid[x - 4][y - 4] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && x<11 && x>1 && Grid[x - 2][y - 2] == ((color) % 2 + 1) && Grid[x - 1][y - 1] == color && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == color && Grid[x + 4][y + 4] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x + 5][y + 5] == ((color) % 2 + 1) && Grid[x + 4][y + 4] == color && Grid[x + 3][y + 3] == color && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == ((color) % 2 + 1)) count++;
	if (y<14 && y>4 && x<14 && x>4 && Grid[x - 5][y - 5] == ((color) % 2 + 1) && Grid[x - 4][y - 4] == color && Grid[x - 3][y - 3] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == ((color) % 2 + 1)) count++;


	//diagnal2
	if (y < 14 && y>4 && x < 10 && x>0 && Grid[x - 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == color && Grid[x + 5][y - 5] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x + 1][y - 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == color && Grid[x - 5][y + 5] == ((color) % 2 + 1)) count++;
	if (y<13 && y>3 && x<11 && x>1 && Grid[x - 2][y + 2] == ((color) % 2 + 1) && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 4][y - 4] == ((color) % 2 + 1)) count++;
	if (y<11 && y>1 && x<13 && x>3 && Grid[x + 2][y - 2] == ((color) % 2 + 1) && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == color && Grid[x - 4][y + 4] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x - 5][y + 5] == ((color) % 2 + 1) && Grid[x - 4][y + 4] == color && Grid[x - 3][y + 3] == color && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == ((color) % 2 + 1)) count++;
	if (y<14 && y>4 && x<10 && x>0 && Grid[x + 5][y - 5] == ((color) % 2 + 1) && Grid[x + 4][y - 4] == color && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == ((color) % 2 + 1)) count++;

	return count;
}

int Gomoku::DeadThressD(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 14 && x>4 && Grid[x + 1][y] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == color && Grid[x - 3][y] == 0 && Grid[x - 4][y] == color && Grid[x - 5][y] == ((color) % 2 + 1)) count++;
	if (x<12 && x>2 && Grid[x + 3][y] == ((color) % 2 + 1) && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == color && Grid[x - 3][y] == ((color) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((color) % 2 + 1) && Grid[x + 4][y] == color && Grid[x + 3][y] == 0 && Grid[x + 2][y] == color && Grid[x + 1][y] == 0 && Grid[x][y] == color && Grid[x - 1][y] == ((color) % 2 + 1)) count++;

	//horizontal
	if (y < 14 && y>4 && Grid[x][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == color && Grid[x][y - 3] == 0 && Grid[x][y - 4] == color && Grid[x][y - 5] == ((color) % 2 + 1)) count++;
	if (y<12 && y>2 && Grid[x][y + 3] == ((color) % 2 + 1) && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == color && Grid[x][y - 3] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y + 5] == ((color) % 2 + 1) && Grid[x][y + 4] == color && Grid[x][y + 3] == 0 && Grid[x][y + 2] == color && Grid[x][y + 1] == 0 && Grid[x][y] == color && Grid[x][y - 1] == ((color) % 2 + 1)) count++;


	//diagnal1
	if (y < 14 && y>4 && x < 14 && x>4 && Grid[x + 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == color && Grid[x - 5][y - 5] == ((color) % 2 + 1)) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x + 3][y + 3] == ((color) % 2 + 1) && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 3][y - 3] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x + 5][y + 5] == ((color) % 2 + 1) && Grid[x + 4][y + 4] == color && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 1][y + 1] == 0 && Grid[x][y] == color && Grid[x - 1][y - 1] == ((color) % 2 + 1)) count++;


	//diagnal2
	if (y < 14 && y>4 && x < 10 && x>0 && Grid[x - 1][y + 1] == ((color) % 2 + 1) && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == color && Grid[x + 5][y - 5] == ((color) % 2 + 1)) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x - 3][y + 3] == ((color) % 2 + 1) && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 3][y - 3] == ((color) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x - 5][y + 5] == ((color) % 2 + 1) && Grid[x - 4][y + 4] == color && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 1][y + 1] == 0 && Grid[x][y] == color && Grid[x + 1][y - 1] == ((color) % 2 + 1)) count++;

	return count;
}

int Gomoku::AliveTwo(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 11 && x>2 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == color && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 4][y] == 0) count++;
	if (x < 12 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == color && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0) count++;

	//horizontal
	if (y < 11 && y>2 && Grid[x][y - 3] == 0 && Grid[x][y - 2] == 0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == color && Grid[x][y + 2] == 0 && Grid[x][y + 3] == 0 && Grid[x][y + 4] == 0) count++;
	if (y < 12 && y>3 && Grid[x][y - 4] == 0 && Grid[x][y - 3] == 0 && Grid[x][y - 2] == 0 && Grid[x][y - 1] == color && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == 0 && Grid[x][y + 3] == 0) count++;

	//diagnal1
	if (y < 11 && y>2 && x < 11 && x>2 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == color && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == 0) count++;
	if (y < 12 && y>3 && x < 12 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == color && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0) count++;

	//diagnal2
	if (y < 11 && y>2 && x < 12 && x>3 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == 0) count++;
	if (y < 12 && y>3 && x < 11 && x>2 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0) count++;

	return count;
}

int Gomoku::DeadTwoA(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 11 && x>-1 && Grid[x][y] == color && Grid[x + 1][y] == color && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 4][y] == 0) count++;
	if (x < 15 && x>3 && Grid[x][y] == color && Grid[x - 1][y] == color && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 4][y] == 0) count++;
	if (x < 12 && x>0 && Grid[x - 1][y] == color && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0) count++;
	if (x < 14 && x>2 && Grid[x + 1][y] == color && Grid[x][y] == color && Grid[x - 1][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0) count++;

	//horizontal
	if (y < 11 && y>-1 && Grid[x][y] == color && Grid[x][y + 1] == color && Grid[x][y + 2] == 0 && Grid[x][y + 3] == 0 && Grid[x][y + 4] == 0) count++;
	if (y < 15 && y>3 && Grid[x][y] == color && Grid[x][y - 1] == color && Grid[x][y - 2] == 0 && Grid[x][y - 3] == 0 && Grid[x][y - 4] == 0) count++;
	if (y < 12 && y>0 && Grid[x][y - 1] == color && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == 0 && Grid[x][y + 3] == 0) count++;
	if (y < 14 && y>2 && Grid[x][y + 1] == color && Grid[x][y] == color && Grid[x][y - 1] == 0 && Grid[x][y - 2] == 0 && Grid[x][y - 3] == 0) count++;

	//diagnal1
	if (y < 11 && y>-1 && x < 11 && x>-1 && Grid[x][y] == color && Grid[x + 1][y + 1] == color && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == 0) count++;
	if (y < 15 && y>3 && x < 15 && x>3 && Grid[x][y] == color && Grid[x - 1][y - 1] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == 0) count++;
	if (y < 12 && y>0 && x < 12 && x>0 && Grid[x - 1][y - 1] == color && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0) count++;
	if (y < 14 && y>2 && x < 14 && x>2 && Grid[x + 1][y + 1] == color && Grid[x][y] == color && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0) count++;

	//diagnal2
	if (y < 11 && y>-1 && x < 15 && x>3 && Grid[x][y] == color && Grid[x - 1][y + 1] == color && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == 0) count++;
	if (y < 15 && y>3 && x < 11 && x>-1 && Grid[x][y] == color && Grid[x + 1][y - 1] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == 0) count++;
	if (y < 12 && y>0 && x < 14 && x>2 && Grid[x + 1][y - 1] == color && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0) count++;
	if (y < 14 && y>2 && x < 12 && x>0 && Grid[x - 1][y + 1] == color && Grid[x][y] == color && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0) count++;

	return count;
}

int Gomoku::DeadTwoB(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 11 && x>1 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == color && Grid[x + 3][y] == 0 && Grid[x + 4][y] == 0) count++;
	if (x < 13 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == color && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0) count++;

	//horizontal
	if (y < 11 && y>1 && Grid[x][y - 2] == 0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == color && Grid[x][y + 3] == 0 && Grid[x][y + 4] == 0) count++;
	if (y < 13 && y>3 && Grid[x][y - 4] == 0 && Grid[x][y - 3] == 0 && Grid[x][y - 2] == color && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == 0) count++;

	//diagnal1
	if (y < 11 && y>1 && x < 11 && x>1 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == color && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == 0) count++;
	if (y < 13 && y>3 && x < 13 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == color && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0) count++;

	//diagnal2
	if (y < 11 && y>1 && x < 13 && x>3 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == color && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == 0) count++;
	if (y < 13 && y>3 && x < 11 && x>1 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == color && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0) count++;

	return count;
}

int Gomoku::DeadTwoC(int x, int y, int color)
{
	int count = 0;
	//vertical
	if (x < 11 && x>0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == color && Grid[x + 4][y] == 0) count++;
	if (x < 14 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == color && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == color && Grid[x + 1][y] == 0) count++;

	//horizontal
	if (y < 11 && y>0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == 0 && Grid[x][y + 2] == 0 && Grid[x][y + 3] == color && Grid[x][y + 4] == 0) count++;
	if (y < 14 && y>3 && Grid[x][y - 4] == 0 && Grid[x][y - 3] == color && Grid[x][y - 2] == 0 && Grid[x][y - 1] == 0 && Grid[x][y] == color && Grid[x][y + 1] == 0) count++;

	//diagnal1
	if (y < 11 && y>0 && x < 11 && x>0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == color && Grid[x + 4][y + 4] == 0) count++;
	if (y < 14 && y>3 && x < 14 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == color && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == color && Grid[x + 1][y + 1] == 0) count++;

	//diagnal2
	if (y < 11 && y>0 && x < 14 && x>3 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == color && Grid[x - 4][y + 4] == 0) count++;
	if (y < 14 && y>3 && x < 11 && x>0 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == color && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == color && Grid[x - 1][y + 1] == 0) count++;

	return count;

}


double Gomoku::EvaluatePoint(int i, int j)
{
	int color = Grid[i][j];
		return  WinFive(i, j,color)* (100000000) + AliveFour(i, j, color) * (3000000) + DeadFourA(i, j, color) * 20000 + DeadFourB(i, j, color) * 18000 + DeadFourC(i, j, color) * 19000 + AliveThree(i, j, color) * 10000 + DeadThressA(i, j,  color) * 500 + DeadThressB(i, j, color) * 800 + DeadThressC(i, j, color) * 600 + DeadThressD(i, j, color) * 550 + AliveTwo(i, j, color) * 650 + DeadTwoA(i, j, color) * 150 + DeadTwoB(i, j, color) * 250 + DeadTwoC(i, j, color) * 200;
	
	
}

double Gomoku::EvaluateState()
{
	double  res = 0; int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
		{
			if (Grid[i][j] == (AIColor)) res += EvaluatePoint(i, j)*(AIColor==CurrentColor ? 1.005:1);
			
			else if (Grid[i][j] == (AIColor % 2 + 1)) res -= EvaluatePoint(i, j)*(AIColor%2+1==CurrentColor?1.005:1);
		}
	return res;
}

MoveValue Gomoku::minMax(double alpha, double beta, int maxDepth, int player)
{
	//if (!canContinue()) {
	//	MoveValue * pMoveValue = new MoveValue();
	//	return *pMoveValue;
	//}
	vector<MOVE> moves = GenerateLegalMoves();
	vector<MOVE>::iterator movesIterator = moves.begin();
	//iterator<MOVE> movesIterator = moves.iterator();
	//double value = 0;
	bool isMaximizer = player == AIColor ? true : false;
	//boolean isMaximizer = (player.equals(playerType));
	if (maxDepth == 0 || isGameOver()) {
		//value = EvaluateState();
		//MOVE temp()
		MoveValue res(EvaluateState());
		return res;
	}
	MoveValue returnMove;



	if (isMaximizer) {

		double a = -DBL_MAX; MOVE newMOVE(-1, -1);
		MoveValue DefaultMove(a, newMOVE);
		MoveValue bestMove(DefaultMove);// = NULL;


		while (movesIterator != moves.end()) {

			MOVE currentMove = *movesIterator;
			movesIterator++;
			applyMove(currentMove);
			returnMove = minMax(alpha, beta, maxDepth - 1, player % 2 + 1);
			{
				Grid[currentMove.x][currentMove.y] = 0;
				CurrentColor = CurrentColor % 2 + 1;
			}
			//board.undoLastMove();
			if ((bestMove.returnValue == DefaultMove.returnValue) || (bestMove.returnValue < returnMove.returnValue)) {
				bestMove.returnValue = returnMove.returnValue;
				bestMove.returnMove = currentMove;
			}
			if (bestMove.returnValue > alpha) {
				alpha = bestMove.returnValue;
				//bestMove = returnMove;
			}
			if (beta <= alpha) {
				//bestMove.returnValue = beta;
				//bestMove.returnMove = DefaultMove.returnMove;
				break;
				//return bestMove; // pruning
			}
		}
		return bestMove;
	}
	else {

		double a = DBL_MAX; MOVE newMOVE(-1, -1);
		MoveValue DefaultMove(a, newMOVE);
		MoveValue bestMove(DefaultMove);// = NULL;



		while (movesIterator != moves.end()) {


			MOVE currentMove = *movesIterator;
			movesIterator++;

			applyMove(currentMove);
			returnMove = minMax(alpha, beta, maxDepth - 1, player % 2 + 1);
			{
				Grid[currentMove.x][currentMove.y] = 0;
				CurrentColor = CurrentColor % 2 + 1;
			}
			//board.undoLastMove();
			if ((bestMove == DefaultMove) || (bestMove.returnValue > returnMove.returnValue)) {
				bestMove.returnValue = returnMove.returnValue;
				bestMove.returnMove = currentMove;
			}
			if (bestMove.returnValue  < beta) {
				beta = bestMove.returnValue;
				//bestMove = returnMove;
			}
			if (beta <= alpha) {
				//bestMove.returnValue = alpha;
				//bestMove.returnMove = DefaultMove.returnMove;
				break;

				//return bestMove; // pruning
			}
		}
		return bestMove;
	}
}

MoveValue Gomoku::negaMax(int depth, int color)
{
	if (depth == 0 || isGameOver()) {
			double res = EvaluateState();
			return MoveValue(res);
	}
	MoveValue bestMove(-DBL_MAX);

	vector<MOVE>LegalMoves = GenerateLegalMoves();
	vector<MOVE>::iterator movesIterator = LegalMoves.begin();
	while (movesIterator != LegalMoves.end()) {
		MOVE currentMove = *movesIterator;
		MOVE newMove = currentMove;
		movesIterator++;
		applyMove(currentMove);
		double val = -(negaMax(depth - 1, color%2+1).returnValue);
		Grid[currentMove.x][currentMove.y] = 0;
		CurrentColor = CurrentColor % 2 + 1;
		//UnmakeMove();
		if (val > bestMove.returnValue) { bestMove.returnValue = val; bestMove.returnMove = currentMove; }
	}
	return bestMove;
}



int main() {
	Gomoku test;
	//test.StartAIGame3(1, 2);//NegaMax
	test.StartAIGame2(1, 2);//MiniMax
	//test.StartAIGame(1, 2);//Alpha-Beta PV
	system("pause");
	return 0;
}

double Minimax_alphabeta(int A[15][15], int depth, double alpha, double beta, bool maximizingPlayer, MOVE & decisionMove)
{
	return 0;
}
