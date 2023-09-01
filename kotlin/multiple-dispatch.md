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

타입을 이용하여 multiple dispatch를 제한적으로나마 구현할 수 있으나 자유롭지는 않다.

```kotlin
sealed class Person {
    class Student(val school: String): Person()
    class Employee(val job: String): Person()
}

fun doSomething(person: Person) = when(person) {
    is Person.Student -> doSomething(person)
    is Person.Emplyoee -> doSomething(person)
}

fun doSomething(student: Person.Student) {
    println(student.school)
}

fun doSomething(employee: Person.Employee) {
    println(employee.job)
}
```

이런 경우 `when` 절에서 `switch` 문으로 계산하는 것이 부담된다면 `Map`으로 해당 문제를 어느정도 해소할 수 있다.

```kotlin
fun main() {
	registerExecutor<Person.Student> {
        println(it.school)
    }
    registerExecutor<Person.Employee> {
        println(it.job)
    }
	val employee: Person = Person.Employee("programmer")
    doSomething(employee)
	val student: Person = Person.Student("highSchool")
    doSomething(student)
}

sealed class Person {
    class Student(val school: String): Person()
    class Employee(val job: String): Person()
}

val executeMap: MutableMap<KClass<out Person>, (Person) -> Unit> = mutableMapOf()

inline fun <reified T: Person> registerExecutor(noinline execute: (T) -> Unit) { 
    executeMap[T::class] = execute as (Person) -> Unit
}

fun doSomething(person: Person) {
    val execute = executeMap[person::class] ?: return
    execute(person)
}
```