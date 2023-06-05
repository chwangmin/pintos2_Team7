Brand new pintos for Operating Systems and Lab (CS330), KAIST, by Youngjin Kwon.

The manual is available at https://casys-kaist.github.io/pintos-kaist/.

### 추가 참고 자료

- [KAIST Pintos Slide Set](https://oslab.kaist.ac.kr/pintosslides/)
- [한양대 핀토스 강의 자료](http://broadpeak.kaist.ac.kr/wiki/dmcweb/download/%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C_%EC%8B%A4%EC%8A%B5_%EA%B0%95%EC%9D%98%EC%9E%90%EB%A3%8C.pdf)

### 테스트 환경

AWS EC2 Ubuntu 18.04 (x86_64)

    $ sudo apt update
    $ sudo apt install -y gcc make qemu-system-x86 python3

## CH1. Alarm clock, Priority Scheduling

제대로 동작되는지 테스트 결과 확인

    $ source ./activate
    $ cd threads
    $ make check

### Alarm clock
- alarm : 호출한 프로세스를 정해진 시간 후에 다시 시작하는 커널 내부 함수
- 기존 핀토스에서는 알람 기능이 Busy waiting을 이용하여 구현되어 있습니다.
- busy waiting은 스레드가 CPU를 점유하면서 대기하고 있는 상태로, 권한을 얻을 때까지 확인하는 것을 의미합니다. 이 경우 CPU의 자원을 불필요하게 낭비하기 때문에 좋지 않은 쓰레드 동기화 방식입니다.
- 이 알람 기능을 sleep/wake up을 이용하여 재구현 하는 것이 목표입니다.

<img width="692" alt="스크린샷 2023-06-05 오전 10 58 48" src="https://github.com/Riudiu/pintos/assets/86466976/9b74d673-0334-4c96-8272-fd3f0abdf9c3">

<img width="927" alt="스크린샷 2023-06-05 오전 11 01 05" src="https://github.com/Riudiu/pintos/assets/86466976/4bff3c57-77e0-49db-b572-02d5888cf58b">

### Priority Scheduling

- 기존 핀토스의 스케줄러는 라운드 로빈으로 구현되어 있습니다. 
- 라운드 로빈 스케줄링은 시분할 시스템을 위해 설계된 선점형 스케줄링의 하나로서, 우선순위와 관련 없이 시간 순서대로 CPU를 할당하는 방식입니다.
- 이를 우선순위를 고려하여 스케줄링 하도록 수정하는 것이 목표입니다.

![스크린샷 2023-06-05 오전 11 13 56](https://github.com/Riudiu/pintos/assets/86466976/1877700d-2692-4bdd-9634-a93b4bf97bc9)

### Priority Inversion Problem

> 우선순위가 높은 쓰레드가 우선순위 낮은 쓰레드를 기다리는 현상

- 우선 순위 스케줄링의 문제점 중 하나는 'priority inversion'입니다. 
- H, M, L 을 각각 높은, 중간, 낮은 우선 순위의 thread라 해봅시다. H가 L을 기다려야 하고(예를 들면, L이 lock을 걸은 경우) M은 ready list에 있다면, L이 CPU 이용 시간을 얻지 못하기 때문에, H도 절대 CPU를 사용하지 못하게 될 것입니다.
- Priority donation 구현하여 lock을 보유한 낮은 우선순위의 thread에게 자신의 우선순위를 기부하도록 합니다. 그리고 lock이 풀리면 기부한 우선순위를 다시 가져오도록 구현하는 것이 목표입니다.

![스크린샷 2023-06-05 오전 11 23 59](https://github.com/Riudiu/pintos/assets/86466976/993b2e64-4ddc-4b04-a514-ad12890639a7)