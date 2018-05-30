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
#include<fstream>
#include<algorithm>
#include <cstdlib>
#include <ctime>
#include "jsoncpp/json.h" // C++编译时默认包含此库
using namespace std;

#define moveMAX 7

fstream fout("C:\\Users\\Administrator\\Desktop\\test3.txt", fstream::out | fstream::app);
fstream fout2("C:\\Users\\Administrator\\Desktop\\test4.txt", fstream::out | fstream::app);
fstream fout3("C:\\Users\\Administrator\\Desktop\\test.txt", fstream::out |fstream::app);

const int SIZE = 15;
bool Grid2[SIZE][SIZE];

int GRID[SIZE][SIZE]={0};

void printboard(){
	fout3<<endl;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			switch (GRID[i][j] ) {
				case 1: fout3<<"*"<<" ";break;
				case 2: fout3<<"+"<<" ";break;
				default : fout3<<"o"<<" ";break;
			}
			
		}
		fout3<<endl;
	}
}

int whoturns(){
	int turns=0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (Grid2[i][j] == true) {
			turns++;
			}
		}
	}
//	if(turns%2==0) return 1;
//	else return 2;
	return turns;
}

void placeBLACK(int x,int y){
	if (x >= 0 && y >= 0) {
		GRID[x][y] = 1;
	}
}

void placeWHITE(int x,int y){
	if (x >= 0 && y >= 0) {
		GRID[x][y] = 2;
	}
}

void placeAt(int x, int y)
{
	if (x >= 0 && y >= 0) {
		Grid2[x][y] = true;
	}
}

struct MOVE {
	int x; int y;//coordinates
	MOVE() {
		x = 14;
		y = 14;
	}
	MOVE(int tx, int ty) {
		x = tx;
		y = ty;
	}
	bool operator ==(MOVE &a) {
		if (a.x == x && a.y == y) return true;
		else return false;
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

struct MOVEwithValue
{
	MOVE candidate_move;
	double eval_value;

};


	bool compareInterval(MOVEwithValue& l, MOVEwithValue& r)
	{
		return l.eval_value < r.eval_value;
	}



class Node {
public:

	Node() {
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				board[i][j] = 0;

		evl_val = 0;
	}

	Node(int a[15][15]) {
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				board[i][j] = a[i][j];
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
	void setState(int state[15][15],int color);
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
	void PrintToFile();

	void StartGame(int color);
	void StartAIGame(int color, int depth);
	void StartAIGame2(int color, int depth);
	void StartAIGame3(int color, int depth);
	void StartAIGame4(int color, int depth);
	void AI_VS_AI();

	bool HasNeighbour(int i, int j);
	bool MustWin(int i, int j, int color);
	bool MustLose(int i, int j, int color);

	bool MaxKill(int depth, MOVE &killmove);
	bool MinKill(int depth, MOVE& protectmove);
	MOVE Kill(int depth);


	vector<vector<int>> GenerateLegalMove();
	vector<vector<int>> GenerateNeighbourMove();
	vector<MOVE> GenerateLegalMoves();
	vector<MOVE> GenerateSortedMoves(int color);
	vector<MOVE> GenerateSortedMoves();

	vector<MOVE> FindKillMove(int color);//找出下一步迫使对方防守的步
	vector<MOVE> FindSafeMove(int color);//找出己方不得不防守的步和通过进攻已达到防守目的的步
	vector<MOVE> FindDefendMove(int color);//找出己方一步之内不得不防守的步
	vector<MOVE> FindWinMove(int color);//找出直接连成五个子的棋
	vector<MOVE> FindSelfNextAliveFour(int color);
	vector<MOVE> FindRivalNextAliveFour(int color);


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
	double EvaluateCandidatePoint(int i, int j);
	double EvaluateState();
	double EvaluateSmallSituation(int a[5], int color);

	MoveValue minMax(double alpha, double beta, int maxDepth, int player);
	MoveValue negaMax(int depth, double alpha, double beta, int color);
	MoveValue Principal_variation_search(int depth, double alpha, double beta);
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


//private:
	int Grid[15][15];
	int CurrentColor;
	int AIColor;
	double mark;

};


Gomoku myboard;

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
	CurrentColor = setAIcolor;//black takes the first step
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
			if (Grid[i][j] == 2) { numberofwhite++; numberofblack = 0; if (numberofwhite == 5) return 2; }
		}
	}

	//vertical
	for (i = 0; i < 15; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = 0; j < 15; j++)
		{
			if (Grid[j][i] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][i] == 2) { numberofwhite++; numberofblack = 0; if (numberofwhite == 5) return 2; }
		}
	}
	//upper_right
	for (i = 0; i <= 10; i++)
	{
		numberofblack = 0; numberofwhite = 0;

		for (j = 0; j <= 14 - i; j++)
		{
			if (Grid[j][j + i] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][j + i] == 2) { numberofwhite++; numberofblack = 0; if (numberofwhite == 5) return 2; }
		}
	}

	//lower_left
	for (i = 0; i <= 10; i++)
	{
		numberofblack = 0; numberofwhite = 0;

		for (j = i; j <= 14; j++)
		{
			if (Grid[j][j - i] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][j - i] == 2) { numberofwhite++; numberofblack = 0; if (numberofwhite == 5) return 2; }
		}
	}

	//upper_left
	for (i = 4; i <= 14; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = 0; j <= i; j++)
		{
			if (Grid[j][i - j] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][i - j] == 2) { numberofwhite++; numberofblack = 0; if (numberofwhite == 5) return 2; }
		}
	}

	//lower_right
	for (i = 0; i <= 10; i++)
	{
		numberofblack = 0; numberofwhite = 0;
		for (j = i; j <= 14; j++)
		{
			if (Grid[j][14 + i - j] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][14 + i - j] == 2) { numberofwhite++; numberofblack = 0; if (numberofwhite == 5) return 2; }
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

void Gomoku::PrintToFile()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			switch (Grid[i][j])
			{
			case 0:fout << 'o' << ' '; break;
			case 1:fout << '*' << ' '; break;
			case 2:fout << '+' << ' '; break;
			default:
				break;
			}
		}
		fout << endl;
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
			if (step == 0&&AIColor==1) {
				SetMove(7, 7, AIColor);
				x = 7; y = 7;
				cout << "AI takes the coordinate: " << x << ", " << y << endl;
				step++;
			}
			else if (step == 0 && AIColor == 2) {
				if (VaildMove(7, 8)) {
					SetMove(7, 8, AIColor);
					x = 7; y = 8;
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					step++;
				}
				else if (VaildMove(7, 7)) {
					SetMove(7, 7, AIColor);
					x = 7; y = 7;
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					step++;
				}
				
			}
			else {
				//int alpha = INT_MIN; int beta = INT_MAX;
				double dur;
				clock_t start, end;
				start = clock();

				double alpha = -DBL_MAX; double beta = DBL_MAX;
				MoveValue res = minMax(alpha, beta, depth, (AIColor));

				MOVE DecideMove = res.returnMove;
				x = DecideMove.x; y = DecideMove.y;
				cout << x << ' ' << y;
				cout << endl;
				end = clock();
				dur = (double)(end - start);
				printf("AI Use Time:%f\n", (dur / CLOCKS_PER_SEC));

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
			if(color==2)
			cout << "please input the coordinate of white: ";
			if(color==1)
			cout << "please input the coordinate of black: ";
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
	int x; int y; int temp[15][15];
	Print();
	stack<MOVE> MoveStack; int step = 0;
	while (1) {
		if (color == AIColor)
		{
			if (color == AIColor)
			{
				if (step == 0 && AIColor == 1) {
					SetMove(7, 7, AIColor);
					x = 7; y = 7;
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					step++;
				}
				else if (step == 0 && AIColor == 2) {
					if (VaildMove(7, 8)) {
						SetMove(7, 8, AIColor);
						x = 7; y = 8;
						cout << "AI takes the coordinate: " << x << ", " << y << endl;
						step++;
					}
					else if (VaildMove(7, 7)) {
						SetMove(7, 7, AIColor);
						x = 7; y = 7;
						cout << "AI takes the coordinate: " << x << ", " << y << endl;
						step++;
					}

				}

				else {
					//int alpha = INT_MIN; int beta = INT_MAX;
					

					for (int mm = 0; mm < 15; mm++)
						for (int nn = 0; nn < 15; nn++)
							temp[mm][nn] = Grid[mm][nn];







					double dur;
					clock_t start, end;
					start = clock();

					//算杀
					MOVE resMove; MoveValue res;
					if (MaxKill(10, resMove)) {
						cout << "kill!\n";
						x = resMove.x; y = resMove.y;
						cout << x << ' ' << y;

						cout << endl;
						end = clock();
						dur = (double)(end - start);
						printf("AI Use Time:%f\n", (dur / CLOCKS_PER_SEC));
						

						for (int mm = 0; mm < 15; mm++)
							for (int nn = 0; nn < 15; nn++)
								Grid[mm][nn] = temp[mm][nn];



					}
					else
					{
						for (int mm = 0; mm < 15; mm++)
							for (int nn = 0; nn < 15; nn++)
								Grid[mm][nn] = temp[mm][nn];


						double alpha = -DBL_MAX; double beta = DBL_MAX;
						res = negaMax(depth, alpha, beta, AIColor);

						MOVE DecideMove = res.returnMove;
						x = DecideMove.x; y = DecideMove.y;
						cout << x << ' ' << y;

						cout << endl;
						end = clock();
						dur = (double)(end - start);
						printf("AI Use Time:%f\n", (dur / CLOCKS_PER_SEC));
					}
					system("pause");
					if (VaildMove(x, y)) {
						SetMove(x, y, AIColor);
						cout << "AI takes the coordinate: " << x << ", " << y << endl;
						cout << EvaluateState() << endl;
						//cout << res.returnValue;
						system("pause");
					}
					else cout << "Invaild Coordinate!\n";
				}
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

void Gomoku::StartAIGame4(int color, int depth)
{
	int x; int y;
	Print();
	stack<MOVE> MoveStack; int step = 0;
	while (1) {
		if (color == AIColor)
		{
			if (color == AIColor)
			{
				if (step == 0 && AIColor == 1) {
					SetMove(7, 7, AIColor);
					x = 7; y = 7;
					cout << "AI takes the coordinate: " << x << ", " << y << endl;
					step++;
				}
				else if (step == 0 && AIColor == 2) {
					if (VaildMove(7, 8)) {
						SetMove(7, 8, AIColor);
						x = 7; y = 8;
						cout << "AI takes the coordinate: " << x << ", " << y << endl;
						step++;
					}
					else if (VaildMove(7, 7)) {
						SetMove(7, 7, AIColor);
						x = 7; y = 7;
						cout << "AI takes the coordinate: " << x << ", " << y << endl;
						step++;
					}

				}

				else {
					//int alpha = INT_MIN; int beta = INT_MAX;
					double alpha = -DBL_MAX; double beta = DBL_MAX;
					MoveValue res = Principal_variation_search(depth,alpha,beta);

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

void Gomoku::AI_VS_AI()
{


}

bool Gomoku::HasNeighbour(int i, int j)
{
	bool res=false;
	if (Grid[i][j] == 0) {
		if (i - 1 >= 0 && j - 1 >= 0 && Grid[i - 1][j - 1] > 0) res = true;
		if (i - 1 >= 0 && j  >= 0 && Grid[i - 1][j] > 0) res = true;
		if (i - 1 >= 0 && j + 1 <=14 && Grid[i - 1][j + 1] > 0) res = true;
		if (i  >= 0 && j - 1 >= 0 && Grid[i ][j - 1] > 0) res = true;
		if (i  >= 0 && j + 1 <= 14 && Grid[i][j + 1] > 0) res = true;
		if (i + 1 <= 14 && j - 1 >= 0 && Grid[i + 1][j - 1] > 0) res = true;
		if (i + 1 <= 14 && j  >= 0 && Grid[i + 1][j] > 0) res = true;
		if (i + 1 <= 14 && j + 1 <= 14 && Grid[i + 1][j + 1] > 0) res = true;
	}
	return res;
}

bool Gomoku::MustWin(int i, int j, int color)
{
	Grid[i][j] = color;
	if (WinFive(i, j, color)) { Grid[i][j] = 0; return true; }
	if (AliveFour(i, j, color)) { Grid[i][j] = 0; return true; }
	if (AliveThree(i, j, color) >= 2) { Grid[i][j] = 0; return true; }
	return false;
}

bool Gomoku::MustLose(int i, int j, int color)
{
	Grid[i][j] = color%2+1;
	if (WinFive(i, j, color % 2 + 1)) { Grid[i][j] = 0; return true; }
	if (AliveFour(i, j, color % 2 + 1)) { Grid[i][j] = 0; return true; }
	if (AliveThree(i, j, color % 2 + 1) >= 2) { Grid[i][j] = 0; return true; }
	return false;
}

bool Gomoku::MaxKill(int depth, MOVE & killmove)
{
	if (WinOrLose() == AIColor && WinOrLose() != 0) return true;
	if (WinOrLose() == AIColor % 2 + 1 && WinOrLose() != 0) return false;
	else if (depth < 0) return false;
	vector<MOVE> rank1 = FindWinMove(AIColor);
	vector<MOVE> rank2 = FindDefendMove(AIColor);
	vector<MOVE> rank3 = FindSelfNextAliveFour(AIColor);
	vector<MOVE> rank4 = FindRivalNextAliveFour(AIColor);

	if (rank1.size() > 0) { killmove = rank1[0]; return true; }
	else if (rank2.size() > 0) {
		vector<MOVE>::iterator rank2movesIterator = rank2.begin();
		while (rank2movesIterator != rank2.end())
		{
			MOVE newmove = *rank2movesIterator;
			Grid[newmove.x][newmove.y] = AIColor;
			if (MinKill(depth - 1, newmove) == false) {
				killmove = newmove;
				Grid[newmove.x][newmove.y] = 0;
				return true;
			}
			Grid[newmove.x][newmove.y] = 0;
			rank2movesIterator++;
		}
	
	}
	else if (rank3.size() > 0) {
		vector<MOVE>::iterator rank3movesIterator = rank3.begin();
		while (rank3movesIterator!=rank3.end())
		{
			MOVE newmove = *rank3movesIterator;
			Grid[newmove.x][newmove.y] = AIColor;
			if (MinKill(depth - 1, newmove) == false) {
				killmove = newmove;
				Grid[newmove.x][newmove.y] = 0;
				return true;
			}
			Grid[newmove.x][newmove.y] = 0;
			rank3movesIterator++;
		}
	}

	else if (rank4.size() > 0) {
		vector<MOVE>::iterator rank4movesIterator = rank4.begin();
		while (rank4movesIterator != rank4.end())
		{
			MOVE newmove = *rank4movesIterator;
			Grid[newmove.x][newmove.y] = AIColor;
			if (MinKill(depth - 1, newmove) == false) {
				killmove = newmove;
				Grid[newmove.x][newmove.y] = 0;
				return true;
			}
			Grid[newmove.x][newmove.y] = 0;
			rank4movesIterator++;
		}
	}
	
	vector<MOVE> killer = FindKillMove(AIColor);
	if (killer.size() == 0) return false;
	vector<MOVE>::iterator movesIterator = killer.begin();
	while (movesIterator != killer.end()) {
		MOVE newmove = *movesIterator;
		Grid[newmove.x][newmove.y] = AIColor;
		if (MinKill(depth - 1, newmove) == false) { 
			killmove = newmove; 
			Grid[newmove.x][newmove.y] = 0;  
			return true; 
		}
		Grid[newmove.x][newmove.y] = 0; 
		movesIterator++;
	}

	return false;
}

bool Gomoku::MinKill(int depth, MOVE & protectmove)
{
	if (depth < 0 && WinOrLose() != AIColor) return true;
	if (WinOrLose() == AIColor % 2 + 1) return true;
	vector<MOVE> protector = FindSafeMove(AIColor % 2 + 1);
	if (protector.size() == 0) return false;
	vector<MOVE>::iterator movesIterator = protector.begin();
	while (movesIterator!=protector.end())
	{
		MOVE newmove = *movesIterator;
		Grid[newmove.x][newmove.y] = AIColor % 2 + 1; 
		if (MaxKill(depth - 1,newmove) == false) { protectmove = newmove; Grid[newmove.x][newmove.y] = 0; return true; }
		Grid[newmove.x][newmove.y] = 0;
		movesIterator++;

	}

	return false;
}

MOVE Gomoku::Kill(int depth)
{
	return MOVE();
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

vector<MOVE> Gomoku::GenerateSortedMoves(int color)
{
	vector<MOVEwithValue> pq;
	vector<MOVE> res;
	int i, j;

	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++)
		{
			if (HasNeighbour(i,j) ){
				if (MustWin(i, j, color)) { res.push_back(MOVE(i, j)); return res; }
				if (MustLose(i, j, color)) { res.push_back(MOVE(i, j)); return res; }
					MOVE newMove(i, j); 
					MOVEwithValue newMOVEwithValue; 
					newMOVEwithValue.candidate_move = newMove; 
					newMOVEwithValue.eval_value = EvaluateCandidatePoint(i, j); 
					pq.push_back(newMOVEwithValue);
			}
			
		}

	if (color == AIColor % 2 + 1) { sort(pq.rbegin(), pq.rend(), compareInterval); }
	if(color==AIColor){ sort(pq.rbegin(), pq.rend(), compareInterval); }

	 MOVE temp;
	for (int k = 0; k < pq.size(); k++) {
		temp = pq[k].candidate_move;
		res.push_back(temp);
	}

	return res;
}

vector<MOVE> Gomoku::GenerateSortedMoves()
{
	
	return vector<MOVE>();
}

vector<MOVE> Gomoku::FindKillMove(int color)
{
	vector<MOVE>res; int i, j;
	for(i=0;i<15;i++)
		for (j = 0; j < 15; j++) {
			if (Grid[i][j] == 0)
			{
				Grid[i][j] = color;
				if (WinFive(i, j, color)) { res.push_back(MOVE(i, j)); Grid[i][j] = 0; return res; }
				if (AliveFour(i, j, color)) { res.push_back(MOVE(i, j)); Grid[i][j] = 0; return res; }
				if (DeadFourA(i, j, color) || DeadFourB(i, j, color) || DeadFourC(i, j, color)) { res.push_back(MOVE(i, j)); }
				if (AliveThree(i, j, color)) { res.push_back(MOVE(i, j)); }
				Grid[i][j] = 0;
			}
		}
	return res;
}

vector<MOVE> Gomoku::FindSafeMove(int color)
{
	vector<MOVE>res; int i, j;
	vector<MOVE>SelfFive;
	vector<MOVE>RivalFive;
	vector<MOVE>SelfFour;
	vector<MOVE>RivalFour;
	vector<MOVE>SelfDeadFour;
	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++) {
			if (Grid[i][j] == 0)
			{
				Grid[i][j] = color;
				if (WinFive(i, j, color)) { SelfFive.push_back(MOVE(i, j)); Grid[i][j] = 0; return SelfFive; }//若己方有直接赢的可能，显然直接赢
				Grid[i][j] = color % 2 + 1;
				if (WinFive(i, j, color % 2 + 1)) { RivalFive.push_back(MOVE(i, j)); Grid[i][j] = 0;  }//若对方下一步就赢，己方这一步赶紧堵上
				Grid[i][j] = color;
				if (AliveFour(i, j, color)) { SelfFour.push_back(MOVE(i, j)); Grid[i][j] = 0; res.push_back(MOVE(i, j));}//对方不会一步之内就赢，而且己方有活四
				Grid[i][j] = color % 2 + 1;
				if (AliveFour(i, j, color % 2 + 1)) { RivalFour.push_back(MOVE(i, j)); Grid[i][j] = 0; res.push_back(MOVE(i, j));}//对方不会一步之内就赢，而且己方无活四
				Grid[i][j] = color;
				if (DeadFourA(i, j, color) || DeadFourB(i, j, color) || DeadFourC(i, j, color)) { SelfDeadFour.push_back(MOVE(i, j)); Grid[i][j] = 0; res.push_back(MOVE(i, j));
				}
				Grid[i][j] = 0;
			}

		}


				if (RivalFive.size() > 0) return RivalFive;//若对方下一步就赢，己方这一步赶紧堵上
				else if (SelfFour.size() > 0) return SelfFour;//若对方不会一步之内就赢，而且己方有活四
				else if (RivalFour.size() > 0) { if (SelfDeadFour.size() > 0) return SelfDeadFour; else return RivalFour; }//对方不会一步之内就赢，而且己方无活四但有死四，否则还是堵起来吧
			
			//	else return res;
				else return vector<MOVE>();
}

vector<MOVE> Gomoku::FindWinMove(int color)
{
	vector<MOVE>res; int i, j;
	vector<MOVE>SelfFive;
	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++) {
			if (Grid[i][j] == 0)
			{
				Grid[i][j] = color;
				if (WinFive(i, j, color)) { SelfFive.push_back(MOVE(i, j)); Grid[i][j] = 0; return SelfFive; }//若己方有直接赢的可能，显然直接赢
				Grid[i][j] = 0;
			}
		}

	return SelfFive;
}

vector<MOVE> Gomoku::FindSelfNextAliveFour(int color)
{
	vector<MOVE>res; int i, j;
	vector<MOVE>SelfFour;
	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++) {
			if (Grid[i][j] == 0)
			{
				Grid[i][j] = color;
				if (AliveFour(i, j, color)) { SelfFour.push_back(MOVE(i, j)); Grid[i][j] = 0; res.push_back(MOVE(i, j)); }//对方不会一步之内就赢，而且己方有活四
				Grid[i][j] = 0;
			}
		}


	return SelfFour;
}

vector<MOVE> Gomoku::FindRivalNextAliveFour(int color)
{
	vector<MOVE>res; int i, j;
	vector<MOVE>RivalFour;
	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++) {
			if (Grid[i][j] == 0)
			{
				Grid[i][j] = color % 2 + 1;
				if (AliveFour(i, j, color % 2 + 1)) { RivalFour.push_back(MOVE(i, j)); Grid[i][j] = 0; res.push_back(MOVE(i, j)); }//对方不会一步之内就赢，而且己方无活四
				Grid[i][j] = 0;
			}
		}
	return RivalFour;
}

vector<MOVE> Gomoku::FindDefendMove(int color)
{
	vector<MOVE>res; int i, j;
	vector<MOVE>SelfFive;
	vector<MOVE>RivalFive;
	vector<MOVE>RivalFour;

	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++) {
			if (Grid[i][j] == 0)
			{
				Grid[i][j] = color % 2 + 1;
				if (WinFive(i, j, color % 2 + 1)) { RivalFive.push_back(MOVE(i, j)); Grid[i][j] = 0; }//若对方下一步就赢，己方这一步赶紧堵上
				Grid[i][j] = 0;
			}
		}

	return RivalFive;
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

double Gomoku::EvaluateCandidatePoint(int i, int j)
{
	Grid[i][j] = CurrentColor;
	int color = Grid[i][j];
	
	double a =WinFive(i, j, color)* (100000000) + AliveFour(i, j, color) * (3000000) + DeadFourA(i, j, color) * 20000 + DeadFourB(i, j, color) * 18000 + DeadFourC(i, j, color) * 19000 + AliveThree(i, j, color) * 10000 + DeadThressA(i, j, color) * 500 + DeadThressB(i, j, color) * 800 + DeadThressC(i, j, color) * 600 + DeadThressD(i, j, color) * 550 + AliveTwo(i, j, color) * 650 + DeadTwoA(i, j, color) * 150 + DeadTwoB(i, j, color) * 250 + DeadTwoC(i, j, color) * 200;
	//Grid[i][j] = 0;
	Grid[i][j] = CurrentColor%2+1;
	color = Grid[i][j];
	
	double b = WinFive(i, j, color)* (100000000) + AliveFour(i, j, color) * (3000000) + DeadFourA(i, j, color) * 20000 + DeadFourB(i, j, color) * 18000 + DeadFourC(i, j, color) * 19000 + AliveThree(i, j, color) * 10000 + DeadThressA(i, j, color) * 500 + DeadThressB(i, j, color) * 800 + DeadThressC(i, j, color) * 600 + DeadThressD(i, j, color) * 550 + AliveTwo(i, j, color) * 650 + DeadTwoA(i, j, color) * 150 + DeadTwoB(i, j, color) * 250 + DeadTwoC(i, j, color) * 200;
	Grid[i][j] = 0;
	return 1.1*a + b;
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


	//vector<MOVE> moves = GenerateLegalMoves();

	vector<MOVE> moves = GenerateSortedMoves(player);

	vector<MOVE>::iterator movesIterator = moves.begin();
	//iterator<MOVE> movesIterator = moves.iterator();
	//double value = 0;
	bool isMaximizer = player == AIColor ? true : false;
	//boolean isMaximizer = (player.equals(playerType));
	if (maxDepth == 0 || isGameOver()) {
		//value = EvaluateState();
		//MOVE temp()
		
		

		MoveValue res(EvaluateState());
		//Print();
		//cout << endl;
		//cout<<res.returnValue<<endl;
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



MoveValue Gomoku::negaMax(int depth, double alpha, double beta, int color)
{
	if (depth == 0 /*|| isGameOver()*/) {
			double res = EvaluateState();
			return MoveValue(res);
	}
	MoveValue bestMove(-DBL_MAX);

	//vector<MOVE>LegalMoves = GenerateLegalMoves();

	vector<MOVE>LegalMoves = GenerateSortedMoves(color);
	int count = 0;
	vector<MOVE>::iterator movesIterator = LegalMoves.begin();
	while (movesIterator != LegalMoves.end()) {
		MOVE currentMove = *movesIterator;
		MOVE newMove = currentMove;
		movesIterator++;
		applyMove(currentMove);
		double val = -(negaMax(depth - 1, -beta,-alpha,color%2+1).returnValue);
		Grid[currentMove.x][currentMove.y] = 0;
		CurrentColor = CurrentColor % 2 + 1;
		//UnmakeMove();
		if (val > bestMove.returnValue) { bestMove.returnValue = val; bestMove.returnMove = currentMove; }
		if (val > alpha) { alpha = val; }
		if (alpha >= beta) break;
		if (count++ >= 15) break;

	}
	return bestMove;
}

MoveValue Gomoku::Principal_variation_search(int depth, double alpha, double beta)
{
	if (depth <= 0 /*|| isGameOver()*/) {
		double res = EvaluateState();
		return MoveValue(res);
	}
	vector<MOVE>LegalMoves = GenerateLegalMoves();
	MoveValue bestMove;
	vector<MOVE>::iterator movesIterator = LegalMoves.begin();

	MOVE currentMove = *movesIterator;
	MOVE newMove = currentMove;
	movesIterator++;
	applyMove(currentMove);

	bestMove.returnValue = -Principal_variation_search(depth - 1, -beta, -alpha).returnValue;
	bestMove.returnMove = currentMove;

	Grid[currentMove.x][currentMove.y] = 0;
	CurrentColor = CurrentColor % 2 + 1;
	//UnmakeMove();
	if (bestMove.returnValue > alpha) {
		if (bestMove.returnValue >= beta) return bestMove;
		alpha = bestMove.returnValue;
	}

	//all remaining moves
	while (movesIterator != LegalMoves.end())
	{
		currentMove = *movesIterator;
		newMove = currentMove;
		movesIterator++;
		applyMove(currentMove);
		//make move

		MoveValue score;
		score.returnValue = -Principal_variation_search(-alpha - 1, -alpha, depth - 1).returnValue;
		score.returnMove = currentMove;

		if (score.returnValue > alpha&&score.returnValue < beta) {
			// research with window [alpha,beta]
			score.returnValue = -Principal_variation_search(-beta, -alpha, depth - 1).returnValue;
			if (score.returnValue > alpha) alpha = score.returnValue;
		}

		Grid[currentMove.x][currentMove.y] = 0;
		CurrentColor = CurrentColor % 2 + 1;
		//UnmakeMove();

		if (score.returnValue > bestMove.returnValue) {
			if (score.returnValue >= beta) return score;
			bestMove = score;
		}
	}
	return bestMove;
}


int Board[15][15] = {0};
void ApplyMove(int i, int j, int color_1) {
	if (i >= 0 && i < 15 && j >= 0 && j < 15 && Board[i][j] == 0) Board[i][j] = color_1;
}


void BoardtoBoard( int (&a)[15][15],  int(& b)[15][15]) {
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			b[i][j] = a[i][j];
}









void Print_Board() {
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			switch (Board[i][j])
			{
			case 0:fout << 'o' << ' '; break;
			case 1:fout << '*' << ' '; break;
			case 2:fout << '+' << ' '; break;
			default:
				break;
			}
		fout << endl;
	}
	fout << endl;
}




void AI_TO_AI() {
	
	Print_Board();
	//system("pause");

	Gomoku AI_a(1);
	Gomoku AI_b(2);
	//AI_b.CurrentColor = 1;//???

	ApplyMove(7, 7, 1);
	AI_a.SetMove(7, 7, AI_a.AIColor);
	AI_a.CurrentColor = AI_a.CurrentColor & 2 + 1;
	AI_b.SetMove(7, 7, AI_a.AIColor);
	AI_b.CurrentColor = AI_b.CurrentColor & 2 + 1;

	ApplyMove(7, 8, 0);
	AI_a.SetMove(7, 8, AI_b.AIColor);
	AI_a.CurrentColor = AI_a.CurrentColor & 2 + 1;
	AI_b.SetMove(7, 8, AI_b.AIColor);
	AI_b.CurrentColor = AI_b.CurrentColor & 2 + 1;

	MoveValue res;
	MOVE DecideMove;

	Print_Board();
	int x; int y;
	while (AI_a.WinOrLose()==0) {

		double dur;
		clock_t start, end;
		start = clock();

		//res = AI_b.minMax(-DBL_MAX, DBL_MAX, 2, (AI_b.AIColor));
		res = AI_b.negaMax(4, -DBL_MAX, DBL_MAX, AI_b.AIColor);


		DecideMove = res.returnMove;
		x = DecideMove.x; y = DecideMove.y;

		fout << endl;
		end = clock();
		dur = (double)(end - start);
		fout<< "AI Use Time: " << dur / CLOCKS_PER_SEC;

		fout2 << dur / CLOCKS_PER_SEC<<endl;

		fout << endl;

		ApplyMove(x, y, AI_b.AIColor);
		AI_a.SetMove(x, y, AI_b.AIColor);
		AI_a.CurrentColor = AI_a.CurrentColor & 2 + 1;
		AI_b.SetMove(x, y, AI_b.AIColor);
		AI_b.CurrentColor = AI_b.CurrentColor & 2 + 1;


		//system("cls");
		Print_Board();
		//system("pause");
		
	
		start = clock();
		
		//res = AI_a.minMax(-DBL_MAX, DBL_MAX, 2, (AI_a.AIColor));

		res = AI_a.negaMax(2,-DBL_MAX, DBL_MAX, AI_a.AIColor);
		 DecideMove = res.returnMove;
		 x = DecideMove.x;  y = DecideMove.y;

		 fout << endl;
		 end = clock();
		 dur = (double)(end - start);
		 fout << "AI Use Time: " << dur / CLOCKS_PER_SEC;
		 fout2 << dur / CLOCKS_PER_SEC << endl;

		 fout << endl;

		ApplyMove(x, y, AI_a.AIColor);
		AI_a.SetMove(x, y, AI_a.AIColor);
		AI_a.CurrentColor = AI_a.CurrentColor & 2 + 1;
		AI_b.SetMove(x, y, AI_a.AIColor);
		AI_b.CurrentColor = AI_b.CurrentColor & 2 + 1;

		//system("cls");
		Print_Board();
		//system("pause");
		fout << endl;

		
	}
}

Json::Value randomAvailablePosition()
{
		int cnt = 0;	int x; int y;
	for(int i=0;i<15;i++)
		for (int j = 0; j < 15; j++)
		{
			myboard.Grid[i][j] = GRID[i][j];
			if(GRID[i][j])cnt++;
		}
	if (cnt == 0) myboard.AIColor = 1;
	else if(cnt ==1 )myboard.AIColor = 2;

	if (cnt % 2 == 0) myboard.CurrentColor = 1;
	else if (cnt % 2 == 1) myboard.CurrentColor = 2;

 int temp[15][15];

	if (cnt == 0 && myboard.AIColor == 1) { x = 7; y = 7; }
	else if (cnt == 1 && myboard.AIColor == 2) {
		if (myboard.VaildMove(7, 8)) { x = 7; y = 8; }
		else if (myboard.VaildMove(7, 7)) { x = 7; y = 7; }
	}
else if (cnt > 1)
	{
	for (int mm = 0; mm < 15; mm++)
		for (int nn = 0; nn < 15; nn++)
			temp[mm][nn] = myboard.Grid[mm][nn];

	myboard.CurrentColor = myboard.AIColor;

	//算杀
	MOVE resMove; MoveValue res;
	if (myboard.MaxKill(10, resMove)) {
		x = resMove.x; y = resMove.y;
		for (int mm = 0; mm < 15; mm++)
			for (int nn = 0; nn < 15; nn++)
				myboard.Grid[mm][nn] = temp[mm][nn];
	}

	else
	{
		for (int mm = 0; mm < 15; mm++)
			for (int nn = 0; nn < 15; nn++)
				myboard.Grid[mm][nn] = temp[mm][nn];


		double alpha = -DBL_MAX; double beta = DBL_MAX;
		res = myboard.negaMax(6, alpha, beta, myboard.AIColor);

		MOVE DecideMove = res.returnMove;
		x = DecideMove.x; y = DecideMove.y;
	}
} 

	Json::Value action;
	action["x"] = x;
	action["y"] = y;
	return action;
}





int main(){
	
	//Gomoku test(1);
	//test.StartAIGame4(1, 2);// Principal_variation_search

	//Gomoku test(2);
    //test.StartAIGame3(1, 6);//NegaMax
	//基本完美

	//test.StartAIGame2(1, 3);//MiniMax
	//基本完美

	//test.StartAIGame(1, 2);//Alpha-Beta PV
	//狗屁不通


	//AI_TO_AI();
	
	//AI对战
	//system("pause");
	// 读入JSON
	string str;
	//fstream cin("in.txt", ios_base::in | ios_base::out);
	getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input);

	// 分析自己收到的输入和自己过往的输出，并恢复状态
	int turnID = input["responses"].size();
	for (int i = 0; i < turnID; i++) {
		placeAt(input["requests"][i]["x"].asInt(), input["requests"][i]["y"].asInt());
	
		if(whoturns()%2==1)
		{
			placeBLACK(input["requests"][i]["x"].asInt(), input["requests"][i]["y"].asInt());
		}
		else{
			placeWHITE(input["responses"][i]["x"].asInt(), input["responses"][i]["y"].asInt());
		}
	
		placeAt(input["responses"][i]["x"].asInt(), input["responses"][i]["y"].asInt());
	
		if(whoturns()%2==1)
		{
			placeBLACK(input["responses"][i]["x"].asInt(), input["responses"][i]["y"].asInt());
		}
		else{
			placeWHITE(input["responses"][i]["x"].asInt(), input["responses"][i]["y"].asInt());
		}	
		
	}
		
	placeAt(input["requests"][turnID]["x"].asInt(), input["requests"][turnID]["y"].asInt());
	
	if(whoturns()%2==1)
		{
			placeBLACK(input["requests"][turnID]["x"].asInt(), input["requests"][turnID]["y"].asInt());
		}
		else{
			placeWHITE(input["requests"][turnID]["x"].asInt(), input["requests"][turnID]["y"].asInt());
		}
		
	
	fout<<whoturns()<<endl;
		printboard();
	// 做出决策存为myAction
	// 输出决策JSON
	Json::Value ret;
	ret["response"] = randomAvailablePosition();
	Json::FastWriter writer;
	cout << writer.write(ret) << endl;
	return 0;
}









