#!/bin/bash

# Файлы для тестирования
TEST_FILE="test.txt"
PATTERN_FILE="patt.txt"

# Временные файлы для хранения выводов
GREP_OUTPUT="grep_output.txt"
GREP_CAT_OUTPUT="s21_grep_output.txt"

# Функция для сравнения вывода grep и grep_cat с указанными флагами
compare_outputs() {
  local flags=$1

  # Выполняем grep и grep_cat с указанными флагами и сохраняем вывод
  grep $flags $TEST_FILE > $GREP_OUTPUT 
  ./s21_grep $flags $TEST_FILE > $GREP_CAT_OUTPUT 

  # Сравниваем файлы посимвольно
  if diff -q $GREP_OUTPUT $GREP_CAT_OUTPUT > /dev/null; then
    echo "Outputs are identical for flags: $flags"
  else
    echo "Outputs differ for flags: $flags"
 ##   echo "Differences:"
 ##   diff $GREP_OUTPUT $GREP_CAT_OUTPUT
  fi
}

# Флаги для тестирования
FLAGS=(
  "-e test"
  "-i test"
  "-v test"
  "-c test"
  "-l test"
  "-n test"
  "-h test"
  "-s test"
  "-f $PATTERN_FILE"
  "-o test"
  "-iv test"
  "-in test"
)

# Проверка работы флагов
for flag in "${FLAGS[@]}"; do
  compare_outputs "$flag"
done

# Удаление временных файлов
rm -f $GREP_OUTPUT $GREP_CAT_OUTPUT