# ToC

---

# 사용자 의견에 귀 기울이기

---

왜 사용자 의견을 수용하고 문서를 고쳐야하는지는 명백하다. 아래의 문서의 용도에 관한 내용을 확인해보자.

- 문서의 용도
    - 대표적인 사용자와의 소통 방법이다.
    - 사용자의 니즈를 해결하는 방법을 소개한다.
    - 사용자가 제품을 이해하고 생산성을 높이도록 하는 데 중요한 역할을 한다.

문서의 용도를 위해 사용자의 피드백으로 어느 부분이 성공적이고, 어느 부분을 보충해야 하는지 확인해야 한다. 이를 위해 이번 장에서는 이하의 내용을 설명한다.

- **사용자 피드백 채널** 만들기
- 피드백에 대한 **조치 취하기**
- 사용자로부터 받은 **피드백 분류하기**

# 피드백 채널 만들기

---

**피드백 채널**이란 사용자가 개발사와 연결을 맺을 수 있는 특정 수단이나 공간이다. 피드백 채널에는 여러가지 종류가 있는데 아래와 같다.

- 문서 페이지를 통해 직접 피드백 받기
- 고객 지원 문제 모니터링하기
- 문서 감정 수집하기
- 사용자 설문조사 만들기
- 사용자 위원회 만들기
- 사용자와 개별적으로 소통하기
- 사용자와 소규모 회의를 진행하기

문서를 통해서 받을 수 있는 피드백 채널에 대해서 알아보자.

> 💡 사용자는 제품을 이해하기 위해 문서에 접근하는 것이므로 독자에게 유용한 정도의 피드백 채널만 운영하는 것이 중요하다.

</aside>

## 문서 페이지를 통해 직접 피드백 받기

- 목표: 사용자가 콘텐츠에서 직접 응답할 수 있는 기회를 제공하는 것
- 장점: 구체적이고 특정한 문제를 발견했을 때 개발사에게 알려주기 용이
- 구현 방법
    - 이메일로 접수를 받거나
    - 이슈 트래커에 등록을 받거나
    - 템플릿이 있는 자체 사이트로 등록을 받거나

### 예시: flutter

[Flutter docs example](https://docs.flutter.dev/get-started/install/linux) 에서 우측 상단 bug 아이콘을 누르면 직접 피드백을 보낼 수 있다.

## 고객 지원 문제 모니터링 하기

- 목표: 동일한 문제를 지속적으로 겪고 있는지 확인하는 것
- 장점
    - 이미 자체 피드백 채널이 개설되어 있을 수 있음
    - 고객 문제를 문서화하는 방법이 이미 있을 수 있음
    - 임시 대처법을 문서화하고 생성하기 위한 사고 관리 시스템이 있을 수 있음

## 문서 감정 수집하기

**문서 감정**은 독자가 문서에 대해 느끼는 감정을 의미한다.

- 목적: 실제로 문서가 도움이 되었는지 확인하여 낮은 점수의 페이지를 개선하는 것
- 장점
    - 문제를 해결하고 해당 페이지의 후속 결과를 측정하기에 용이함
    - 높은 평점을 받는 페이지의 원인을 아는 경우 다른 페이지에도 적용하여 성공을 재현할 수 있음
- 단점
    - 설문조사에 많은 응답이 있어야함
    - 문서 변경 후 후속 평가를 위해서도 다시 많은 수의 응답을 받아야함
    - 독자의 맥락에 따라 페이지가 저평가 되는 원인이 문서에 없을 수도 있음
- 구현 방법
    - 문서 내에 예/아니오 버튼과 같이 도움이 되었는지 여부에 관한 짧은 응답을 할 수 있는 란을 제작

### 예시: Android docs

[Android docs example](https://developer.android.com/guide) 에서 우상단과 하단에 `Was this helpful` 란에서 확인할 수 있다.

### 예시: Unity3d doc

[Unity docs example](https://docs.unity3d.com/Manual/UnityOverview.html)의 하단에서 별점을 줄 수 있는 란을 확인할 수 있다.

## 사용자 설문조사 만들기

- 장점
    - 집계하기 쉬운 자동화된 방식 사용 가능
    - 제품과 문서에 대한 구체적인 질문이 가능
    - CSAT와 같은 기준으로 측정한다면 좀 더 객관적으로 사용자 피드백 변화 측정 가능

## 사용자 위원회 만들기

**사용자 위원회**는 제품에 대해 조언을 제공할 현재 사용자 또는 잠재적 사용자로 이루어진 그룹이다.

- 장점
    - 새로운 서비스와 문서에 대한 피드백을 받을 수 있음
    - 다양한 피드백 방법을 적용하기 쉬움
    - 핵심 사용자 그룹과의 관계를 구축하는데에 도움이 됨
- 단점
    - 제품에 중요한 영향을 미치는 사용자의 수가 적어야 함

# 피드백에 대해 조치 취하기

---

피드백에 대해 조치를 취하기에는 이하의 **프로세스**가 필요하다.

- 피드백 분류하기
- 피드백 요구사항 정의하기
- 피드백 조치하기
    - 추가적인 정보를 요구 후 추가 조치
    - 피드백 무시
    - 문서 및 제품 개선

여기서 분류하는 작업이 제일 중요한데, **분류(triage)**란 피드백을 선별하고 우선순위를 지정하는 작업이다. 유한한 시간에 가장 가치있는 개선사항을 선택하여 적용하는 것이 목적이다.

그리고 위와 같은 **표준 프로세스**를 정의하는 이유는 여럿있지만 아래와 같은 이유가 대표적이다.

- 사용자 문제에 대한 응답 시간 단축
- 요청된 작업이 미처리 상태로 계속 남아 있는 것을 방지
- 문제에 대해 표준화된 우선순위 설정
- 한정된 자원을 가장 필요하고 영향이 큰 변경 작업에 투입

## 피드백 분류하기

피드백을 분류하기 위해서는 아래의 질문을 통해 우선순위를 결정하는 것이 중요하다.

- 문제가 유효한가?
- 문제를 해결할 수 있는가?
- 문제가 얼마나 중요한가?

### 문제가 유효한가

피드백을 볼 때에는 `신뢰하되 확인` 하는 것이 중요하다. 이유는 문서에서 시작된 피드백이라도 문서와 일절 관계없을 수 있기 때문이다. 그래서 *문서* 피드백이 **유효한**지 알아보고 아니라면 다른 팀에게 전달하는 것이 좋다. 문서에 대한 피드백이 아닌 예시는 아래와 같다.

- 제품 피드백: 기능이 예상대로 작동하지 않거나 원하는 기능이 누락됨
- 고객지원 요청: 로컬 환경에서 특정 작업을 완료하는 데 어려움을 겪음

### 문제를 해결할 수 있는가

문제를 해결하여 조치할 수 있으려면 다음과 같아야 한다.

- 중복되지 않음
- 재현 가능함
- 범위가 정해짐

버그 이슈를 해결할때와 동일한 수순인데 각각이 성립하지 않는 경우에는 아래와 같은 조치를 시도할 수 있다.

- 중복 이슈가 존재
    
     ⇒ 중복된 이슈가 있다면 무의미한 리소스를 반복해서 사용할 수 있으므로 중복 이슈는 닫고, 중복 이슈가 많다면 우선순위를 높이는 것을 고민해보자.
    
- 재현이 불가능함
    
     ⇒ 로컬에서의 문제일 가능성이 있으므로 필요한 환경이 갖춰지도록 문서를 수정할 필요를 고민해보자. 혹은 사용자에게 문제에 대한 정보를 추가로 요청하여 구체적인 문제를 해결하자.
    
- 범위가 정해지지 않음
    
     ⇒ 리소스가 무한한 것이 아니므로 적절한 수정가능한 정도의 조치 범위로 정리할 수 있는 작업으로 분해해서 조치하자. 이것이 불가능한 경우 (제품을 아예 새로 만들어야 하는 경우)에는 사용자에게 추가 문의를 통해 개선할 수 있다.
    

### 문제가 얼마나 중요한가

문제가 문서의 문제이고, 해결할 수 있는 방안이 정해졌다면, 문제를 실제로 언제 수행할지만 결정하면 된다. 이는 우선순위에 관한 문제인데 아래와 같은 사항으로 정리할 수 있다.

- 문제가 얼마나 중요한가
- 문제를 얼마나 빨리 해결해야 하는가

### 피드백 분류하기 예시: Flutter

분류 작업에 관한 wiki: https://github.com/flutter/flutter/wiki/Triage#triage-process-for-teams

이슈 수선순위에 관한 wiki: https://github.com/flutter/flutter/wiki/Issue-hygiene#priorities

이슈 분류 작업과 이후 레이블을 통해서 https://github.com/flutter/flutter/issues 에 정의해두고 있다.

## 사용자에게 후속 조치 취하기

피드백은 사용자와 소통하는 도구인데 조치를 취하고 있는 과정을 설명하지 않으면 아무런 의미가 없다. 그러니 조치하고 있다면 설명하는 것이 중요하다.

### 예시: Spring boot

Doc 수정 issue를 이와 같이 관리하고 정정 과정을 표기하고 있다.

https://github.com/spring-projects/spring-boot/issues/35032

### 예시: Kafka

Doc 수정 issue를 이와 같이 관리하고 정정 과정을 표기하고 있다.

https://issues.apache.org/jira/projects/KAFKA/issues/KAFKA-15483?filter=allopenissues

# 요약

---

- 문서는 사용자와 소통하기 위한 주요 방법으로, 사용자는 피드백을 통해 소통하길 원한다.
- 다양한 피드백 채널을 필요에 따라 구축하여 피드백을 받아야 한다.
- 적절한 피드백인지 분류 및 우선순위를 결정한 이후에는 조치를 하고 후속 조치를 전달하라.