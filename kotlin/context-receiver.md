# Context receiver

## Scope

`Kotlin` 코드를 작성하다보면 여러가지 `Scope`-postfix를 갖는 클래스들을 많이 보게 된다. `Scope` 인터페이스들은 해당 `Scope`에서 제공되어야하는 필수적인 기능들을 정의하고 해당 `Scope`에서 할 수 있는 동작들은 확장 함수로 정의된다. 대표적인 예시로 `CoroutineScope`가 있다.

```kotlin
interface CoroutineScope {
    val corountineContext: CoroutineContext
}

fun CoroutineScope.launch() {
    // internal logic
}
```

`Scope`를 직접 사용할 때에는 scope-function (with, run, apply) 함수를 이용하여 아래와 같이 사용할 수 있다.

```kotlin
fun main() {
    val coroutineScope = //.. 
    
    with(coroutineScope) {
        // corotine scope으로 bound된 scope
    }
}
```

## Problems

우리는 이를 굉장히 편리하게 사용하지만 문제가 존재한다. 다시 새로운 예시를 들어보자. 아래와 같이 `Scope` 내에서만 사용하는 `Entity`의 확장함수를 정의하여 DSL을 정의할 수 있다.

```kotlin
interface Entity

interface Scope {
    fun Entity.doAction() {
        // ...
    }
}

fun Scope.doMoreAction() {
    // ...
}
```

이와 같은 코드를 구성할때 아래와 같은 문제를 생각할 수 있다.

1. `doAction`를 `Entity`를 extends한 클래스에 대해서 정의하기 어렵다.
2. `doMoreAction`가 실제로 scope 함수로 한정되었는지와 상관없이 실행할 수 있다.
3. 한번에 한가지 `Scope`만 receiver로 정의할 수 있다.

## To context receiver

3가지 문제를 해결하기 위해 context receiver라는 문법이 [KEEP-259](https://github.com/Kotlin/KEEP/blob/master/proposals/context-receivers.md)로 제안되었다.

`context` 키워드를 이용하여 함수앞에 정의하면 context receiver를 정의할 수 있다.

```kotlin
interface Entity
interface Scope

// Scope를 context로 정의할 수 있다.
// 확장 함수가 아니게 된다.
context(Scope)
fun doMoreAction() {
    // ...
}

// 여러개의 context를 정의할 수 있다.
// 확장함수가 아니게 된다.
context(Scope, Entity)
fun doAction() {
    // ...
}
```

이로써 `확장함수가 아니게 되었기에 1, 2 번을 해소할 수 있다`. 그리고 `context에 인자를 넣으면서 여러 context를 정의할 수 있다`. 해당 코드를 사용할때에는 아래와 같이 사용할 수 있다.

```kotlin
fun main() {
    val entity: Entity = // ...
    val scope: Scope = // ...
    with(scope) {
        doMoreAction()

        with(entity) {
            doAction()
        }
    }

    scope.doMoreAction() // Compile error: 확장함수가 아니다.
}
```

`context` 키워드는 함수외의 `interface`, `class`에도 동일하게 정의할 수 있는데, 이로써 의존성 주입과 동일한 형태로 코드를 작성할 수 있다.

```kotlin
context(Logger) // context로써 dependency가 주입된다.
class UserRepository(
    // explicit하게 dependency가 주입된다.
    private val users: Users
): Repository {

}
```

이에 관한 [블로그](https://blog.rockthejvm.com/kotlin-context-receivers/#6-appendix-gradle-configuration)에서는 아래와 같은 가이드라인을 제공한다.

- 비지니스 로직을 위한 객체는 explicit하게 di를 하라
- 외의 context에 대해서는 `context`로 explicit하게 주입하라

가장 큰 이유는 **implicit한 의존은 코드를 읽기 어렵고 이해하기 어렵게 만들기** 때문이다. 그래서 적어도 비지니스 로직의 경우에 강제로 주입하도록 코드를 구성하는 것이 좋다.

## Reference

- https://blog.rockthejvm.com/kotlin-context-receivers/#6-appendix-gradle-configuration
- https://github.com/Kotlin/KEEP/blob/master/proposals/context-receivers.md