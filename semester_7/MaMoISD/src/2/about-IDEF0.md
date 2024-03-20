# Описание модели IDEF0

## Контекстная диаграмма (диаграмма верхнего уровня)

1. Один блок - A-0;
2. Его имя представляет общий смысл проекта (теплостанция, информационная
программа);
3. Несколько однотипных стрелок на вход и несколько на выход.

## Диаграммы декомпозиции n-уровня

1. Представлена списком функций, детализирующих выполнение родительской функции
на (n-1) уровне;
2. Имя диаграммы образуется как A(номер-блока-1)...(номер-блока-(n-1)), первый
уровень называется A0;

## Источники

1. методичка
2. https://advanced-quality-tools.ru/assets/idef0-rus.pdf

## Предположения

1. A-0: Обработка ботом сообщений от пользователя (A0)
2. A0: Приём сообщения (A1) -> Обработка сообщения (A2) -> Отправка сообщения (A3)