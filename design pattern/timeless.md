# 영원한 건축
---
디자인 패턴이라는 용어나 개념은 건축학에서부터 나온 개념이다. 크리스토퍼 알렉산더의 저서인 "패턴 랭귀지"에서부터 나왔는데, 본 책은 "패턴 랭귀지"의 전작이다.

## 공간

물리적인 위상으로써 건물내의 공간들은 패턴을 갖는다. 예를 들어 한 집에 존재하는 거실과 화장실 등등의 구성 요소가 건물내의 패턴에 해당된다. 하지만 이 공간적인 패턴들은 그 공간이 구현되는 문화에 따라 변화한다. 한국에서는 보일러 문화로 인해 좌식문화가 보편화 되어 있고, 서양권의 경우 벽난로 문화로 인해 좌식문확가 없다. 이러한 세부 요소로 인해 각각의 공간 패턴들이 만들어내는 사건 패턴은 변화할 수 있다.

## 사건 패턴

사건 패턴은 어떤 공간에서 사람들이나 환경이 발생시키는 사건들이다. 예시로는 가족간의 생활이나 회사 사무실의 생활, 그리고 자연적인 바람이나 수풀들 등이 그 예이다. 일반적으로 공간과 사건사이에는 인과관계가 존재하지 않는다. 공간이 의도적으로 지어져서 해당 사건 패턴이 발생할수도 있고, 사람들이 어떤 일정한 행동을 위해 사용하는 공간이 사건 패턴을 더 강화하는 공간으로 발전시킬수도 있다.

## 관계 패턴

공간 패턴은 어떠한 요소들의 관계를 정의하는 패턴이다. 건축 설계상에서 예를 들면 문이라는 요소에는 경첩이나 높이 등등의 관계가 같이 정의된다. 그래서 우리가 흔히 생각하는 어떠한 구성 요소도 실제로는 관계 패턴이 같이 정의되어 있다.

## 살아있는 패턴

건물들은 위와 같은 패턴들로 이루어져 있는데, 그 구현이 항상 일정하고 항상 같지 않다. 건물이나 도시를 설계할 때 항상 그 조건이 매번 다르기 때문이다. 예를 들어 `채광이 좋은 방`이라는 패턴을 만족하기 위해서는 태양의 각도, 건물의 각도 등에 의해 항상 창문과 방의 형태가 다르게 결정되기 때문이다. 오히려 정확한 수직성과 균일한 반복성이 더해진 패턴들은 좋지 못하다. 해당 조건에서 매우 불안정할 수 있기 때문이다.

이러한 관점에서 살아있는 패턴이란 자연과 같이 반복되지만 그 조건에 맞게 항상 유연하게 구현이 되는 일반적인 패턴 구조를 의미한다. 이러한 구조를 통해서 우리들이나 자연이 자연스럽게 행하고 싶은 행동을 가볍게 할 수 있을 수 있다. 책에서 언급한 것과 같이 너무나도 폐쇄적인 공원은 자유롭게 넘나들고 싶은 우리의 욕구를 만족시키지 못하고 부자연스럽다. 해당 건물이나 도시 안에 있는 개체들이 본인이 표하고자 하는 힘을 있는 그대로 표출할 수 있을 때 비로소 살아 있는 패턴이라고 볼 수 있다.

# 개발에서의 적용
---

영원한 건축에서 말하는 패턴과 같이 우리가 클래스라고 부르는 프로그램의 구성 요소도 분리할 수 없는 패턴들로 정의될 수 있다. 해당 저서에서 표현하는 패턴은 일정한 세부요소들을 제외하고 사고하도록 정의되어 있으므로 개발에 있어서도 특정한 구현을 위한 세부요소들이 무시된 개념으로 사고할 수 있다. 그래서 GoF의 디자인 패턴 저서에서도 동일한 방식으로 세부 사항을 무시한 개념으로 일반적인 요소로 접근한다.

각각의 패턴은 개발에서 디자인 패턴으로 아래와 상등한다고 느껴졌다.

- 사건 패턴: 객체들이 사용되는 패턴
- 관계 패턴: 클래스간의 관계와 계약으로써의 패턴

예를 들어 디자인 패턴의 생성 패턴은 아래와 같이 이해할 수 있을 것이다.

- 사건: 객체를 생성하는 사건
- 관계: 팩토리 패턴이나 빌더 패턴 등

이러한 사건과 관계속에서 특정 사용성을 정의하기 위해 세부조건이 구현되면서 우리가 실제로 사용하는 공간(클래스 구조)가 만들어지는 것으로 이해하였다.

## 살아 있는 패턴

그때그때마다 구현되는 세부 구현사항은 달라지지만, 우리가 원하는 API의 의도에 맞게 구현되는 Interface와 같이, 패턴에서는 각각의 class나 interface들이 우리가 원하는 의도에 맞게 구현되도록 서로간의 관계를 정의한 것으로 이해하였다. 살아 있는 패턴은 우리가 원하는 의도가 적절하게 부자연스럽지 않게 구현하는 패턴일 것이다.

SOLID나 Component 설계 원칙을 말할 때 우리들은 `수정을 최소화하고`, `기능 추가에는 쉽게` 만드는 것을 주 목표로한다. 그러면서 자칫 복잡해져 상기한 목표를 저해할 수 있는 상황을 자연스럽게 반복되는 패턴으로써 정의한 내용이 디자인 패턴이라고 느껴졌다.

## 우리의 패턴 언어

패턴의 정의를 다시 생각하면, 주어진 장소에서 계속해서 반복되면서도 시시각각 조금씩 다른 형태로 표현되는 활동과 공간이 결합된 어떤 것이다. 어떻게 패턴은 생기고, 패턴에 맞는 건물이 서로 다른 모습으로 구현되는 것일까?

사실 패턴은 그것이 정의하는 실체를 만들기 위해 우리가 해야하는 일종의 규칙이기 때문이다. 패턴들을 우리가 사고하고 만들어 내기 위해 패턴은 우리가 사용하는 것과 유사한 패턴 언어를 따른다.

예를 들어 가장 단순한 언어에는 수학에서의 집합과 논리언어를 생각해볼 수 있는데, 패턴 언어에서는 패턴이 원소이고 두 원소를 잇는 방법이 패턴간의 유의미한 규칙들이다. 이러한 패턴들은

1. 패턴들은 사회에 합당한 구조만이 유지된다.
2. 패턴들은 우리가 일관성 있는 공간 배치를 만들 수 있는 실질적인 능력을 부여한다.

패턴들은 어디서 나오는 것일까? 패턴들은 사람들의 경험과 사회로부터 출발한다. 새로운 패턴의 출현은 기본적으로 근간이 되는 지점이 필요하기 마련인데, 이러한 근간들이 사람들의 경험과 사회에 축적된 패턴들로 볼 수 있다. 그리고 지속적으로 반복되고 이어지는 이유는 또다시 사람들이 해당 패턴을 언어에 녹여서 사용하기 때문이다.

소프트웨어의 예를 들면 책임과 역할이 있는 객체간의 관계가 패턴이 되고 해당 패턴은 반복되기에 GoF가 정리한 디자인 패턴임으로 이해하였다. 수많은 경험을 쌓은 GoF가 지속적으로 반복되는 패턴언어를 정립한 것이다.