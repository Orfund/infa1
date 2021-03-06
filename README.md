# infa1
######  ТЕКУЩИЙ СПИСОК АКТИВНЫХ МОДУЛЕЙ И ИХ ФУНКЦИОНАЛЬНОСТЬ
#  Angem.h
- Ну, собственно, структура - вектор. Геометрический вектор на плоскости, имеет поля x и y, обращение к которым происходит с помощью:
 - `.[0] и .[1]  `
 - `.[2n] .[2n+1] `
 - `.[X] .[Y] `
 - `.getx() .gety()`
 **Это абсолютно эквивалентные выражения**

------------

- Над вектором определены операции `+ -  * `(как на число, так и на другой вектор).
Если умножать на вектор, получается число (работаем на плоскости)

- определена операция `vector1%vector2` - определяет пропорциональность векторов

- операция `vector1==vector2` - равенство (покоординатно)

- ` vector1 = vector2` - записывает в vector1 копию вектора vector 2. При последующем изменении vector2 vector1 **не** изменится
- `.length() `возвращает геометрическую длину вектора

- удобное чтение и запись. `vector1>>F;` запишет vector1 в файл F
`vector1<<F` прочитает вектор из файла. Для записи из терминала и прочтения из него используется` vector1>>stdout` и `vector1<<stdin`

------------

 -  Массив из векторов можно сортировать фунцией `void Sort(vector*v, int n, skalar f, int dir)`. Разберемся тщательнее. `skalar f `- указатель на функцию. Ее параметром обязательно является вектор, а возвращает она `double`. Если используется C++11 и выше, в качестве этого параметра можно передать **ламбда-функцию** 
 Например, ` Sort(vectors, n, [](vector v)->double{return v.length();})`. Ну или указатель.
 dir происходит от direction и означает сторону сортировки. По умолчанию - по возрастанию, то есть 1.
 Можно передать -1 и отсортируется по убыванию. Очень рекомендую сделать проверку на ноль при запуске функции.
**ВАЖНОЕ ЗАМЕЧАНИЕ: SORT ИМЕЕТ ТИП ВОЗВРАЩАЕМОГО ЗНАЧЕНИЯ VOID И МЕНЯЕТ ПЕРЕДАННЫЙ В НЕЕ МАССИВ.**

------------

- Функция `linear(vector*v, double q, int n)` возвращает линейную комбинацию массива v, где каждый элемент умножен на q
`linear(vector*v, double*q, int n)` возвращает линейню комбинацию массива v, где каждый элемент умножается на соответствующий ему элемент q (v[i]*q[i])

------------

------------
# ** ВСЕ ПОСЛЕДУЮЩИЕ МОДУЛИ ПОДКЛЮЧАЮТСЯ `#include"collections.h"`**
------------




# List.h
Первое, что хочется сказать - это c++. Командой gcc компилироваться не будет и файлы, где это используется, должны иметь расширение .cpp

Введено расширение массивов - List. 
- Конструктор: `List<T>mylist = List<T>(number)`, где T - тип элемента, а number - начальное количество.
- Убрана возможность выстрелить себе в ногу, уйдя за границы.

- `mylist.length` теперь приватно. Это означает, что еще одна возможность выстрелить себе в ногу убрана. Взамен функция `mylist.Length()` вернет длину списка. Это значит, что ее нельзя назначить самостоятельно.

- `mylist[i]` работает и на чтение и на запись. Разумеется, тип должен совпадать.

- ` mylist.Append(T Object)` записывает элемент `Object` в конец списка, увеличивая его длину. Теперь это работает быстрее, потому что каждый раз не происходит `realloc`. 

- `mylist.Append(List l)`  склеит mylist с l, который обязан быть того же типа.

- `mylist.Map(void f)` Применит к каждому элементу списка функцию `f`

- `mylist.Map(obj f)` Применит функцию к каждому объекту и изменит объект на возвращаемое значение
- `mylist.Map(obj f, void*ptr)` аналогично, но с передачей указателя на какой-то объект, используемый в `f`. Пример: вывод в файл `list.Map([](vector v, void*ptr)->vector{v>>(FILE*)ptr;return v;},f);`


-   Определен оператор присваивания, загружающий копию списка.

- `mylist.Find(T object, eqrel F)` поиск объекта, эквивалентного объекту object по отношению эквивалентности `eqrel F`. ( EQuality RELationship). F должна иметь аргументами два объекта типа `T` и возвращать 1, если они эквивалентны.
Найдется первый элемент с начала. По умолчанию` eqrel F` это `==`. То есть этот параметр можно не передавать, но тогда `==` должно быть определено для `T`

- `mylist.Sort(ordrel F)`  Сортирует элементы по отношению порядка `ordrel F`. и в `Find`, и в `Sort` можно передавать лямбды с возвращаемым типом int. Однако для `ordrel F` должно равняться нулю если отношение не выполнено.
**Важно: Sort меняет сам список и ничего не возвращает**

- `mylist.Reshuffle(sigma s)` Возвращает перестановку этого списка. Роль аргумента играет функция s переводящая целое число в целое число. За чем хотелось бы следить: **биективность** от 0 до n и **целочисленность**. Функция сломается и будет абсолютно права, когда попытается взять `mylist[3.5]`

- `mylist.Remove(int index)` Удаляет элемент с индексом `index`, сдвигая все то, что стоит за `index` влево. То есть элемент `index+1` будет иметь индекс `index`

- `mylist.Fill(obj T, num n)` Заполнение списка n элемнтами со значением T.

------------




# Container
Класс- контейнер. Имеет в себе указатель на объект (любой). 
- `container.set(&object)  или container c = &object`

- Но вот тип содержимого придется запомнить. Потому что иначе получить его не получится. Синтаксис геттера таков: `container.get<type>()`. Вместо type подставляется сам тип. Можно сделать контейнер в контейнере, кстати)
# Sequences.h

------------

# Dict.h
