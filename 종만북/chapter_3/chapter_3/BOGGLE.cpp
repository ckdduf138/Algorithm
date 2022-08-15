#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

char board[5][5];

bool dfs(int i, int j, const string& word)
{
	if (i < 0 || i >= 5 || j < 0 || j >= 5)	return false;
	if (board[i][j] != word[0])				return false;

	if (word.size() == 1)					return true;

	for (int dir = 0; dir < 8; dir++)
	{
		int nx = i + dx[dir];
		int ny = j + dy[dir];

		if (dfs(nx, ny, word.substr(1))) return true;
	}

	return false;
}

string find(const string& word)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			bool isTrue = dfs(i, j, word);
			if (isTrue == true) return "YES";
		}
	}

	return "NO";
}

void input()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> board[i][j];
		}
	}

	int n;	cin >> n;

	while (n--)
	{
		string word;	cin >> word;

		string answer = find(word);
		cout << word << " " << answer << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(0);	cin.tie(0);	cout.tie(0);

	// 테스트케이스
	int c;	cin >> c;

	while (c--)
	{
		// 입력
		input();
	}
}

// input
/*
3
URLPM
XPRET
GIAET
XTNZY
XOQRS
6
PRETTY
GIRL
REPEAT
KARA
PANDORA
GIAZAPX
*/

// output
/*
PRETTY YES
GIRL YES
REPEAT YES
KARA NO
PANDORA NO
GIAZAPX YES
*/