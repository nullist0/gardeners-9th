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

// TODO

## Fragment Lifecycle

## Reference

