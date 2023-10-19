[New Feature][Component] Support lifecycle-aware component

# Summary

This proposal is to suggest to add some new API for lich component. The new APIs will release the component object when given lifecycle takes `ON_DESTROY` event, and then it will not be used anymore.

# Proposal

## Background

In now, the component created by lich is considered as singleton because `ComponentFactory<T>` is defined by `object` keyword. Also this implementation is guided in `README.md`. But this will imply some problems.

- Even if the component is not used anymore, it will not be collected by the GC. This will hold a lot of memory to hold the components. For example, components for log-in Activity, will not be created again if user logged in.
- `context.getComponent` has some confused definition. This function call looks that the created component will receive the given `context` instance. But the component will receive the `applicationContext`.

Thanksfully, there is a concept of `Lifecycle` and `ViewModelStore.clear()` in Android framework. I hope that the lifetime of the component is the same as the lifecycle of context.

## Sketched change area

I don't have the concrete implementation for this proposal. So this section is just a sketch to implement this proposal. After this proposal is approved, the concrete implementation should be followed.

The steps to implement this proposal is followings.

1. Change the interface of `ComponentProvider`
2. Change `DefaultComponentProvider.getComponent` to observe lifecycle.
3. Add some new APIs to support new features.

### Change of interface

To get the two types of owners, the `ComponentProvider` is needed to be changed.

```kotlin
interface ComponentProvider {
    fun <T : Any, OWNER> getComponent(context: Context, factory: ComponentFactory<T>, owner: OWNER?) : T
    where OWNER is ViewModelStoreOwner, OWNER is LifecycleOwner
}
```

### Change of `ComponentProvider`

`ComponentProvider` should observe the given `lifecycle` using the `context`.

```kotlin
internal class DefaultComponentProvider : ComponentProvider {
    override fun <T : Any, OWNER> getComponent(context: Context, factory: ComponentFactory<T>, owner: OWNER?) : T 
    where OWNER is ViewModelStoreOwner, OWNER is LifecycleOwner {
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

        // Pass the given context
        val result = runCatching { accessor.createComponent(factory, context) }
        creating.setResult(result)

        accessor.setComponent(factory, result.getOrNull())

        // observe lifecycle
        when (owner) {
            is ViewModelStoreOwner -> {
                val viewModelFactory = object: ViewModelProvider.Factory {
                    override <T: ViewModel> fun create(modelClass: Class<T>) {
                        return object: ViewModel() {
                            override fun onCleared() {
                                accessor.setComponent(null)
                            }
                        } as T
                    }
                }
                ViewModelProvider(owner, viewModelFactory).get<ViewModel>()
            }
            is LifecycleOwner -> {
                val observer = object: DefaultLifecycleObserver {
                    // remove component
                    override fun onDestroy(owner: LifecycleOwner) {
                        accessor.setComponent(null)
                    }
                }
                owner.lifecycle.addObserver(observer)
            } 
        }

        return result.getOrThrow()
    }
}
```

### Add new APIs

From the `Components.kt`, the entry point of this new features should be provided.

```kotlin
fun <T> Context.getComponent(factory: ComponentFactory<T>): T {
    return when(this) {
        // component is bounded to the lifecycle of ViewModel
        is ViewModelStoreOwner -> componentProvider.getComponent(context.applicationContext, factory, this)

        // component is boudned to the lifecycle of the android component
        is LifecycleOwner -> componentProvider.getComponent(context, factory, this)

        // component is singleton
        else -> componentProvider.getComponent(context.applicationContext, factory, null)
    }
}

// This API will be used for the ViewModelProvider.Factory. 
// The extras[APPLICATION_KEY] is application object so there is no way to determine whether the given context is bounded to lifecylce.
// So a new API will be needed to support components in ViewModel.
fun <T> CreationExtras.getComponent(factory: ComponentFactory<T>): T {
    val context = requireNotNull(this[APPLICATION_KEY])
    val viewModelStoreOwner = requireNotNull(this[VIEW_MODEL_STORE_OWNER_KEY])

    return componentProvider.getComponent(context, factory, viewModelStoreOwner)
}
```

### Affected impact

If an application is using Lich-component, there is no things to change immediately. The public APIs are not changed, so it is okay to use lich-component, if there is no need to optimize memory. But:

- if you want to optimize memory, then you must change the API calls in `ViewModelProvider.Factory` to use `CreationExtras.getComponent` to handle the lifecycle of components in `ViewModel`.
- or if your component has some mutable state, then you must change the `context.getComponent` calls to `context.applicationContext.getComponent` manually.

### Remained problems of above change

The remained problems of the above change are considered as followings.

- If a component is used in multiple lifecycle-aware Android components at once, then `context` object might be leaked.

If you have an idea, please let me know.