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
		// l: �̹� ������ ���� ���� ��
		int n, l;	cin >> n >> l;

		// ������ �뿩 ��� ���� 
		vector<int> hall(n + 1);

		// index: [0] 0���� �ʱ�ȭ
		hall[0] = 0;

		for (int idx = 1; idx <= n; idx++)
		{
			// ������ �뿩 ��� �Է�
			int cost;	cin >> cost;

			// current index : vec[0] + vec[1] + ... + vec[idx]
			hall[idx] = hall[idx - 1] + cost;
		}

		// output answer
		double answer = 1234567890.0;

		for (int day = l; day <= n; day++)
		{
			for (int index = 0; day + index <= n; index++)
			{
				// temp sum
				double sum = ((double)hall[day + index] - (double)hall[index]) / day;

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