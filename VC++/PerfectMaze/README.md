# 랜덤 미로 생성

<h3> 구현기능 </h3> <hr>
미로 생성: DFS를 이용해 상하좌우 랜덤으로 길을 뚫어 길이 하나인 완전 미로 생성<br>
쓰레드와 타이머를 이용해 미로가 생성되는 과정 시각화

<h3> 제작과정 </h3> <hr>
초기상태의 방과 방 사이의 벽을 뚫어 완전미로 생성<br>
벽을 무시하고 방을 기준으로 DFS를 실행해 만약 왼쪽으로 갔다면 현재 있는 방을 기준으로 왼쪽 벽을 부수고 왼쪽 방으로 이동하며 미로 생성<br>
방문한 방은 체크하여 더 이상 방문할 곳이 없을때까지 반복한다

<img src="https://user-images.githubusercontent.com/69779719/172580113-bc15eaa1-8fe9-43fb-b99f-8ac95f78b709.png" width="20" height="20"> 방(길) <br>
<img src="https://user-images.githubusercontent.com/69779719/172580438-b72e3da2-e49e-4fab-a90c-6d0ea187e771.png" width="20" height="20"> 벽
<h3> 실행과정 </h3> <hr>

1. 방의 상하좌우가 벽으로 막혀 있는 초기 상태<br>
<img src="https://user-images.githubusercontent.com/69779719/172576129-414a0455-6223-425a-a947-3cb7b86c526a.png" width="450" height="450"><br>

2. 랜덤으로 시작 위치 생성<br>
<img src="https://user-images.githubusercontent.com/69779719/172576286-b7a3b02b-de5f-498d-bd18-81391ce0ce27.png" width="450" height="450"><br>

3. 랜덤으로 상하좌우 이동하며 길 뚫어 미로 생성<br>
<img src="https://user-images.githubusercontent.com/69779719/172576373-83196d81-ebfc-453a-b980-92e06f5ec99e.png" width="450" height="450"><br>

<h3> 사용기술 </h3> <hr>
WINAPI, DFS

<h3> ETC </h3> <hr>
