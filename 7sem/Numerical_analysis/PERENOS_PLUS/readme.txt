 Программа для проверки одномерного варианта р.с. для уравнения переноса.
 с a=sin(\pi x) u=exp(x)cos(\pi x)  f=exp(t)(cos(\pi x)+\pi cos(2\pi x)).
 Область [0,X]x[0,T].
 Задаются число
 точек  N по временной переменной и число точек M по пространственной
 переменной. Выводятся на экран нормы в W21,С и L2 ошибок расчета при t=T
 в таблице (n_max х m_max) для N/10^{k}, M/10^{l}   k=0,...,n_max,
 l=0,...,m_max, а также замеры времени расчета на каждой из сеток.
 Создается файл peren_h2.tex, с таблицей норм ошибок и замерами времени.

main содержится в файле otl_glad.c
peren_h2,dat содержит параметры запуска
func.c содержит функции для коэффициента переноса, точного решения, правой части
input.c - подпрограмма чтения из файла peren_h2.dat
normi.c - подпрограммы вычисления норм
peren_h2.c - программа, реализующая схему
print.c - подпрораммы вывода на экран результатов счета
progon.c - алгоритм прогонки
tabtex.c - создание файла формата tex с результатами счета

makefile -создание выполняемого файла peren_h2.exe
запуск:  peren_h2.exe filename
параметр запуска содержит символьную строку filename.dat без расширения .dat
