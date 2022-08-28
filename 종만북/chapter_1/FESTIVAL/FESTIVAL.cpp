#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// �׽�Ʈ���̽�
	int c;	cin >> c;

	while (c--)
	{
		// n: ������ �뿩�� �� �ִ� ������ ��
		// l:�̹� ������ ���� ���� ��
		int n, l;	cin >> n >> l;

		// ������ �뿩 ��� ���� 
		vector<int> vec(n + 1);

		// index: 0 0���� �ʱ�ȭ
		vec[0] = 0;
		for (int idx = 1; idx <= n; idx++)
		{
			// ������ �뿩 ��� �Է�
			int num;	cin >> num;

			// current index : vec[0] + vec[1] + vec[idx] ...
			vec[idx] = vec[idx - 1] + num;
		}

		// output answer
		double answer = 1234567890.0;


		for (int i = l; i <= n; i++)
		{
			for (int j = 0; i + j <= n; j++)
			{
				// temp sum
				double sum = ((double)vec[i + j] - (double)vec[j]) / i;

				// �ּڰ� ã��
				answer = min(sum, answer);
			}
		}

		// output
		printf("%.11lf\n", answer);
	}
}

// input
/*
2
6 3
1 2 3 1 2 3
6 2
1 2 3 1 2 3
*/
// output
/*
1.75000000000
1.50000000000
*/