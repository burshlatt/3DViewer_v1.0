# 3DViewer v1.0

Реализация программы 3DViewer v1.0.

## Introduction

В данном проекте я реализовал на языке программирования Си и C++ программу для просмотра 3D моделей в каркасном виде (3D Viewer). Сами модели загружаются из файлов формата .obj и имеется возможность просматривать их на экране с возможностью вращения, масштабирования и перемещения (с помощью аффинных преобразований).

## 3DViewer

- Программа была разработана на языке Си и C++ стандарта C11 с использованием компилятора gcc.
- Сборка программы осуществляется с помощью Makefile со стандартным набором целей для GNU-программ: all, install, uninstall, clean, dvi, dist, tests, gcov_report. Установка ведется в каталог src/build.
- Имеется покрытие unit-тестами модулей, связанных с загрузкой моделей и аффинными преобразованиями
- Программа предоставляет возможность:
    - Загружать каркасную модель из файла формата obj (поддержка только списка вершин и поверхностей).
    - Перемещать модель на заданное расстояние относительно осей X, Y, Z.
    - Поворачивать модель на заданный угол относительно своих осей X, Y, Z
    - Масштабировать модель на заданное значение.
- В программе реализован графический пользовательский интерфейс, на базе GUI-библиотеки с API для C89/C99/C11 (Qt)
- Графический пользовательский интерфейс содержит:
    - Кнопку для выбора файла с моделью и поле для вывода его названия.
    - Зону визуализации каркасной модели.
    - Кнопки для перемещения модели. 
    - Кнопки и поля ввода для поворота модели. 
    - Кнопки и поля ввода для масштабирования модели.  
    - Информацию о загруженной модели - название файла, кол-во вершин и ребер.
- Программа позволяет:
    - Настраивать тип проекции (параллельная и центральная).
    - Настраивать тип линий (сплошная, пунктирная), цвет и толщину ребер, цвет и размер вершин.
    - Выбирать цвет фона.
    - Сохранять полученные ("отрендеренные") изображения в файл в форматах bmp и jpeg.
    - По специальной кнопке записывать небольшие "скринкасты" - текущие пользовательские аффинные преобразования загруженного объекта в gif-анимацию (640x480, 10fps, 5s).
- Настройки программы сохраняются между перезапусками программы.
