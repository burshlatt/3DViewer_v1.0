CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
TEST_LIBS = -lcheck -lm -lpthread

#	== ВЫПОЛНИТЬ ВСЕ ДЕЙСТВИЯ ==
all: clean uninstall dist install gcov_report dvi

#	== УСТАНОВКА ПРОГРАММЫ ==
install:
	@echo -------------------INSTALL-------------------
	make uninstall --quiet
	mkdir build
	cd ./3DViewer/ && qmake && make && make clean && rm -rf Makefile && mv 3DViewer.app ../build/
	cp Music/space_music.mp3 build/3DViewer.app/Contents/Resources/
	@echo -------------------SUCCESS-------------------

#	== ЗАПУСК ПРОГРАММЫ ==
run:
	cd ./build && open 3DViewer.app
	
#	== УДАЛЕНИЕ ПРОГРАММЫ ==
uninstall:
	@echo -------------------UNINSTALL-------------------
	rm -rf build
	@echo --------------------SUCCESS--------------------

#	== ОЧИСТКА ФАЙЛОВ ==
clean:
	cd ./CFiles/ && rm -rf s21_3dViewer *.o *.a *.info *.gcda *.gcno *.out test report/ gcov_test
	cd ./test/ && rm -rf *.a *.out
	rm -rf 3DViewer.tar.gz

#	== УСТАНОВКА LCOV ==
lcov:
	cd && brew install lcov

#	== СОЗДАНИЕ GCOV ОТЧЕТА ==
#	Для корректной работы нужно установить lcov: make lcov
gcov_report: tests
	cd ./CFiles/ && $(CC) $(FLAGS) --coverage ../test/test.c s21_3dViewer.c s21_affins.c s21_3dViewer.a $(TEST_LIBS) -o gcov_test
	cd ./CFiles/ && ./gcov_test
	cd ./CFiles/ && lcov -t "3dviewer" -o 3dviewer.info -c -d .
	cd ./CFiles/ && genhtml -o report 3dviewer.info
	cd ./CFiles/ && open ./report/index.html
	
#	== ОТКРЫТИЕ README ПРОЕКТА ==
dvi:
	open readme.html

#	== СОЗДАНИЕ АРХИВА ПРОЕКТА ==
dist:
	tar czvf 3DViewer.tar.gz .

#	== КОМПИЛЯЦИЯ БИБЛИОТЕКИ ==
s21_3dViewer.a:
	cd ./CFiles/ && $(CC) -c $(FLAGS) s21_*.c
	cd ./CFiles/ && ar rc s21_3dViewer.a s21_*.o

#	== ЗАПУСК UNIT-ТЕСТОВ ==
tests: s21_3dViewer.a
	cd ./CFiles/ && cp s21_3dViewer.a ../test/
	cd ./test/ && $(CC) -fsanitize=address -lcheck test.c s21_3dViewer.a -o test.out && ./test.out

#	== ПРОВЕРКА СТИЛЯ ==
clang:
	cp ../materials/linters/.clang-format CFiles/
	cp ../materials/linters/.clang-format 3DViewer/
	cp ../materials/linters/.clang-format test/
	cd ./CFiles/ && clang-format -n *.c *.h
	cd ./3DViewer/ && clang-format -n *.cpp *.h
	cd ./test/ && clang-format -n *.c
	rm CFiles/.clang-format
	rm 3DViewer/.clang-format
	rm test/.clang-format
