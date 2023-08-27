# Multiple dispatch

Multiple dispatch는 dynamic dispatch가 런타임 타입으로 작동되는 방법론이다. 즉 타입과 상관없이 해당 함수가 존재하면 dispatch가 수행되도록 구현할 수 있다.

## With Example

Kotlin은 Multiple dispatch를 지원하지 않는다. 예를 들어 아래와 같은 코드는 타입으로 완전성을 지원하지만 실행을 지원하지는 않는다.

```kotlin
sealed class Person {
    class Student(
        val school: String
    ): Person()

    class Employee(
        val job: String
    ): Person()
}

fun doSomething(student: Person.Student) {
    println(student.school)
}

fun doSomething(employee: Person.Employee) {
    println(employee.job)
}

fun main() {
    val person: Person = Person.Employee("Developer")

    doSomething(person)
}
```

Multiple dispatch가 언어 지원으로 지원하는 경우에는 위의 코드가 실행된다. 이러한 불편함을 Kotlin에서는 polymorphism으로 해소한다.

```kotlin
sealed class Person {
    abstract fun doSomething()
    
    class Student(
        val school: String
    ): Person() {
        override fun doSomething() {
            println(school)
        }
    }

    class Employee(
        val job: String
    ): Person() {
        override fun doSomething() {
            println(job)
        }
    }
}

fun main() {
    val person: Person = Person.Employee("Developer")

    person.doSomething()
}
```