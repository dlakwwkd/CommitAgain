Release_v0.2 (4주차)
--
- 싱글플레이는 아직 구현되지 않음
- 한 컴퓨터에서 테스트할 수 있도록 클라의 서버접속IP를 127.0.0.1로 고정
- (네트워크 테스트까지 끝마쳤지만, 배포버전은 일단 이렇게 하였음)
- 로그인 아이디는 일단 클라에서 랜덤으로 생성하도록 하였음

  
서버
--

- 접속시 로그인 처리 및 방 생성
- 레디 처리, 자동 게임 시작 처리, 클라와 로딩 동기화
- 서버에서 게임을 띄우고, 캐릭터 생성 후 클라에 전달 구현
- 연결 끊김에 따른 플레이어 아웃 처리, 게임방 파괴 구현
- 각 클라들의 마우스 클릭 정보를 받아 캐릭터 이동 구현


클라이언트
--
- 메인메뉴 구현
- 네트워크 접속하는 과정 GUI화
- 로딩 화면 구현, 서버와의 전송 과정 동기화
- 서버의 유닛 정보 받아와 스프라이트 띄우기 구현
- 마우스를 이용한 유닛이동 정보를 서버에 전달 
- 서버에서 받은 유닛들의 이동정보에 따른 위치좌표 갱신 


실행방법
--
1. zip파일 받은 후 Release_v0.2 폴더 압축해제
2. 서버 실행(SkimaServer.exe)
3. 클라 2개 실행(Skima.exe)
4. 클라1 : 멀티플레이 -> 서버 접속 -> 방 생성, 
   클라2 : 멀티플레이 -> 서버 접속 -> 방 참여
5. 둘다 게임 시작을 누르면 자동으로 게임이 시작 됨
6. 마우스 우클릭으로 유닛을 이동시켜 볼 수 있음


조작법
--
마우스 우클릭 : 캐릭터 이동
