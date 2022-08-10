#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

vector<string> board;

struct info {
	int x;
	int y;
	int idx;
};

bool dfs(int i, int j, string word)
{
	stack<info> s;

	s.push({ i,j,0 });

	while (!s.empty())
	{
		info curr = s.top();
		s.pop();

		//cout << board[curr.x][curr.y] << "\n";

		for (int dir = 0; dir < 8; dir++)
		{
			int nx = curr.x + dx[dir];
			int ny = curr.y + dy[dir];
			int nIdx = curr.idx + 1;

			if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)				continue;
			if (board[nx][ny] != word[nIdx])						continue;

			if (nIdx == word.size() - 1) return true;

			s.push({ nx,ny,nIdx });
		}
	}

	return false;
}

string find(string word)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board[i][j] == word[0])
			{
				bool isTrue = dfs(i, j, word);
				if (isTrue == true) return "YES";
			}
		}
	}

	return "NO";
}

void input()
{
	for (int i = 0; i < 5; i++)
	{
		string s;	cin >> s;
		board.push_back(s);
	}

	int n;	cin >> n;

	for (int i = 0; i < n; i++)
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
1
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