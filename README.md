##= Release 0.8v =
**변경사항**
 - 로그인 시스템 구현
 - 방목록 시스템 구현
 - 전반적인 UI 개선
 - 배경음악 추가
 - ObjectPool 도입(기존의 ObjectManager 제거)
 - CallAfterFunc 제대로 사용
 - Timer 구현
 - Mob 구현 중에 있음(일단 주석처리)
 - 기타 여러 버그 수정 

**조작방법**
 - 캐릭터 이동 : 마우스 우클릭  
 - 스킬 사용 : Q or W or E + 마우스 좌클릭

##Skima.sln 빌드하는 법(Cloning 했을 때)
1. CommitAgain\Skima\cocos2d 폴더 안의 download-deps.py 실행   
2. Skima.sln 실행후 솔루션 탐색기에서 Skima프로젝트를 시작 프로젝트로 설정후 빌드   

##Skima.sln 빌드하는 법(zip파일로 받았을 때)
1. 깃허브의 Skima > cocos2d @4e645c > Download ZIP    
2. ZIP 압축을 푼 후, cocos2d 폴더 안의 download-deps.py 실행   
3. cocos2d-x-custom-3 폴더 안의 모든 파일 및 폴더를   
       \CommitAgain-Release_v0.5\CommitAgain-Release_v0.5\Skima\cocos2d에 넣습니다   
4. Skima.sln 실행후 솔루션 탐색기에서 Skima프로젝트를 시작 프로젝트로 설정후 빌드   
