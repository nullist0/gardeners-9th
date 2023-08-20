# inject-pacakge

Java의 Dependency Injection 스펙은 [JSR 330](https://jcp.org/en/jsr/detail?id=330)에 정의되어 있다. 안드로이드도 당연히 DI를 위해서 이와 같은 스펙을 사용한다.

## javax.inject 패키지

JSR-330은 javax.inject 패키지에 정의되어 있는데, 해당 패키지에는 아래와 같은 내용을 정의한다. 외에도 다른 어노테이션도 있다.

- @Inject 어노테이션
- Provider\<T\> 인터페이스

@Inject 어노테이션은 의존성주입을 할 함수나 생성자에 명시하기 위한 용도로 사용되며, Provider 인터페이스는 해당 의존성을 생산하고 제공하는데에 사용하도록 정의되어 있다.

의존성 주입을 할때에 `Factory`를 만들어 객체의 생성을 간편하게 만드는 패턴을 직접 생성해주고, 테스트 가능하도록 만드는 것이 주요한 목표이다. 예를 들어 해당 패키지의 예시를 발췌해보자.

```kt
class Stopwatch @Inject constructor(val timeSource: TimeSource) {
    fun start() { ... }
    fun stop(): Long { ... }
}
```

이때 `TimeSource`가 `Stopwatch`의 의존성이 된다. `TimeSource`를 생성하는데에 복잡한 경우나, 생성자가 변경될 가능성이 많은 경우 `@Inject` 어노테이션과 `Provider`를 이용하여 해당 의존성을 주입하도록 구현하는 것이다. 각각의 DI 라이브러리 구현체는 서로 다른 방법으로 해당 의존성을 설정할 수 있고 값을 제공할 수 있다.

## Reference
- https://ryanharter.com/blog/2023/08/simple-apis-are-elegant-apis/
- http://javax-inject.github.io/javax-inject/api/javax/inject/package-summary.html
- https://jcp.org/en/jsr/detail?id=330