# Fragment

안드로이드에서 `Fragment`는 Android 3.0에서 나왔다. 목표는 아래와 같다.

- 독립적인 Lifecycle을 갖는다
- Activity와는 달리 host할 component(Activity, Fragment)가 필요하다.
- Backstack을 갖는다.
- UI event를 처리할 수 있는 layout을 갖는다.

Fragment에는 아래와 같은 구성 요소를 갖는다.

- Framgnet Manager: Fragment를 host에 관리하는 역할을 갖는다.
- Fragment Transaction: Fragment를 Backstack의 원소로써 관리한다.
- Fragment Lifecycle: Fragment의 Lifecycle에 맞는 데이터를 관리한다.

## FragmentManager

`FragmentManager`는 `Fragment`를 추가하고 삭제하는 책임을 갖는 클래스이다. 이때  `Fragment`를 추가하고 관리하기 위해 `FragmentTransaction`을 생성하고 이를 Android Handler를 통해 실행시킨다. `Fragment`는 자신만의 Back stack을 갖기 때문에 해당 `FragmentTransaction`이 역순으로 처리될 수 있도록 구현이 되어있다. 예를 들어 추가하는 Transaction은 backstack에서 pop될 때 삭제하는 처리를 하게 된다.

Android의 화면 회전은 configuration change를 야기하고 `Activity`의 재생성을 유발하게 된다. `Fragment`를 호스트하고 있는 `Activity`가 재생성될때 현재 보고 있는 `Fragment`를 다시 보여주도록 하는 것을 미리 구현하고 있다. 과거에는 `Fragment` 객체 자체를 유지하게 하므로써 해당 작업을 할 수 있었다. 최신 버전인 1.6.1에서는 `SavedStateRegistryOwner`를 이용하여 `onSaveInstanceState` callback에서 `FragmentManager`의 `State`를 저장하고 복원한다. 이로써 개발자가 신경쓰지 않고도 `Fragment`를 복원할 수 있다.

## Fragment Lifecycle

## Reference

