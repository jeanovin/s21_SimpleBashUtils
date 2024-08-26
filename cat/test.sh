#!/bin/bash

# Файл для тестирования
TEST_FILE="test.txt"

# Временные файлы для хранения выводов
CAT_OUTPUT="cat_output.txt"
S21_CAT_OUTPUT="s21_cat_output.txt"

# Функция для сравнения вывода cat и s21_cat с указанными флагами
compare_outputs() {
  local flags=$1

  # Выполняем cat и s21_cat с указанными флагами и сохраняем вывод
  cat $flags $TEST_FILE > $CAT_OUTPUT
  ./s21_cat $flags $TEST_FILE > $S21_CAT_OUTPUT

  # Сравниваем файлы посимвольно
  if diff -q $CAT_OUTPUT $S21_CAT_OUTPUT > /dev/null; then
    echo "Outputs are identical for flags: $flags"
  else
    echo "Outputs differ for flags: $flags" 
  fi
}

# Флаги для тестирования
FLAGS=(
  "-b"
  "-e"
  "-n"
  "-s"
  "-t"
  "-v"
)

# Проверка работы флагов
for flag in "${FLAGS[@]}"; do
  compare_outputs "$flag"
done

# Удаление временных файлов
rm -f $CAT_OUTPUT $S21_CAT_OUTPUT