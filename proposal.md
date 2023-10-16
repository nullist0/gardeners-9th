[New Feature][Component] Support lifecycle-aware component

# Summary

This proposal is to suggest to add some new API for lich component. The new APIs will release the component object when given lifecycle takes `ON_DESTROY` event.

# Proposal

## Background

In now, the component created by lich is considered as singleton because `ComponentFactory<T>` is defined by `object` keyword. Also this implementation is guided in `README.md`. But this will imply some problems.

- Even if the component is not used anymore, it will not be collected by the GC. This will hold a lot of memory to hold the components. For example, components for log-in Activity, will not be created again if user logged in.
- `context.getComponent` has some confused definition. This function call looks that the created component will receive the given `context` instance. But the component will receive the `applicationContext`.

Thanksfully, there is a concept of `Lifecycle` in Android framework. I hope that the lifetime of the component is the same as the lifecycle of context.

## Sketched change area

I don't have the concrete implementation for this proposal. So this section is just a sketch to implement this proposal. After this proposal is approved, the concrete implementation should be followed.

The steps to implement this proposal is followings.

- Change `DefaultComponentProvider.getComponent` to observe lifecycle.

### Change of `ComponentProvider`

`ComponentProvider` should observe the given `lifecycle` using the `context`.

```kotlin
internal class DefaultComponentProvider : ComponentProvider {
        override fun <T : Any> getComponent(context: Context, factory: ComponentFactory<T>): T {
        val accessor = ComponentFactory.Accessor
        accessor.getComponent(factory)?.let {
            @Suppress("UNCHECKED_CAST")
            return if (it is Creating) it.await() else it as T
        }

        val creating = Creating()
        while (!accessor.compareAndSetComponent(factory, null, creating)) {
            accessor.getComponent(factory)?.let {
                @Suppress("UNCHECKED_CAST")
                return if (it is Creating) it.await() else it as T
            }
        }

        // Pass the given context if it bounded to the lifecycle
        // If it has no lifecycle, then it will be considered as a singleton
        val componentContext = context
            .takeIf { this is LifecycleOwner }
            ?: context.applicationContext

        val result = runCatching { 
            accessor.createComponent(
                factory, 
                componentContext
            )
        }
        creating.setResult(result)

        accessor.setComponent(factory, result.getOrNull())

        // observe lifecycle
        (context as? LifecycleOwner)?.lifecycle?.let {
            val observer = object: DefaultLifecycleObserver {
                // remove component
                override fun onDestroy(owner: LifecycleOwner) {
                    accessor.setComponent(null)
                }
            }
            it.addObserver(observer)
        }

        return result.getOrThrow()
    }
}
```

### Remained problems of above change

The remained problems of the above change are considered as followings.

- If a component is used in multiple lifecycle-aware Android components at once, then `context` object might be leaked.
- Components created in the `ViewModel.Factory` will not be collected by the `ViewModel.onCleared` because the given context is `applicationContext`.
- If an instance of `ViewModel` is created directly in an lifecycle-aware Android component, the `context` object might be leaked because `ViewModel` may live more than the Android component.

If you have an idea, please let me know.