# Mockito

## Mockito-inline

테스트 코드를 사용할 때 Mockito를 사용하는데, `final` method나 `static` method의 경우에는 stuvbbing과 mocking이 지원되지 않는다. 이러한 문제를 해결하고자 `mockito-inline`이라는 모듈을 통해 JVM 으로 돌아가는 테스트 코드에서는 해당 기능을 제공하게 된다.

하지만 이러한 모듈이 있음에도, kotlin에서 여러 문제를 야기하는데 아래와 같은 문제를 야기한다.

- kotlin에서 `companion object`는 실제 컴파일된 코드에서는 `Companion`이라는 `public static final` 클래스로 정의되어 `static` method가 아니다.

`companion object`는 그리고 외부에서 주입할 수 있는 형태로 제공되지도 않으므로, 해당 함수를 Mockito로 테스트하고자 한다면 `@JvmStatic`를 이용하여 실제로 `static` 함수로 만들어주어야 한다.

이미 `static` method를 mockking하고 stubbing하는 것이 testing의 anti-pattern인데 어노테이션까지 붙어가며 처리를 해야하는지는 의문이다. 그래서 아래와 같은 방법을 추천한다.

- `static` method를 adapter 패턴으로 숨기고 해당 객체를 verify하기
- `static` method 자체를 테스트하지 않고 반환값을 assert하기
- `static` method 자체를 테스트하지 않고 인자로 넘긴 객체를 verify하기

## Argument captor

Observer 패턴을 사용할 때 해당 객체에 observer를 추가하는 것이 캡슐화된다면 observer을 실행하는지 테스트하기가 어려울 수 있다. 여기서 말하는 상황은 외부에서 주입된다면 mock 객체를 넣어서 처리하는 상황이 아니고, 외부 요인으로 해당 callback이 실행될 수 있으면서 해당 callback이 실행하여 처리되는 결과를 확인할 수 있는 상황이 아니다.

예를 들어 click event와 같은 경우, Android에서는 `Espresso` 라이브러리를 쓰거나 React에서는 `Cypresso`의 E2E 테스팅 라이브러리를 사용하면 외부 조건을 바로 실행할 수 있다. 하지만 이러한 E2E 테스팅은 매우 느리기 때문에 Unit test로 처리하고 싶은 경우에는 `ArgumentCapor`를 쓸 수 있다.

```kotlin

@Captor
private lateinit var clickListenerCaptor: ArgumentCaptor<View.OnClickListener>

@Test
fun testViewClick() {
    // given
    val mockedButton = mock<Button>()
    val clickListenerCaptor: View.OnClickListener = argumentCaptor()
    val mockedEventHandler: () -> Unit = mock()

    val viewBinder = TestViewBinder(binding)
    val mockedEventHandler: () -> Unit = mock()
    val bindinng: TestViewBinding = mock {
        on { button } doReturn mockedButton
    }
    val dummyUiState = UiState(onClickListItem = mockedEventHandler)

    // when
    viewBinder.updateUi(dummyUiState)

    // then
    verify(mockedButton).setOnClickListner(clickListenerCaptor.capture())
    clickListenerCaptor.value.invoke(mockedButton)
    verify(mockedEventHandler).invoke()
}
```