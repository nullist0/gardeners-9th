# App Startup

Android에서 App Startup이라는 라이브러리가 존재한다. 해당 라이브러리는 앱 초기화를 위한 기능을 제공하는데 그 내부에서 `ContentProvider`를 이용하여 `Application` 초기화보다 먼저 실행되게 된다. 그리고 각 컴포넌트를 초기화하기 위한 의존성을 미리 정의할 수 있어 필요한 의존성을 각자 초기화하여 구현할 수 있다.