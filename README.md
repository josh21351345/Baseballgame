UBlueprintFunctionLibrary를 상속받아 블루프린트에서 호출할 수 있도록 제작되었습니다.

1) 랜덤 숫자 생성 (StartNewGame)
  1~9까지의 숫자를 배열에 저장한 후, 랜덤하게 3개를 선택하여 Answer로 설정
  모든 플레이어의 시도 횟수를 초기화

2) 입력 검증 (IsValidGuess)
  입력된 문자열이 3자리인지 확인
  1~9 사이의 숫자로만 이루어져 있는지 확인
  중복된 숫자가 포함되어 있지 않은지 검사

3) 스트라이크 / 볼 판정 (CheckStrike, CheckBall)
  같은 위치에 같은 숫자가 있으면 스트라이크
  다른 위치에 같은 숫자가 있으면 볼
  FindChar를 사용하여 해당 숫자가 존재하는지 확인

4) 입력 처리 (ProcessGuess)
  플레이어별 입력 횟수를 기록하고 3회 초과 시 입력을 막음
  정답을 맞추면 게임을 초기화하고 승리 메시지를 반환
  정답이 아닐 경우 스트라이크 / 볼 개수를 출력
  모든 플레이어가 기회를 소진하면 자동으로 게임 리셋
