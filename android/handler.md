# Handler

Android에는 Ui 처리를 위한 Main Thread가 존재하는데, Worker Thread에서 Ui 요소에 접근하는 것은 금지되어 있다. 그래서 `TextView`와 같은 객체에 접근하기 위해서는 Main Looper의 Handler를 통해서 접근해야한다. 이때, `post`함수를 이용하여 접근할 수 있다.

Ui 요소가 처리가 되는 Handler와는 별개로 Ui요소를 렌더링하는 처리가 분리되어 있는데, 이때는 `postOnAnimation`과 같은 함수로 호출하게 되면 해당 fram을 그릴때 호출되는 `doFrame`에서 처리를 요청하게 된다. Touch Event와 같은 처리 이후 Animation 혹은 Draw 단계에서 처리해야 하는 작업이 있을때 이와 같은 처리를 통해 해결할 수 있다.