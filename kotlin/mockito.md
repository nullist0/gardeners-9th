# Mockito-inline

테스트 코드를 사용할 때 Mockito를 사용하는데, `final` method나 `static` method의 경우에는 stuvbbing과 mocking이 지원되지 않는다. 이러한 문제를 해결하고자 `mockito-inline`이라는 모듈을 통해 JVM 으로 돌아가는 테스트 코드에서는 해당 기능을 제공하게 된다.

하지만 이러한 모듈이 있음에도, kotlin에서 여러 문제를 야기하는데 아래와 같은 문제를 야기한다.

- kotlin에서 `companion object`는 실제 컴파일된 코드에서는 `Companion`이라는 `public static final` 클래스로 정의되어 `static` method가 아니다.

`companion object`는 그리고 외부에서 주입할 수 있는 형태로 제공되지도 않으므로, 해당 함수를 Mockito로 테스트하고자 한다면 `@JvmStatic`를 이용하여 실제로 `static` 함수로 만들어주어야 한다.

이미 `static` method를 mockking하고 stubbing하는 것이 testing의 anti-pattern인데 어노테이션까지 붙어가며 처리를 해야하는지는 의문이다. 그래서 아래와 같은 방법을 추천한다.

- `static` method를 adapter 패턴으로 숨기고 해당 객체를 verify하기
- `static` method 자체를 테스트하지 않고 반환값을 assert하기
- `static` method 자체를 테스트하지 않고 인자로 넘긴 객체를 verify하기