#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<numeric>

using namespace std;

class Gomoku
{
public:
	Gomoku();
	~Gomoku();
	bool VaildMove(int x, int y);
	void SetMove(int x,int y,int color);
	int WinOrLose();
	bool WhetherWin(int x,int y,int color);
	void Print();
	void StartGame(int color);
	vector<vector<int>> GenerateLegalMove(int A[15][15]);
	vector<vector<int>> GenerateNeighbourMove(int A[15][15]);
	int  AliveFour(int x, int y);
	int  DeadFourA(int x, int y);
	int  DeadFourB(int x, int y);
	int  DeadFourC(int x, int y);
	int AliveThree(int x, int y);
	int DeadThressA(int x, int y);
	int DeadThressB(int x, int y);
	int DeadThressC(int x, int y);
	int DeadThressD(int x, int y);
	int AliveTwo(int x, int y);
	int DeadTwoA(int x, int y);
	int DeadTwoB(int x, int y);
	int DeadTwoC(int x, int y);


	double EvaluatePoint(int i, int j);
	double EvaluateState();
	double EvaluateSmallSituation(int a[5],int color);
	
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

Gomoku::~Gomoku()
{

}

bool Gomoku::VaildMove(int x, int y)
{
	if (Grid[x][y] == 0&&x>=0&&x<15 && y >= 0 && y<15) return true;
	else	return false;
}

void Gomoku::SetMove(int x, int y, int color)
{
	if (color == 1) Grid[x][y] = 1;
	if (color == 2) Grid[x][y] = 2;

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
			if (Grid[j][14+i - j] == 1) { numberofblack++; numberofwhite = 0; if (numberofblack == 5) return 1; }
			if (Grid[j][14+i - j] == 2) { numberofwhite++; numberofblack = 0; if (numberofblack == 5) return 2; }
		}
	}


	return 0;
}

bool Gomoku::WhetherWin(int x,int y,int color)
{
	int tx = x; int ty = y;
	if (color == 1) {
		int count = 0;
		while (x>=0&&x<15 && Grid[x][y] == 1) { x++; count++; if (count == 5) return true; }
		x = tx - 1; y = ty;
		while (x>=0&&x<15 && Grid[x][y] == 1) { x--; count++; if (count == 5) return true; }

		count = 0; x = tx; y = ty;
		while ( y >= 0 && y<15 && Grid[x][y] == 1) { y++; count++; if (count == 5) return true; }
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
		while(!VaildMove(x, y)) cin >> x >> y;
		SetMove(x, y, color);
		system("cls");
		Print();
		if (WhetherWin(x,y,1)) { cout << "Black Win!\n"; break; }
		if (WhetherWin(x, y, 2)) { cout << "White Win!\n"; break; }
		color = color % 2 + 1;

	}
}

vector<vector<int>> Gomoku::GenerateLegalMove(int A[15][15])
{
	vector<int> oneMove(2, 0);
	vector<vector<int>> res;
	for (int i = 0; i<15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (A[i][j] == 0) {
				oneMove[0] = i; oneMove[1] = j;
				res.push_back(oneMove);
			}
			return res;
		}
}

vector<vector<int>> Gomoku::GenerateNeighbourMove(int A[15][15])
{
	vector<int> oneMove(2, 0);
	vector<vector<int>> res;
	int B[15][15]; int i, j;
	for( i=0;i<15;i++)
		for( j=0;j<15;j++)
		{
			if (A[i][j] != 0)  B[i][j] = 1;
			else B[i][j] = 0;
		}
	for(i=0;i<15;i++)
		for (j = 0; j < 15; j++)
		{
			if (B[i][j] ==1) {
				if (B[i - 1][j - 1] == 0) {oneMove[0] = i-1; oneMove[1] = j-1;res.push_back(oneMove);B[i-1][j-1] = 2;}
				if (B[i - 1][j ] == 0) { oneMove[0] = i-1; oneMove[1] = j; res.push_back(oneMove); B[i - 1][j ] = 2; }
				if (B[i - 1][j + 1] == 0) { oneMove[0] = i-1; oneMove[1] = j+1; res.push_back(oneMove); B[i - 1][j + 1] = 2; }
				if (B[i ][j - 1] == 0) { oneMove[0] = i; oneMove[1] = j-1; res.push_back(oneMove); B[i ][j - 1] = 2; }
				if (B[i ][j + 1] == 0) { oneMove[0] = i; oneMove[1] = j+1; res.push_back(oneMove); B[i ][j + 1] = 2; }
				if (B[i + 1][j - 1] == 0) { oneMove[0] = i+1; oneMove[1] = j-1; res.push_back(oneMove); B[i + 1][j - 1] = 2; }
				if (B[i + 1][j ] == 0) { oneMove[0] = i+1; oneMove[1] = j; res.push_back(oneMove); B[i + 1][j ] = 2; }
				if (B[i + 1][j + 1] == 0) { oneMove[0] = i+1; oneMove[1] = j+1; res.push_back(oneMove); B[i + 1][j + 1] = 2; }

			}
		}
	return res;
}

int Gomoku::AliveFour(int x, int y)
{
	int count = 0;
	vector<int> temp;//vertical
	while (x >= 0 && x < 15 && Grid[x][y] == CurrentColor) { temp.push_back(CurrentColor); x++; }
	if (x >= 0 && x < 15) temp.push_back(Grid[x][y]);
	while (x >= 0 && x < 15 && Grid[x][y] == CurrentColor) { temp.insert(temp.begin(), CurrentColor); x--; }
	if (x >= 0 && x < 15) temp.insert(temp.begin(), Grid[x][y]);
	if (accumulate(temp.begin(), temp.end(), 0) == 4 * CurrentColor) count++;

		temp.clear();//horizontal
		while(y >= 0 && y < 15 && Grid[x][y] == CurrentColor){ temp.push_back(CurrentColor); y++; }
		if(y >= 0 && y < 15) temp.push_back(Grid[x][y]);
		while (y >= 0 && y < 15 && Grid[x][y] == CurrentColor) { temp.insert(temp.begin(), CurrentColor);  y--; }
		if (y >= 0 && y < 15) temp.insert(temp.begin(), Grid[x][y]);
		if (accumulate(temp.begin(), temp.end(), 0) == 4 * CurrentColor) count++;


		temp.clear();
		while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == CurrentColor) { temp.push_back(CurrentColor); y++; x++; }
		if(y >= 0 && y < 15&& x >= 0 && x < 15)  temp.push_back(Grid[x][y]);
		while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == CurrentColor) { temp.insert(temp.begin(), CurrentColor); y--; x--; }
		if (y >= 0 && y < 15 && x >= 0 && x < 15)  temp.insert(temp.begin(), Grid[x][y]);
		if (accumulate(temp.begin(), temp.end(), 0) == 4 * CurrentColor) count++;

		temp.clear();
		while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == CurrentColor) { temp.push_back(CurrentColor); y++; x--; }
		if (y >= 0 && y < 15 && x >= 0 && x < 15)  temp.push_back(Grid[x][y]);
		while (y >= 0 && y < 15 && x >= 0 && x < 15 && Grid[x][y] == CurrentColor) { temp.insert(temp.begin(),CurrentColor); y--; x++; }
		if (y >= 0 && y < 15 && x >= 0 && x < 15)  temp.insert(temp.begin(), Grid[x][y]);
		if (accumulate(temp.begin(), temp.end(), 0) == 4 * CurrentColor) count++;
		
		return count;
}

int  Gomoku::DeadFourA(int x, int y)
{
	int count = 0;
	//vertical
	if (x < 14 && x>3 && Grid[x + 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == 0) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == CurrentColor && Grid[x + 1][y] == 0) count++;
	if (x<13 && x>2 && Grid[x + 2][y] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y] == CurrentColor&& Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == 0 ) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x +2][y] == 0) count++;
	if (x<12 && x>1 && Grid[x + 3][y] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y] == CurrentColor && Grid[x+1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == 0) count++;
	if (x<12 && x>1 && Grid[x - 2][y] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x + 3][y] == 0) count++;
	if (x<11 && x>0 && Grid[x + 4][y] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == CurrentColor && Grid[x+1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0) count++;
	if (x<11 && x>0 && Grid[x - 1][y] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 4][y] == 0) count++;

	//horizontal
	if (y<14 && y>3 && Grid[x][y+1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == CurrentColor && Grid[x][y-4] == 0) count++;
	if (y<14 && y>3 && Grid[x][y-4] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == CurrentColor && Grid[x][y+1] == 0)count++;
	if (y<13 && y>2 && Grid[x][y+2] == ((CurrentColor) % 2 + 1) && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == 0)count++;
	if (y<13 && y>2 && Grid[x][y-3] == ((CurrentColor) % 2 + 1) && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y+2] == 0)count++;
	if (y<12 && y>1 && Grid[x][y+3] == ((CurrentColor) % 2 + 1) && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0) count++;
	if (y<12 && y>1 && Grid[x][y-2] == ((CurrentColor) % 2 + 1) && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y+3] == 0)count++;
	if (y<11 && y>0 && Grid[x][y+4] == ((CurrentColor) % 2 + 1) && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0) count++;
	if (y<11 && y>0 && Grid[x][y-1] == ((CurrentColor) % 2 + 1) && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y+4] == 0) count++;


	//diagnal1
	if (x<14 && x>3 && y<14 && y>3 && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 4][y - 4] == 0) count++;
	if (x<14 && x>3 && y<14 && y>3 && Grid[x - 4][y - 4] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == CurrentColor && Grid[x + 1][y + 1] == 0) count++;
	if (x<13 && x>2 && y<13 && y>2 && Grid[x + 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == 0) count++;
	if (x<13 && x>2 && y<13 && y>2 && Grid[x - 3][y - 3] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x + 2][y + 2] == 0) count++;
	if (x<12 && x>1 && y<12 && y>1 && Grid[x + 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0)count++;
	if (x<12 && x>1 && y<12 && y>1 && Grid[x - 2][y - 2] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x + 3][y + 3] == 0) count++;
	if (x<11 && x>0 && y<11 && y>0 && Grid[x + 4][y + 4] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0) count++;
	if (x<11 && x>0 && y<11 && y>0 && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 4][y + 4] == 0) count++;


	//diagnal2
	if (x<14 && x>3 && y<11 && y>0 && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 4][y + 4] == 0) count++;
	if (x<14 && x>3 && y<11 && y>0 && Grid[x - 4][y + 4] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 3][y + 3] == CurrentColor && Grid[x + 1][y - 1] == 0) count++;
	if (x<13 && x>2 && y<12 && y>1 && Grid[x + 2][y - 2] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 3][y + 3] == 0) count++;
	if (x<13 && x>2 && y<12 && y>1 && Grid[x - 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x + 2][y - 2] == 0) count++;
	if (x<12 && x>1 && y<13 && y>2 && Grid[x + 3][y - 3] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == 0) count++;
	if (x<12 && x>1 && y<13 && y>2 && Grid[x - 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x + 3][y - 3] == 0) count++;
	if (x<11 && x>0 && y<14 && y>3 && Grid[x + 4][y - 4] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0) count++;
	if (x<11 && x>0 && y<14 && y>3 && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 4][y - 4] == 0) count++;

	return count;
}

int  Gomoku::DeadFourB(int x, int y)
{
	int count = 0;
	//vertical
	if (x<14 && x>4 && Grid[x + 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == CurrentColor && Grid[x - 5][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<14 && x>4 && Grid[x + 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == 0 && Grid[x - 4][y] == CurrentColor && Grid[x - 5][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<13 && x>3 && Grid[x + 2][y] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == ((CurrentColor) % 2 + 1))count++;
	if (x<12 && x>2 && Grid[x + 3][y] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<12 && x>2 && Grid[x + 3][y] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<11 && x>1 && Grid[x + 4][y] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == 0 && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y] == CurrentColor && Grid[x + 3][y] == 0 && Grid[x + 2][y] == CurrentColor && Grid[x+1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == ((CurrentColor) % 2 + 1))count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y] == CurrentColor && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == ((CurrentColor) % 2 + 1)) count++;

	//horizontal
	if (y<14 && y>4 && Grid[x][y+1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-4] == CurrentColor && Grid[x][y-5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<14 && y>4 && Grid[x][y+1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == 0 && Grid[x][y-4] == CurrentColor && Grid[x][y-5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && Grid[x][y+2] == ((CurrentColor) % 2 + 1) && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-3] == CurrentColor && Grid[x][y-4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<12 && y>2 && Grid[x][y+3] == ((CurrentColor) % 2 + 1) && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == ((CurrentColor) % 2 + 1)) count++;
	if (y<12 && y>2 && Grid[x][y+3] == ((CurrentColor) % 2 + 1) && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && Grid[x][y+4] == ((CurrentColor) % 2 + 1) && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == 0 && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x ][y-2] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y+5] == ((CurrentColor) % 2 + 1) && Grid[x][y+4] == CurrentColor && Grid[x][y+3] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y+5] == ((CurrentColor) % 2 + 1) && Grid[x][y+4] == CurrentColor && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal1
	if (x<14 && x>4 && y<14 && y>4 && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 2] == CurrentColor && Grid[x - 4][y - 4] == CurrentColor && Grid[x - 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (x<14 && x>4 && y<14 && y>4 && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == CurrentColor && Grid[x - 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (x<13 && x>3 && y<13 && y>3 && Grid[x + 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 4][y - 4] == ((CurrentColor) % 2 + 1)) count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x + 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == ((CurrentColor) % 2 + 1)) count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x + 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == ((CurrentColor) % 2 + 1)) count++;
	if (x<11 && x>1 && y<11 && y>1 && Grid[x + 4][y + 4] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == ((CurrentColor) % 2 + 1)) count++;
	if (x<10 && x>0 && y<10 && y>0 && Grid[x + 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y + 4] == CurrentColor && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;
	if (x<10 && x>0 && y<10 && y>0 && Grid[x + 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y + 4] == CurrentColor && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal2
	if (x<10 && x>0 && y<14 && y>4 && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 2] == CurrentColor && Grid[x + 4][y - 4] == CurrentColor && Grid[x + 5][y - 5] == ((CurrentColor) % 2 + 1))count++;
	if (x<10 && x>0 && y<14 && y>4 && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == CurrentColor && Grid[x + 5][y - 5] == ((CurrentColor) % 2 + 1))count++;
	if (x<11 && x>1 && y<13 && y>3 && Grid[x - 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 4][y - 4] == ((CurrentColor) % 2 + 1))count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x - 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == ((CurrentColor) % 2 + 1)) count++;
	if (x<12 && x>2 && y<12 && y>2 && Grid[x - 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == ((CurrentColor) % 2 + 1)) count++;
	if (x<13 && x>3 &&  y<11 && y>1 && Grid[x - 4][y + 4] == ((CurrentColor) % 2 + 1) && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == ((CurrentColor) % 2 + 1)) count++;
	if (x<14 && x>4 && y<10 && y>0 && Grid[x - 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y + 4] == CurrentColor && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;
	if (x<14 && x>4 && y<10 && y>0 && Grid[x - 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y + 4] == CurrentColor && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;

	return count;
}

int Gomoku::DeadFourC(int x, int y)
{
	int count = 0;
	//vertical
	if (x<14 && x>4 && Grid[x + 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == CurrentColor && Grid[x - 5][y] == ((CurrentColor) % 2 + 1))count++;
	if (x<13 && x>3 && Grid[x + 2][y] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == ((CurrentColor) % 2 + 1))count++;
	if (x<11 && x>1 && Grid[x + 4][y] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == ((CurrentColor) % 2 + 1))count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y] == CurrentColor && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == 0 && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == ((CurrentColor) % 2 + 1))count++;
	
	//horizontal
	if (y<14 && y>4 && Grid[x][y+1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-3] == CurrentColor && Grid[x][y-4] == CurrentColor && Grid[x][y-5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && Grid[x][y+2] == ((CurrentColor) % 2 + 1) && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == CurrentColor && Grid[x][y-4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && Grid[x ][y+4] == ((CurrentColor) % 2 + 1) && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y+5] == ((CurrentColor) % 2 + 1) && Grid[x][y+4] == CurrentColor && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == 0 && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal1
	if (y<14 && y>4 && x<14 && x>4 && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 4][y - 4] == CurrentColor && Grid[x - 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && x<13 && x>3 && Grid[x + 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 4][y - 4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && x<11 && x>1 && Grid[x + 4][y + 4] == ((CurrentColor) % 2 + 1) && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == ((CurrentColor) % 2 + 1))count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x + 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y + 4] == CurrentColor && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal2
	if (y<14 && y>4 && x<10 && x>0 && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 4][y - 4] == CurrentColor && Grid[x + 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && x<11 && x>1 && Grid[x - 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 4][y - 4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && x<13 && x>3 && Grid[x - 4][y + 4] == ((CurrentColor) % 2 + 1) && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x - 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y + 4] == CurrentColor && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;

	return count;
}

int Gomoku::AliveThree(int x, int y)
{
	int count = 0;
	//vertical
	if (x < 13 && x>3 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == 0 && Grid[x - 4][y] == 0) count++;
	if (x<12 && x>2 && Grid[x + 3][y] ==0 && Grid[x + 2][y] == 0 && Grid[x+1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0) count++;
	if (x<11 && x>1 && Grid[x + 4][y] ==0 && Grid[x + 3][y] ==0 && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == 0) count++;
	
	//horizontal
	if (y<13 && y>3 && Grid[x ][y+2] == 0 && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == 0 && Grid[x][y-4] == 0) count++;
	if (y<12 && y>2 && Grid[x][y+3] == 0 && Grid[x][y+2] == 0 && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-3] == 0) count++;
	if (y<11 && y>1 && Grid[x ][y+4] == 0 && Grid[x][y+3] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == 0) count++;


	//diagnal1
	if (y<13 && y>3 && x<13 && x>3 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == 0) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0) count++;
	if (y<11 && y>1 && x<11 && x>1 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == 0) count++;


	//diagnal2
	if (y<13 && y>3 && x<11 && x>1 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == 0) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0) count++;
	if (y<11 && y>1 && x<13 && x>3 && Grid[x - 4][y + 4] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == 0) count++;

	return count;
}

int Gomoku::DeadThressA(int x, int y)
{
	int count = 0;
	//vertical
	if (x < 13 && x>2 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == (CurrentColor%2+1)) count++;
	if (x < 12 && x>1 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x + 2][y] == CurrentColor && Grid[x + 3][y] == (CurrentColor % 2 + 1)) count++;
	if (x<12 && x>1 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == (CurrentColor % 2 + 1)) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x + 2][y] == (CurrentColor % 2 + 1)) count++;
	if (x<11 && x>0 && Grid[x + 4][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == CurrentColor && Grid[x+1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == (CurrentColor % 2 + 1)) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x-1][y] == CurrentColor && Grid[x ][y] == CurrentColor && Grid[x + 1][y] == (CurrentColor % 2 + 1)) count++;

	//horizontal
	if (y < 13 && y>2 && Grid[x][y+2] == 0 && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == (CurrentColor % 2 + 1)) count++;
	if (y < 12 && y>1 && Grid[x][y-2] == 0 && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y+2] == CurrentColor && Grid[x][y+3] == (CurrentColor % 2 + 1)) count++;
	if (y<12 && y>1 && Grid[x][y+3] == 0 && Grid[x][y+2] == 0 && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == (CurrentColor % 2 + 1)) count++;
	if (y<13 && y>2 && Grid[x][y-3] == 0 && Grid[x][y-2] == 0 && Grid[x][y-1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y+2] == (CurrentColor % 2 + 1)) count++;
	if (y<11 && y>0 && Grid[x ][y+4] == 0 && Grid[x][y+3] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == (CurrentColor % 2 + 1)) count++;
	if (y<14 && y>3 && Grid[x][y-4] == 0 && Grid[x][y-3] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y+1] == (CurrentColor % 2 + 1)) count++;

	//diagnal1
	if (y < 13 && y>2 && x < 13 && x>2 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == (CurrentColor % 2 + 1)) count++;
	if (y < 12 && y>1 && x < 12 && x>1 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 3][y + 3] == (CurrentColor % 2 + 1)) count++;
	if (y < 12 && y>1 && x<12 && x>1 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == (CurrentColor % 2 + 1)) count++;
	if (y < 13 && y>2 && x<13 && x>2 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x + 2][y + 2] == (CurrentColor % 2 + 1)) count++;
	if (y < 11 && y>0 && x<11 && x>0 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == (CurrentColor % 2 + 1)) count++;
	if (y < 14 && y>3 && x<14 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == (CurrentColor % 2 + 1)) count++;


	//diagnal2
	if (y < 13 && y>2 && x < 12 && x>1 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == (CurrentColor % 2 + 1)) count++;
	if (y < 12 && y>1 && x < 13 && x>2 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 3][y + 3] == (CurrentColor % 2 + 1)) count++;
	if (y < 12 && y>1 && x<13 && x>2 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == (CurrentColor % 2 + 1)) count++;
	if (y < 13 && y>2 && x<12 && x>1 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == (CurrentColor % 2 + 1)) count++;
	if (y < 11 && y>0 && x<14 && x>3 && Grid[x - 4][y + 4] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == (CurrentColor % 2 + 1)) count++;
	if (y < 14 && y>3 && x<11 && x>0 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == (CurrentColor % 2 + 1)) count++;

	return count;
}

int Gomoku::DeadThressB(int x, int y)
{
	int count = 0;
	//vertical
	if (x < 14 && x>3 && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x-1][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == 0) count++;
	if (x < 11 && x>0 && Grid[x -1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x + 2][y] == CurrentColor && Grid[x + 3][y] == CurrentColor && Grid[x + 4][y] == 0) count++;

	if (x<12 && x>1 && Grid[x + 3][y] == 0 && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] ==0) count++;
	if (x<13 && x>2 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x + 2][y] == 0) count++;
	
	if (x<11 && x>0 && Grid[x + 4][y] == 0 && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0) count++;
	if (x<14 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0) count++;

	//horizontal
	if (y < 14 && y>3 && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-3] == CurrentColor && Grid[x][y-4] == 0) count++;
	if (y < 11 && y>0 && Grid[x ][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+3] == CurrentColor && Grid[x][y+4] == 0) count++;

	if (y<12 && y>1 && Grid[x][y+3] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0) count++;
	if (y<13 && y>2 && Grid[x][y-3] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y+2] == 0) count++;

	if (y<11 && y>0 && Grid[x][y+4] == 0 && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0) count++;
	if (y<14 && y>3 && Grid[x][y-4] == 0 && Grid[x][y-3] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0) count++;

	//diagnal1
	if (y < 14 && y>3 && x < 14 && x>3 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 4][y - 4] == 0) count++;
	if (y < 11 && y>0 && x < 11 && x>0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 4][y + 4] == 0) count++;

	if (y < 12 && y>1 && x<12 && x>1 && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0) count++;
	if (y < 13 && y>2 && x<13 && x>2 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x + 2][y + 2] == 0) count++;

	if (y < 11 && y>0 && x<11 && x>0 && Grid[x + 4][y + 4] == 0 && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0) count++;
	if (y< 14 && y>3 && x<14 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0) count++;


	//diagnal2
	if (y < 14 && y>3 && x < 11 && x>0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 4][y - 4] == 0) count++;
	if (y < 11 && y>0 && x < 14 && x>3 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 4][y + 4] == 0) count++;

	if (y < 12 && y>1 && x<13 && x>2 && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == 0) count++;
	if (y < 13 && y>2 && x<12 && x>1 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == 0) count++;

	if (y < 11 && y>0 && x<14 && x>3 && Grid[x - 4][y + 4] == 0 && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0) count++;
	if (y< 14 && y>3 && x<11 && x> 0&& Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0) count++;

	return count;
}

int Gomoku::DeadThressC(int x, int y)
{
	int count;
	//vertical
	if (x < 14 && x>4 && Grid[x + 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 4][y] == CurrentColor && Grid[x - 5][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x - 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 4][y] == CurrentColor && Grid[x + 5][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<13 && x>3 && Grid[x + 2][y] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 3][y] == CurrentColor && Grid[x - 4][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<11 && x>1 && Grid[x - 2][y] == ((CurrentColor) % 2 + 1) && Grid[x - 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == CurrentColor && Grid[x + 4][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y] == CurrentColor && Grid[x + 3][y] == CurrentColor && Grid[x + 2][y] == 0 && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<14 && x>4 && Grid[x - 5][y] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y] == CurrentColor && Grid[x - 3][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == ((CurrentColor) % 2 + 1)) count++;

	//horizontal
	if (y < 14 && y>4 && Grid[x][y+1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-3] == 0 && Grid[x][y-4] == CurrentColor && Grid[x][y-5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y-1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y+2] == 0 && Grid[x][y+3] == 0 && Grid[x][y+4] == CurrentColor && Grid[x][y+5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && Grid[x][y+2] == ((CurrentColor) % 2 + 1) && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == 0 && Grid[x][y-3] == CurrentColor && Grid[x][y-4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && Grid[x ][y-2] == ((CurrentColor) % 2 + 1) && Grid[x][y-1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y+2] == 0 && Grid[x][y+3] == CurrentColor && Grid[x][y+4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y+5] == ((CurrentColor) % 2 + 1) && Grid[x][y+4] == CurrentColor && Grid[x][y+3] == CurrentColor && Grid[x][y+2] == 0 && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y-1] == ((CurrentColor) % 2 + 1)) count++;
	if (y<14 && y>4 && Grid[x][y-5] == ((CurrentColor) % 2 + 1) && Grid[x][y-4] == CurrentColor && Grid[x][y-3] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal1
	if (y < 14 && y>4 && x < 14 && x>4 && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == CurrentColor && Grid[x - 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == CurrentColor && Grid[x + 5][y + 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && x<13 && x>3 && Grid[x + 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 4][y - 4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && x<11 && x>1 && Grid[x - 2][y - 2] == ((CurrentColor) % 2 + 1) && Grid[x - 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 4][y + 4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x + 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y + 4] == CurrentColor && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 2][y + 2] == 0 && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;
	if (y<14 && y>4 && x<14 && x>4 && Grid[x - 5][y - 5] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y - 4] == CurrentColor && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal2
	if (y < 14 && y>4 && x < 10 && x>0 && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == CurrentColor && Grid[x + 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == CurrentColor && Grid[x - 5][y + 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<13 && y>3 && x<11 && x>1 && Grid[x - 2][y + 2] == ((CurrentColor) % 2 + 1) && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 4][y - 4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<11 && y>1 && x<13 && x>3 && Grid[x + 2][y - 2] == ((CurrentColor) % 2 + 1) && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 4][y + 4] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x - 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y + 4] == CurrentColor && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 2][y + 2] == 0 && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;
	if (y<14 && y>4 && x<10 && x>0 && Grid[x + 5][y - 5] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y - 4] == CurrentColor && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1)) count++;

	return count;
}

int Gomoku::DeadThressD(int x, int y)
{
	int count;
	//vertical
	if (x < 14 && x>4 && Grid[x + 1][y] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y] ==0 && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == 0 && Grid[x - 4][y] == CurrentColor && Grid[x - 5][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<12 && x>2 && Grid[x + 3][y] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y] == CurrentColor && Grid[x+1][y] == 0 && Grid[x ][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 3][y] == ((CurrentColor) % 2 + 1)) count++;
	if (x<10 && x>0 && Grid[x + 5][y] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y] == CurrentColor && Grid[x + 3][y] == 0 && Grid[x + 2][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == ((CurrentColor) % 2 + 1)) count++;

	//horizontal
	if (y < 14 && y>4 && Grid[x][y+1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == CurrentColor && Grid[x ][y-3] == 0 && Grid[x][y-4] == CurrentColor && Grid[x][y-5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<12 && y>2 && Grid[x][y+3] == ((CurrentColor) % 2 + 1) && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x ][y-1] == 0 && Grid[x ][y-2] == CurrentColor && Grid[x ][y-3] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && Grid[x][y+5] == ((CurrentColor) % 2 + 1) && Grid[x][y+4] == CurrentColor && Grid[x][y+3] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y] == CurrentColor && Grid[x ][y-1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal1
	if (y < 14 && y>4 && x < 14 && x>4 && Grid[x + 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == CurrentColor && Grid[x - 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x + 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 3][y - 3] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<10 && x>0 && Grid[x + 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x + 4][y + 4] == CurrentColor && Grid[x + 3][y + 3] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;


	//diagnal2
	if (y < 14 && y>4 && x < 10 && x>0 && Grid[x - 1][y + 1] == ((CurrentColor) % 2 + 1) && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x +3][y - 3] == 0 && Grid[x + 4][y - 4] == CurrentColor && Grid[x + 5][y - 5] == ((CurrentColor) % 2 + 1)) count++;
	if (y<12 && y>2 && x<12 && x>2 && Grid[x - 3][y + 3] == ((CurrentColor) % 2 + 1) && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 3][y - 3] == ((CurrentColor) % 2 + 1)) count++;
	if (y<10 && y>0 && x<14 && x>4 && Grid[x - 5][y + 5] == ((CurrentColor) % 2 + 1) && Grid[x - 4][y + 4] == CurrentColor && Grid[x - 3][y + 3] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == ((CurrentColor) % 2 + 1)) count++;

	return count;
}

int Gomoku::AliveTwo(int x, int y)
{
	int count;
	//vertical
	if (x < 11 && x>2 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0 && Grid[x + 4][y] == 0) count++;
	if (x < 12 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == 0 && Grid[x-1][y] == CurrentColor && Grid[x ][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0) count++;

	//horizontal
	if (y < 11 && y>2 && Grid[x][y-3] == 0 && Grid[x][y-2] == 0 && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x ][y+1] == CurrentColor && Grid[x][y+2] == 0 && Grid[x][y+3] == 0 && Grid[x][y+4] == 0) count++;
	if (y < 12 && y>3 && Grid[x][y-4] == 0 && Grid[x][y-3] == 0 && Grid[x][y-2] == 0 && Grid[x ][y-1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x ][y+1] == 0 && Grid[x][y+2] == 0 && Grid[x][y+3] == 0) count++;

	//diagnal1
	if (y < 11 && y>2 && x < 11 && x>2 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == 0) count++;
	if (y < 12 && y>3 && x < 12 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0) count++;

	//diagnal2
	if (y < 11 && y>2 && x < 12 && x>3 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == 0) count++;
	if (y < 12 && y>3 && x < 11 && x>2 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0) count++;

		return count;
}

int Gomoku::DeadTwoA(int x, int y)
{
	int count;
	//vertical
	if (x < 11 && x>-1 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == CurrentColor && Grid[x + 2][y] == 0 && Grid[x+3][y] == 0 && Grid[x + 4][y] == 0 ) count++;
	if (x < 15 && x>3 && Grid[x][y] == CurrentColor && Grid[x - 1][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 4][y] == 0) count++;
	if (x < 12 && x>0 && Grid[x-1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 && Grid[x + 3][y] == 0) count++;
	if (x < 14 && x>2 && Grid[x + 1][y] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x - 2][y] == 0 && Grid[x - 3][y] == 0) count++;

	//horizontal
	if (y < 11 && y>-1 && Grid[x][y] == CurrentColor && Grid[x][y+1] == CurrentColor && Grid[x][y+2] == 0 && Grid[x][y+3] == 0 && Grid[x][y+4] == 0) count++;
	if (y < 15 && y>3 && Grid[x][y] == CurrentColor && Grid[x][y-1] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-3] == 0 && Grid[x][y-4] == 0) count++;
	if (y < 12 && y>0 && Grid[x][y-1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y+2] == 0 && Grid[x][y+3] == 0) count++;
	if (y < 14 && y>2 && Grid[x][y+1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y-2] == 0 && Grid[x][y-3] == 0) count++;

	//diagnal1
	if (y < 11 && y>-1 && x < 11 && x>-1 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == CurrentColor && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == 0) count++;
	if (y < 15 && y>3 && x < 15 && x>3 && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 4][y - 4] == 0) count++;
	if (y < 12 && y>0 && x < 12 && x>0 && Grid[x - 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == 0) count++;
	if (y < 14 && y>2 && x < 14 && x>2 && Grid[x + 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x - 2][y - 2] == 0 && Grid[x - 3][y - 3] == 0) count++;

	//diagnal2
	if (y < 11 && y>-1 && x < 15 && x>3 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == CurrentColor && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == 0) count++;
	if (y < 15 && y>3 && x < 11 && x>-1 && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 4][y - 4] == 0) count++;
	if (y < 12 && y>0 && x < 14 && x>2 && Grid[x + 1][y - 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == 0) count++;
	if (y < 14 && y>2 && x < 12 && x>0 && Grid[x - 1][y + 1] == CurrentColor && Grid[x][y] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x + 2][y - 2] == 0 && Grid[x + 3][y - 3] == 0) count++;

	return count;
}

int Gomoku::DeadTwoB(int x, int y)
{
	int count;
	//vertical
	if (x < 11 && x>1 && Grid[x - 2][y] == 0 && Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x+1][y] ==0 && Grid[x + 2][y] == CurrentColor && Grid[x + 3][y] == 0 && Grid[x + 4][y] == 0 ) count++;
	if (x < 13 && x>3 && Grid[x - 4][y] == 0 && Grid[x - 3][y] == 0 && Grid[x - 2][y] == CurrentColor && Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x + 2][y] == 0 ) count++;

	//horizontal
	if (y < 11 && y>1 && Grid[x][y-2] == 0 && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y+2] == CurrentColor && Grid[x][y+3] == 0 && Grid[x][y+4] == 0) count++;
	if (y < 13 && y>3 && Grid[x][y-4] == 0 && Grid[x][y-3] == 0 && Grid[x][y-2] == CurrentColor && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y+2] == 0) count++;

	//diagnal1
	if (y < 11 && y>1 && x < 11 && x>1 && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == CurrentColor && Grid[x + 3][y + 3] == 0 && Grid[x + 4][y + 4] == 0) count++;
	if (y < 13 && y>3 && x < 13 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == 0 && Grid[x - 2][y - 2] == CurrentColor && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0) count++;

	//diagnal2
	if (y < 11 && y>1 && x < 13 && x>3 && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == CurrentColor && Grid[x - 3][y + 3] == 0 && Grid[x - 4][y + 4] == 0) count++;
	if (y < 13 && y>3 && x < 11 && x>1 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == 0 && Grid[x + 2][y - 2] == CurrentColor && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0) count++;

	return count;
}

int Gomoku::DeadTwoC(int x, int y)
{
	int count;
	//vertical
	if (x < 11 && x>0 &&  Grid[x - 1][y] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0 && Grid[x + 2][y] ==0 && Grid[x + 3][y] == CurrentColor && Grid[x + 4][y] == 0) count++;
	if (x < 14 && x>3  && Grid[x - 4][y] == 0 && Grid[x - 3][y] == CurrentColor && Grid[x - 2][y] == 0 && Grid[x-1][y] == 0&& Grid[x][y] == CurrentColor && Grid[x + 1][y] == 0) count++;

	//horizontal
	if (y < 11 && y>0 && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0 && Grid[x][y+2] == 0 && Grid[x][y+3] == CurrentColor && Grid[x][y+4] == 0) count++;
	if (y < 14 && y>3 && Grid[x][y-4] == 0 && Grid[x][y-3] == CurrentColor && Grid[x][y-2] == 0 && Grid[x][y-1] == 0 && Grid[x][y] == CurrentColor && Grid[x][y+1] == 0) count++;

	//diagnal1
	if (y < 11 && y>0 && x < 11 && x>0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0 && Grid[x + 2][y + 2] == 0 && Grid[x + 3][y + 3] == CurrentColor && Grid[x + 4][y + 4] == 0) count++;
	if (y < 14 && y>3 && x < 14 && x>3 && Grid[x - 4][y - 4] == 0 && Grid[x - 3][y - 3] == CurrentColor && Grid[x - 2][y - 2] == 0 && Grid[x - 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x + 1][y + 1] == 0) count++;

	//diagnal2
	if (y < 11 && y>0 && x < 14 && x>3 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0 && Grid[x - 2][y + 2] == 0 && Grid[x - 3][y + 3] == CurrentColor && Grid[x - 4][y + 4] == 0) count++;
	if (y < 14 && y>3 && x < 11 && x>0 && Grid[x + 4][y - 4] == 0 && Grid[x + 3][y - 3] == CurrentColor && Grid[x + 2][y - 2] == 0 && Grid[x + 1][y - 1] == 0 && Grid[x][y] == CurrentColor && Grid[x - 1][y + 1] == 0) count++;

	return count;
	
}



double Gomoku::EvaluatePoint(int i, int j)
{
	if(Grid[i][j]==CurrentColor) 
	return  AliveFour(i, j) * 300000 + DeadFourA(i, j) * 2500 + DeadFourB(i, j) * 3000 + DeadFourC(i, j) * 2600 + AliveThree(i, j) * 3000 + DeadThressA(i, j) * 500 + DeadThressB(i, j) * 800 + DeadThressC(i, j) * 600 + DeadThressD(i, j) * 550 + AliveTwo(i, j) * 650 + DeadTwoA(i, j) * 150 + DeadTwoB(i, j) * 250 + DeadTwoC(i, j) * 200;
	else if (Grid[i][j] = CurrentColor % 2 + 1) {
		double res = 0; CurrentColor = CurrentColor % 2 + 1;
		res=AliveFour(i, j) * 300000 + DeadFourA(i, j) * 2500 + DeadFourB(i, j) * 3000 + DeadFourC(i, j) * 2600 + AliveThree(i, j) * 3000 + DeadThressA(i, j) * 500 + DeadThressB(i, j) * 800 + DeadThressC(i, j) * 600 + DeadThressD(i, j) * 550 + AliveTwo(i, j) * 650 + DeadTwoA(i, j) * 150 + DeadTwoB(i, j) * 250 + DeadTwoC(i, j) * 200;
		CurrentColor = CurrentColor % 2 + 1;
		return res;
	}
}

double Gomoku::EvaluateState()
{
	double  res = 0; int i, j;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
		{
			if (Grid[i][j] == (AIColor)) res += EvaluatePoint(i, j);
			else if (Grid[i][j] == (AIColor % 2 + 1)) res -= EvaluatePoint(i, j); 
		}
	return res;
}

double Gomoku::EvaluateState(int A[15][15])
{
	if(Grid[i][j]==)
}

double Gomoku::EvaluateSmallSituation(int a[5],int color)
{
	if(a[0]== color &&a[1]== color &&a[2]== color &&a[3]== color &&a[4]==)
}



int main() {
	Gomoku test;

	test.StartGame(1);

	system("pause");
	return 0;
}