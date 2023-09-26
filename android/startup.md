# App Startup

Android에서 App Startup이라는 라이브러리가 존재한다. 해당 라이브러리는 앱 초기화를 위한 기능을 제공하는데 그 내부에서 `ContentProvider`를 이용하여 `Application` 초기화보다 먼저 실행되게 된다. 그리고 각 컴포넌트를 초기화하기 위한 의존성을 미리 정의할 수 있어 필요한 의존성을 각자 초기화하여 구현할 수 있다. 예시로 `WorkManager`의 경우 `WorkManager.initialize` 함수로 초기화를 할 수 있다.

해당 라이브러리와 같은 경우 `Application`이 생성하기 전에 실행되지만 `ApplicationContext`를 사용할 수 있다.

해당 라이브러리를 사용할 때 장점은 아래와 같다.
- `ContentProvider`를 하나만 생성한다.
- `Initializer<T>.dependencies()`의 반환값을 이용하여 먼저 초기화 되어야 하는 라이브러리를 정의할 수 있다.
- 순환 초기화가 있는 경우 `Exception`이 발생하도록 구현되어있다.
- `Initializer<T>`를 중복으로 초기화하지 않도록 구현되어 있다.