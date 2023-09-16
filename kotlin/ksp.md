# KSP

KSP는 Kotlin symbol processing의 약자로 어노테이션 프로세싱을 위한 compiler를 제공한다. 이 플러그인을 이용하여 annotation으로 파일을 자동 생성하는 경우 아래의 라이브러리를 사용하는 경우가 있다.

https://square.github.io/kotlinpoet/

## With kotlinpoet

코드를 자동 생성할때 여러 import 문들을 해소하기가 어려우며, 각 클래스에 맞게 자동 생성하는 코드를 구성하기 어려울 수 있다. 해당 라이브러리를 이와같은 상황에서 사용하면 편리하다.

각각의 상황에서 kotlinpoet은 사용할 수 있는 클래스들을 선언해두었는데, 아래와 같이 볼 수 있다.

1. 파일의 생성: `FileSpec`
2. 타입의 생성: `TypeSpec`
3. 타입 alias 생성: `TypeAliasSpec`
4. 함수의 생성: `FunSpec`
5. 파라미터의 생성: `ParameterSpec`
6. 프로퍼티의 생성: `PropertySpec`
7. 어노테이션 생성: `AnnotationSpec`

코틀린 언어 스펙에 있는 모든 내용을 추가한 것이라고 생각하면 된다. 여기서는 Generic과 관련한 내용만을 간단하게 다룬다.

### Example

```kt
// interface
package com.component.generic

interface Component<T>

// annotation
package com.auto.component.annotations

annotation class AutoComponentFactory

// annotated
package com.example.service

@AutoComponentFactory
class TestTarget

// generated
package com.example.service

import com.component.generic.Component

class TestTargetFactory: Componenet<TestTarget> {
    fun get(): TestTarget = TestTarget()
}
```

위와 같이 정의된 `Component<T>`를 구현하는 `**Factory` 클래스들을 자동생성하고 싶다고 가정해보자. Kotlinpoet에서는 아래와 같이 작성하면 된다.

#### Find annotated classes
```kt
class AutoCompoentFactorySymbolProcessor(
    private val codeGenerator: CodeGenerator
): SymbolProcessor {
    override fun process(resolver: Resolver): List<KSAnnotated> {
        val symbols = resolver.getSymbolsWithAnnotation(
            "com.auto.component.annotations.AutoComponentFactory"
        )
        // do some logic and return
    }
}
```

#### Make factory classes
```kt
class AutoCompoentFactorySymbolProcessor(
    private val codeGenerator: CodeGenerator
): SymbolProcessor {
    private fun createAutoLichComponent(classDeclaration: KSClassDeclaration) {
        val factoryClassName = ClassName(
                classDeclaration.packageName.asString(),
                "${classDeclaration.simpleName.asString()}Factory"
        )
        val componentFactoryClassName = ClassName(
            "com.component.generic",
            "Component"
        ).parameterizedBy(classDeclaration.toClassName())
        val createFunSpec = FunSpec.builder("get")
            .addStatement("return %T()", classDeclaration.toClassName())
            .returns(classDeclaration.toClassName())
            .build()

        val componentFactoryTypeSpec = TypeSpec.classBuilder(factoryClassName)
                .superclass(componentFactoryClassName)
                .addFunction(createFunSpec)
                .build()
        FileSpec.builder(factoryClassName)
                .addType(componentFactoryTypeSpec)
                .build()
                .writeTo(codeGenerator, Dependencies.ALL_FILES)
    }
}
```