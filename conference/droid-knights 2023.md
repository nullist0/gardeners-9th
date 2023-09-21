# Droid Knights 2023 Review

## Session 2. Anddroid MVVM 패턴 접근법

여러 아키텍처 패턴이 안드로이드에 공개되어 있다. 예를 들어 아래와 같다.

- Android Architecture: MVVM + UiState + Compose / XML
- Slack circuit
- Airbnb mavericks
- tivi Android app

### With MVVM: Problem

아래와 같은 시나리오를 개발하는 예제를 알아보자.

1. 목록에서 리스트 삭제 버튼 클릭
2. 삭제 경고 alert 표시
3. Pincode 입력
4. 리스트 삭제 처리 완료

```kt
class ViewBinder(private val viewModel: ListViewModel) {
    init {
        lifecycleScope.launch {
            viewModel.listUiStateLiveData.collect(::bindView)
        }
    }

    // ...
    fun bindView(uiState: ListUiState) {
        listAdapter.submit(
            uiState.items.map {
                it.toListItem { 
                    showAlert(it, ::tryDelete)
                }
            }
        )
    }

    private fun showAlert(
        listItem: ListItem,
        onClickOk: (String) -> Unit
    ) {
        // ...
    }

    private fun tryDelete(item: Item, pinCode: String) {
        val isDeleted = viewModel.tryDelete(item, pinCode)
        // ...
    }
}
```

위와 같이 `ViewModel`이 비즈니스 로직을 갖고 있기 때문에 `View`와 함수 호출을 번갈아가면서 처리해야 한다. 하지만 이와 같은 경우 두가지 문제가 생긴다.
- `ViewModel`의 로직을 테스트 하기 위해 이러한 핑퐁을 시뮬레이션 하듯이 처리해야 한다.
- 화면에 실제로 경고 alert이 표시되는지 테스트하기 위해서는 UI testing해야 한다.

```kt
@Test
fun test() {
    val viewModel = // ...

    val uiState = viewModel.listUiStateLiveData.value
    val item = uiState.items.first()
    val pinCode = // ...
    viewModel.tryDelete(item, pinCode)
    val actualUiState = viewModel.listUiStateLiveData.value

    assert(noFirstItemUiState, actualUiState)
}
```

하지만 우리는 아래와 같은 점을 원한다.
- Ui testing 없이 경고 alert이 보여주는 로직이 있는지 확인하고 싶다.
- `ViewModel`과의 핑퐁 없이 로직을 확인하고 싶다.

### Solution in 퍼핀

퍼핀에서는 위와 같은 장점을 위해 모든 처리를 `ViewModel`에서 `Flow`로 처리한다. 또한 테스트를 아래와 같이 구성한다.

```kt
class ListViewModel {
    fun deleteItem(item) {
        uiEventFlow.emit(DialogEvent.Delete)
        uiEventFlow
            .filter { it is OkEvent }
            .collect { uiStateFlow.emit(ListUiState(...)) }
    }
}
```

```kt
@Test
fun test() = runTest {
    val viewModel = // ...
    val uiEventFlow = // ...
    val uiStateFlow = // ...
    val item = // ...
    val items = // ...

    viewModel.deleteItem(items)
    assertEquals(DialogEvent.Delete, uiStateFlow.value)

    uiEventFlow.emit(OkEvent(pinCode))
    assertEquals(ListUiState(items.filterNot { it == item }), uiStateFlow.value)
}
```

### Advantage

- Ui에 집중한 코드만 작성할 수 있다.
- 로직은 Flow로 모두 비동기 처리할 수 있다.
- Single Activity Architecture 도 쉽게 가능하다.
- KSP 적용도 가능하다.
- QA test를 자동화된 테스트로 작성할 수 있다.

### Disadvantage

- Flow 공부를 위한 learning curve가 높아진다.

### Conclusion

이렇게 개발하자는 의미가 아니라, 개발 편의성이 부족하면 필요한 아키텍처를 개발하는 것이 좋다는 걸 보이고 싶었다.