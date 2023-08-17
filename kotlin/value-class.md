# Value class

비지니스 로직을 구현할 때 `String`이나 `Int` 같이 primitive 타입을 단순히 wrapping한 타입을 정의해야하는 경우도 있다. `data class`나 `class`로 하는 경우에 해당 단일 값을 위해서 객체를 매번 생성하고 사용해야하는 단점이 생긴다.

이럴때 `typealias`가 좋은 방안이 될 수 있지만 실제로 타입이 생기는 것이 아니라는게 문제이다. 

첫째로, `typealias`는 타입을 정의해주지 않는다. 아래와 같은 코드는 컴파일도 되고 실행도 된다.
```kotlin
typealias UserId = Int

fun Int.foo() = this + 4

fun foo(x: Int, y: UserId) = x + y

fun main() {
    val n: Int = 5
    val userId: UserId = 3

    // extension function을 공유할 수 있다.
    println(userId.foo()) // 7

    // 새 타입이 아니기에 서로 섞어서 인자로 사용할 수 있다.
    println(foo(userId, n)) // 8
}
```

비지니스 로직을 위해 주의해서 사용하기 위해 타입을 지정하고자 사용한 것인데 의미가 없어진다. Kotlin 1.5에서 stable하게 지원하는 value class의 경우 위와 같은 경우를 해소하면서, compile time에 해당 타입으로 교체하므로 runtime overhead도 해소할 수 있다.