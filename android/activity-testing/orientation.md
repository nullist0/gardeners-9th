Android에서 Activity 테스트를 위해서 `ActivityScenario`를 이용하여 테스트를 진행한다. `ActivityScenario`를 사용할때의 주의점은 `onActivity`내에서 모든걸 해결하려고 해서는 안된다는 점이다.

소스코드를 확인하면 바로 알 수 있다. Androidx test 라이브러리의 `ActivityScenario.onActivity`를 가져와보았다. `Lock`을 이용한 동시성 제어를 제외하고 인자로 받은 `action`을 `MainThread`에서 실행하도록 구현되어있다.

```java
class ActivityScenario {
    public ActivityScenario<A> onActivity(final ActivityAction<A> action) {
        // A runnable to perform given ActivityAction. This runnable should be invoked from the
        // application main thread.
        Runnable runnableAction = () -> {
            checkMainThread();

            lock.lock();
            try {
                checkNotNull(
                    currentActivity, "Cannot run onActivity since Activity has been destroyed already");
                action.perform(currentActivity);
            } finally {
                lock.unlock();
            }
        };

        if (Looper.myLooper() == Looper.getMainLooper()) {
            // execute any queued work on main looper, to make behavior consistent between running
            // on Robolectric with paused main looper and instrumentation
            controlledLooper.drainMainThreadUntilIdle();
            runnableAction.run();
        } else {
            getInstrumentation().waitForIdleSync();
            getInstrumentation().runOnMainSync(runnableAction);
        }
        return this;
    }
}

```

이때 `MainLooper`를 blocking하므로 `WindowManager`에서 실행하는 configuration change를 바로 실행할 수 없다. 그러므로 화면 회전에 의한 assertion을 하고 싶다면, `onActivity`를 하나로 끊어서 처리해야한다.

```kt
private lateinit var scenario: ActivityScenario<SampleActivity>

@Before
fun setUp() {
    scenario = launchActivity()
}

@After
fun tearDown() {
    scenario.close()
}

@Test
fun badTest() {
    scenario.onActivity { activity ->
        activity.requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        // assert with some effect by the configuration change...
    }
}

@Test
fun goodTest() {
    scenario.onActivity { activity ->
        activity.requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        // assert with some effect by the configuration change...
    }
    // assert with some effect by the configuration change...
}
```

또한 Robolectrics가 알지 못하는 `Activity`에 대해 자동으로 Manifest를 작성해주고 있었지만 Manifest를 작성해주지 않도록 변경되면서 빌드에 따라서 접근가능한 `Activity`가 변경되는 경우에는 이에 대한 처리를 해주어야 한다. 예를 들어 `:sample` 모듈에 `Activity`가 정의되어있고, `production` 빌드에서 제외된다면, `production` 빌드로 unit test를 실행할 때 fail이 발생하게 된다. 이러한 경우 해당 모듈도 같이 빌드하는 phase에 대한 test 폴더에 파일을 옮겨 주어야 한다.