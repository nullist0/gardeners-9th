# Lifecycle

Android에서 React와 유사하게 여러 lifecycle callback이 있다. 하지만 React와는 달리 Lifecycle이 다른 component에 유연하게 분산되는 구조가 아닌 Activity나 Service와 같은 컴포넌트에 매우 의존적이게 된다. 이를 해소하기 위해 observer 패턴으로 Lifecycle 문제를 해소하였다.

## Testing

Lifecycle-aware한 component들은 lifecycle에 따른 테스트 코드를 작성하여 의도한 라이프사이클이 무엇인지 문서화하는 것이 좋다. 이를 위해 `LifecycleOwner`의 Test 버전이 존재한다.

Lifecycle에 따른 값을 검증하고자 한다면 다음과 같이 검증할 수 있다.
```kotlin
@Test
fun testExpectation() {
    // given
    val testLifecycleOwner = TestLifecycleOwner()
    val expectedOnCreate = createExpectation()
    val target = TargetClass(testLifecycleOwner.lifecycle)

    // when
    testLifecycleOwner.handleLifecycleEvent(Lifecycle.Event.ON_CREATE)

    // then
    assertEquals(expectedOnCreate, target.foo())
}
```

해당 component가 lifecycle에 맞춰서 어떠한 LiveData나 Flow를 구독하고 해제해야 한다면 다음과 같이 테스트할 수 있다.

```kotlin
@Test
fun testNoPropagateStateWhenOnStop() {
    // given
    val testLifecycleOwner = TestLifecycleOwner()
    val stateFlow = StateFlow<Int>(0)
    val domainObject = mock()
    val target = TargetClass(testLifecycleOwner.lifecycle, stateFlow, domainObject)

    // when
    testLifecycleOwner.handleLifecycleEvent(Lifecycle.Event.ON_STOP)
    stateFlow.update { it + 1 }

    // then
    verifyNoInteractions(domainObject)
}

@Test
fun testPropagateStateWhenRecoverToOnStart() {
    // given
    val testLifecycleOwner = TestLifecycleOwner()
    val stateFlow = StateFlow<Int>(0)
    val domainObject = mock()
    val target = TargetClass(testLifecycleOwner.lifecycle, stateFlow, domainObject)

    // when
    testLifecycleOwner.handleLifecycleEvent(Lifecycle.Event.ON_STOP)
    stateFlow.update { it + 1 }
    testLifecycleOwner.handleLifecycleEvent(Lifecycle.Event.ON_START)

    // then
    verify(domainObject).someFunctionToBeCalled()
}
```