#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// 테스트케이스
	int c;	cin >> c;

	while (c--)
	{
		// n: 연장을 대여할 수 있는 날들의 수
		// l: 이미 섭외한 공연 팀의 수
		int n, l;	cin >> n >> l;

		// 공연장 대여 비용 저장 
		vector<int> hall(n + 1);

		// index: [0] 0으로 초기화
		hall[0] = 0;

		for (int idx = 1; idx <= n; idx++)
		{
			// 공연장 대여 비용 입력
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

				// 최솟값 찾기
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