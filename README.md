Выполнил: Приладышев Юрий\
Посылки:\
320827816   A1m - Реализация STRING MERGE SORT\
320829679   A1q - Реализация STRING QUICK SORT\
321045346   A1r - Реализация MSD RADIX SORT\
321045888   A1rq - Реализация MSD RADIX+QUICK SORT\


Прогнал по 10 прогонов каждого алгоритма на массивах размеров от 100 до 3000 (шаг 100).\
MSD Radix with quick-switch лучшее время благодаря раннему переключению на String Quick при малых подмассивам.\
Обычный MSD Radix – второй по скорости, при этом даёт минимальное число символных сравнений.\
String-ориентированные реализации работают примерно на уровне классических Merge/Quick.\
cq: avg time = 0.093 ms, avg comps = 44174.403\
cm: avg time = 0.121 ms, avg comps = 26418.409\
a1m: avg time = 0.128 ms, avg comps = 26420.658\
a1q: avg time = 0.179 ms, avg comps = 58583.942\
mr: avg time = 0.088 ms, avg comps = 7380.391\
mrq: avg time = 0.080 ms, avg comps = 20907.531

