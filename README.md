# 임베디드 시스템 기말 프로젝트
## 순천향대학교 사물인터넷 학과 5조
### 프로젝트 목록
- 버스 예약
- 버스 마스터 컨트롤
- 버스 앞문
- 버스 뒷문
- 흡연 감지

### 프로젝트별 세부사항
1. 버스 예약
- 사용 외부 라이브러리 : DFRobotDFPlayerMini.h

2. 버스 마스터 컨트롤

3. 버스 앞문
- 사용 외부 라이브러리 : DFRobotDFPlayerMini.h, Servo.h

4. 버스 뒷문
- 사용 외부 라이브러리 : Servo.h

5. 흡연 감지
- 사용 외부 라이브러리 : DFRobotDFPlayerMini.h

### 통신
- 버스 예약 <--> 흡연 감지 : SPI - 버스 예약 정보를 흡연 감지에 있는 LCD에 출력
- 버스 예약 <--> 버스 뒷문 : I2C - 버스 예약 정보를 버스 뒷문에 있는 LCD에 출력
- 버스 마스터 컨트롤 <--> 버스 앞문 : SPI - 버스 앞문 상태와 구동 명령을 전달
- 버스 마스터 컨트롤 <--> 버스 뒷문 : UART - 버스 뒷문 상태와 구동 명령을 전달

- DFPlayer <--> 아두이노 : UART - DF플레이어 구동