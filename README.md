##= Release 0.5v =
**변경사항**  
 - 대대적인 서버 리펙토링
 - 서버와 클라의 캐릭터 위치 동기화 방법 개선
 - 클라의 좌표를 서버에서 방마다 다르게 매핑하게 하여 동시에 여러 게임 돌릴 수 있도록 함
 - 오브젝트 풀 개념 도입(서버의 ObjectManager, 클라의 EffectManager)
 - UnitType을 UnitID에 포함시켜 비트연산으로 타입 구별
 - 이동속도, 스킬 사거리, 이펙트 크기 등 여러 수치 조정
 - 새로운 스킬 'Teleport' 추가
 - 원격 서버 디버깅 셋팅
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
