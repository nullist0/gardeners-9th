# Phantom type

팬텀 타입이란 구현부가 아닌 선언부에만 나타나는 타입 파라미터이다.

```kotlin
class Data<T>(val id: Int)
```

위의 `Data`는 제네릭 타입 `T`를 받아 구현부에서 사용하고 있지 않으므로 해당 타입이 팬텀 타입이라고 볼 수 있다.

팬텀 타입은 아래와 같은 장점으로 사용할 수 있다.

- 컴파일 타임에 타입 조건을 만족할 수 있다.
- 타입조건만 다른 중복 코드를 제거할 수 있다.
- Enum 파라미터를 타입 시스템으로 바꿀 수 있다.
- 타입 파라미터는 컴파일 타임에 제거할 수 있으므로 런타임 성능 저하를 일으키지 않는다.


## 예시

```kotlin
// 팬텀 타입
data class Id<T>(val id: Int)

data class User(
    val id: Id<User>
)

data class Book<STATE: BookState>(
    val id: Id<Book>,
    // 아래의 코드는 불필요해진다.
    // val state: BookState,
)

sealed class BookState {
    class CanBorrow: BookState()
    class AlreadyBorrow: BookState()
}

fun foo(user: User, book: Book<*>) {
    // 타입 시스템에 의해 아래의 코드는 유효하지 않음을 확인할 수 있다.
    if (user.id == book.id) {
        // do something
    }
}

// Enum을 타입 파라미터로 대체할 수 있다.
fun borrow(user: User, book: Book<CanBorrow>) {
    // call API to save borrowing
}
```