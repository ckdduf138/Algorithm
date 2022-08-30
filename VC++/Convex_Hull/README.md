# 볼록 껍질

<h3> 구현기능 </h3> <hr>
볼록 껍질 생성: 그레이엄의 스캔 알고리즘을 이용해 랜덤으로 생성된 점들 중 가장 밖에 있는 점들을 찾아 볼록 껍질 생성<br>
쓰레드와 타이머를 이용해 볼록 껍질이 생성되는 과정 시각화

<h3> 제작과정 </h3> <hr>
랜덤으로 100개의 점을 생성<br>
CCW를 이용해 회전 방향을 구해 STACK에 가장 밖에 있는 점만 구함<br>
볼록 다각형(모든 내각이 180도 미만인 다각형) 만들기<br>
그레이엄의 스캔(Graham Scan) 알고리즘의 시간 복잡도 : O(NlogN)<br>

<h3>그레이엄의 스캔 알고리즘 구현</h3><hr>
1. 가장 x, y가 작은 기준점을 찾는다.<br>
2. 기준점 이외의 점들을 반시계 방향을 정렬한다.<br>
3. ccw를 활용하여 블록 껍질을 찾는다.<br>
ccw>0이 되었을 때만 스택에 넣어주면 된다.<br>
1) CCW(1, 2, 3) > 0 : 좌회전 (Left Turn)<br>
2) CCW(1, 2, 3) < 0 : 우회전 (Right Turn)<br>
3) CCW(1, 2, 3) = 0 : 3개의 점이 일직선상에 있음<br>

<h3> 실행과정 </h3><hr>
1. 랜덤의 100개 점 생성<br>

![image](https://user-images.githubusercontent.com/69779719/187388723-37ed5eca-3590-4636-991a-42acf16b5ef4.png)

2. 볼록 껍질 생성<br>

![ConvexHull](https://user-images.githubusercontent.com/69779719/144611860-b4920428-c990-42ad-80be-a6613df05592.png)

<h3> 사용기술 </h3> <hr>
WINAPI, C++, 볼록 껍질(Convex Hull)

<h3> ETC </h3> <hr>



