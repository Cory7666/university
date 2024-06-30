Методы рефакторинга кода:
* составление методов:
  * выделение метода;
  * встраивание метода;
  * встраивание временной переменной;
  * замена временной переменной вызовом метода;
  * введение поясняющей переменной;
  * расщепление временной переменной;
  * удаление присваиваний параметрам;
  * замена метода объектом методов;
  * замещение алгоритма;
  
* перемещение функций между объектами:
  * перемещение метода - Move Method;
  * перемещение поля - Move Field;
  * выделение класса - Extract Class;
  * встраивание класса - Inline Class;
  * сокрытие делегата - Hide Delegate;
  * удаление посредника - Remove Middle Man;
  * введение внешнего метода - Introduce Foreign Method;
  * введение локального расширения - Introduce Local Extension;
  
* упрощение условных выражений:
  *- декомпозиция условного оператора - Decompose Conditional;
  *- консолидация условного выражения - Consolidate Conditional Expression;
  *- консолидация дублирующихся условных фрагментов - Consolidate Duplicate Conditional Fragments;
  * удаление управляющего флага - Remove Control Flag;
  *- замена вложенных условных операторов граничным оператором - Replace Nested Conditional with Guard Clauses;
  *- замена условного оператора полиморфизмом - Replace Conditional with Polymorphism;
  *- введение объекта Null - Introduce Null Object;
  
* упрощение вызова методов:
  *- переименовывание метода - Rename Method;
  * добавление параметра - Add Parameter;
  *- удаление параметра - Remove Parameter;
  * разделение запроса и модификатора - Separate Query from Modifier;
  * параметризация метода - Parameterize Method;
  * замена параметра явными методами - Replace Parameter with Explicit Methods;
  * сохранение всего объекта - Preserve Whole Object;
  * замена параметра вызовом метода - Replace Parameter with Method;
  *- введение граничного объекта - Introduce Parameter Object;
  *- удаление метода установки значения - Remove Setting Method;
  *- сокрытие метода - Hide Method;
  *- замена конструктора фабричным методом - Replace Constructor with Factory Method;
  * инкапсуляция нисходящего преобразования типа - Encapsulate Downcast;
  * замена кода ошибки исключительной ситуацией - Replace Error Code with Exception;
  * замена исключительной ситуации проверкой - Replace Exception with Test.
