# ViewModel

`ViewModel`은 `UiState`를 노출하고 `Business logic`을 담당하는 클래스이다.

- `UiState`: Android platform에 의존하지 않고 화면에 보여야하는 정보를 담는 객체이다.
- `Business logic`: 애플리케이션을 가치있게 만드는 비지니스를 만족하기 위한 로직이다.

## Lifecycle of ViewModel

`ViewModel`는 `Activity`와 lifecycle을 다르게 갖는다. 왜냐하면 Configuration change에 의해서 `Activity`가 재생성되어도 유지되어야하는 로직과 정보를 갖기 때문이다. 같은 동일한 화면의 경우 보여야하는 비지니스 정보는 유지되어야 하므로 lifecycle이 다르게 처리된다.

- Configuration change에 의해서 `onDestroy` 될때는 `ViewModel`이 소멸하지 않는다.
- 이외의 실제로 `onDestroy`를 하여 재생성되지 않은 경우에는 `ViewModel`이 같이 소멸한다.

`ViewModel`의 lifecycle이 `Activity`나 `Fragment`와 다르기때문에 `ViewModel`에 해당 인스턴스들을 넘겨주어서는 안된다. 즉, `Context`와 같은 객체를 넘기게 되면 이미 파괴한 객체를 사용하게 되므로 주의해야 한다.