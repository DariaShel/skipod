# Курс Суперкомпьютеры и параллельная обработка данных (5 семестр)

## Формулировка задания
Разработка параллельной версии программы для транспонирования матриц.

Так же выполнить следующие требования:
1) Реализовать параллельную версию предложенного алгоритма с использованием технологий OpenMP и MPI (DVMH, OpenACC).
2) Начальные параметры для задачи подбираются таким образом, чтобы:
    * Задача помещалась в оперативную память одного процессора.
    * Время решения задачи было в примерном диапазоне 5 сек.-15 минут.
3) Исследовать масштабируемость полученной параллельной программы: построить графики зависимости времени исполнения от числа ядер/процессоров для различного объёма входных данных.
Для каждого набора входных данных найти количество ядер/процессоров, при котором время выполнения задачи перестаёт уменьшаться.
Оптимальным является построение трёхмерного графика: по одной из осей время работы программы, по другой - количество ядер/процессоров и по третьей - объём входных данных.
Каждый прогон программы с новыми параметрами рекомендуется выполнять несколько раз с последующим усреднением результата (для избавления от случайных выбросов).
Для замера времени рекомендуется использовать вызовы функции omp_get_wtime или MPI_Wtime, общее время работы должно определяться временем самого медленного из процессов/нитей.
Количество ядер/процессоров рекомендуется задавать в виде p=2n, n=0, 1, 2, ... , k, где k определяется доступными ресурсами.
4) Определить основные причины недостаточной масштабируемости программы при максимальном числе используемых ядер/процессоров.
5) Сравнить эффективность OpenMP и MPI-версий параллельной программы.
6) Подготовить отчет о выполнении задания, включающий: описание реализованного алгоритма, графики зависимости времени исполнения от числа ядер/процессоров для различного объёма входных данных, текст программы.

# Курс Распределённые системы (7 семестр)

## Формулировка задания

### Задача 1
В транспьютерной матрице размером 8*8, в каждом узле которой находится один процесс, необходимо выполнить операцию нахождения максимума среди 64 чисел (каждый процесс имеет свое число). Найденное максимальное значение должно быть получено на каждом процессе.
Реализовать программу, моделирующую выполнение операции MPI_ALLREDUCE на транспьютерной матрице при помощи пересылок MPI типа точка-точка.
Оценить сколько времени потребуется для выполнения операции MPI_ALLREDUCE, если все процессы выдали эту операцию редукции одновременно. Время старта равно 100, время передачи байта равно 1 (Ts=100,Tb=1). Процессорные операции, включая чтение из памяти и запись в память, считаются бесконечно быстрыми.

### Задача 2
Доработать MPI-программу, реализованную в рамках курса “Суперкомпьютеры и параллельная обработка данных”. Добавить контрольные точки для продолжения работы программы в случае сбоя. Реализовать один из 3-х сценариев работы после сбоя: a) продолжить работу программы только на “исправных” процессах; б) вместо процессов, вышедших из строя, создать новые MPI-процессы, которые необходимо использовать для продолжения расчетов; в) при запуске программы на счет сразу запустить некоторое дополнительное количество MPI-процессов, которые использовать в случае сбоя.
Подготовить отчет о выполнении задания, включающий описание алгоритма, детали реализации, а также временные оценки работы алгоритма.
Отчет и текст программы необходимо разместить в трекере.