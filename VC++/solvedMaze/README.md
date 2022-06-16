# 미로 찾기

<h3> 구현기능 </h3> <hr>
미로 생성: DFS를 이용해 상하좌우 랜덤으로 길을 뚫어 길이 하나인 완전 미로 생성<br>
미로 찾기: BFS를 이용해 특정 위치부터 최소한의 경로로 미로 경로 찾기<br>

<h3> 제작과정 </h3> <hr>
BFS 탐색하며 visted에 방문전 노드 저장 목적지 도달시 visted를 역 탐색하며 경로 추적
BFS는 상하좌우 탐색하며 매 순간 출발지로부터 최선(최소거리)의 경우를 기록하므로 vitsed를 역 추적하면
출발지로부터 도착지까지 최소거리와 최소거리의 경로를 구할 수 있다.

<h3> 실행과정 </h3> <hr>
1. 미로 생성
<img src="https://user-images.githubusercontent.com/69779719/174023636-c5ff02f9-dae3-4f28-934e-28507dbe522f.png" width="400" height="400"/>

2. 시작 위치 마우스 클릭시 시작위치부터 도착지점까지 최적의 경로 탐색
<img src="https://user-images.githubusercontent.com/69779719/174023625-535d07bd-e4df-4bb4-97e4-340ed570eab7.png" width="400" height="400"/>

<h3> 사용기술 </h3> <hr>
WINAPI, DFS, BFS

<h3> ETC </h3> <hr>
