#!/bin/sh

cout=0
for i in $(cat numbers.txt)
{
    cout=$(( $cout + $i ))
}
echo Количество аргументов. Их среднее арифметическое.
echo -e "$(cat numbers.txt | wc -w) \c"
echo $(( $cout/$(cat numbers.txt | wc -w) ))