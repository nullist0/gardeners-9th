# 도입 - 서로 다른 프로세스 하지만 같은 결과

---

저자는 서로 다른 프로세스로 구현이 되었지만 동일한 결과가 일어난 상황에 도달했다.

- 프로세스 1
    - 기술 분석가에 의해 도출된 너무나도 복잡한 모델
    - 구현상 불가능한 모델로인해 개발자에 의해 구현된 모델로 도출된 구현
- 프로세스 2
    - 아무런 일반화와 추상화를 사용하지 않고 구현된 구현

결과는 동일했다.

> 기능성은 갖췄지만 비대하고 매우 이해하기 어려웠으며, **유지보수가 불가능**했다.
> 

<aside>
ℹ️ 클린 아키텍처로부터 소프트웨어가 **소프트**인 이유는 변경이 가능하기 때문이다. 아니라면 하드웨어와 동일하다. 이러한 점에서 강하게 말하면 두 경우 모두 **소프트웨어**로서는 가치가 없다.

</aside>

# MODEL-DRIVEN DESIGN

---

왜 앞서 일어난 두 시나리오가 같은 결과를 맞이하게 되었는가? 모델에는 크게 세 가지의 쟁점이 존재한다.

- 구현으로서의 모델 (= 코드)
- 도메인으로서의 모델 (= 분석 모델)
- 보편 언어로서의 모델

첫번째 사례에서는 **도메인으로서의 모델**에만 치중한 결과이며, 두번째 사례는 **구현으로서의 모델**에만 치중하게된 사례이다.

> 이유가 어찌되었든 결과적으로 설계의 기반이 되는 개념이 부족한 소프트웨어는 기껏해야 해당하는 소프트웨어의 행위를 설명하지 못한 채 그저 유익한 일을 수행하는 메커니즘 정도밖에 되지 않는다.
> 

모델 주도 설계에서는 이러한 이분법적인 모델 구조를 인정하지 않는다. 모델은 **순수한 기술적 쟁점을 제외한 모든 개념과 구현 가능성**을 포괄해야 한다. 둘 중 하나라도 결여된 모델이 발견된다면 새로운 모델을 찾아내고 지속적으로 모델을 하나로 관리해야 한다. 그래야만…

> 모델링과 설계 프로세스가 **단 하나의 반복 고리**를 형성할 수 있다.

# 모델링 패러다임과 도구 지원

---

프로그래밍 언어는 크게 2가지 패러다임이 존재한다.

- 절차형 프로그래밍 언어
- 객체지향 프로그래밍 언어

이 중에서 모델 주도 설계에 적합한 패러다임은 **객체지향 프로그래밍 언어**이다. 우리는 모델링을 할때 기본적으로 두 가지를 하나의 개념에 묶고는 한다.

- 모델 구성요소가 다른 모델 구성요소간의 해야하는 행위
- 모델 구성요소가 가져야하는 본연의 정보

우리는 이 둘을 묶은 개념이 실제 메모리에 올라가 있는 데이터를 흔히 **객체**라고 한다.

<aside>
ℹ️ 클린 아키텍처의 스터디에서 객체지향이 아키텍처에 유용한 이유로 프레임워크에 직접적인 의존을 하지 않고, 의존성 역전을 할 수 있다는 점도 배웠었다.

</aside>

## 왜 절차형 언어는 어려운가?

순수하게 절차적인 언어의 경우 데이터를 **기술적으로 조작할 뿐** 모델 구성요소를 표현할 수 있는 방법이 없기 때문이다.

### 예시: Point

단순하게 **한 점으로부터 한 점까지의 거리**를 구하고자할 때를 생각해보자. 객체지향 언어에서는 요구조건과 동일한 문장으로 코드를 작성할 수 있다.

```kotlin
class Point(val x: Double, val y: Double) {
    // PointA.distanceFrom(PointB)
    fun distanceFrom(point: Point): Double {
        val dx = abs(point.x - x)
        val dy = abs(point.y - y)
        return sqrt(dx * dx + dy * dy)
    }
}
```

```c
struct Point {
	double x,y;
};

// 한 점에서 한 점까지의 거리를 구조할 수 없다.
// 이 함수는 그저 두 점사이의 거리를 구할 뿐이다.
double distance(struct Point* p1, struct Point* p2) {
	double dx = pl->x - p2->x;
	double dy = pl->y - p2->y;
	return sqrt(dx*dx+dy*dy) ;
}
```

# 내부 드러내기: 왜 모델이 사용자에게 중요한가

---

모델 주도 설계를 하게되면 모델링은 **도메인 문제사항**과 **구현 문제사항**, **보편 언어** 모두를 아우르는 존재가 되는데, 이를 사용자에게 표현하지 않게 되면 문제상황에 도달하게 될 수 있다.

## 예시: 인터넷 익스플로러 즐겨찾기 기능

인터넷 익스플로러 즐겨찾기 기능을 구현하는 구현 제약사항에 의해 아래와 같은 개념이 모델링에 추가되었지만 사용자에게 어색함을 준 예시이다.

- 구현상의 제약사항: 즐겨찾기 내용을 파일로서 저장한다.
- 사용자에게의 표기: 파일과 동일한 구조로 보여주지 않았다.
- 사용자의 어색함: 즐겨찾기 이름을 변경할 때 파일명 규칙에 대한 에러를 발견하게 되었다.

<aside>
💡 우리는 이를 흔히 UX가 올바르지 않다고 표현하기도 한다.

</aside>

차라리 파일이라는 제약사항을 UI로서도 표현하여 유저에게 이를 명시하라.

# HANDS-ON MODELER

---

흔히 회사에서는 제조업의 판단을 따라하여 아래와 같이 책임을 엄격하게 구분하려 한다.

- 설계자의 책임
- 구현자의 책임

제조업에서는 이와같은 행태가 어느정도 현실적으로 돌아가지만, 소프트웨어 설계에 있어서 모델러와 개발자의 영역을 이와같이 구분하는 경우에 문제가 발생한다.

- 개발자의 관점에서 모델을 다룰지 않을 때의 문제
    - 애플리케이션을 대상으로 모델이 동작하게 만드는 법을 모른다면, **그 모델은 소프트웨어와 무관**해진다.
    - 코드의 변경과 모델의 변경이 동등하다는 점을 모른다면 리팩터링은 **구현에 손쉬운 방향으로 진행되므로** 모델을 약화시킬 것이다.
- 모델러의 관점에서 개발을 하지 않을 때의 문제
    - **구현상의 제약조건을 감안하는 능력을 갖추지 못할** 것이다.
    - 모델은 결국 실용적이지 않은 **이론적에 그치는 분석 모델로 돌아가게 될 것**이다.

결론적으론 

- 모델에 기여하는 모든 기술자는 프로젝트 내에서 수행하는 일차적 역할과는 상관없이 코드를 접하는 데 어느정도 시간을 투자해야 한다.
- 코드를 변경하는 책임이 있는 모든 이들은 코드를 통해 모델을 표현하는 법을 반드시 배워야 한다.
- 모든 개발자는 모델에 관한 일정 수준의 토의에 깊이 관여해야 하고 도메인 전문가와도 접촉해야 한다.
- 다른 방식으로 모델에 기여하는 사람들은 의식적으로 코드를 접하는 사람들과 보편 언어를 토대로 모델의 아이디어를 나누는 데 적극 참여해야 한다.
