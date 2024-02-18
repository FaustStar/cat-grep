#!/bin/bash

test_data="./test"
successed_number=0
failed_number=0
test_number=1

for file in $test_data/*.txt; do
    for flag in -b -e -n -s -t -v -T -E --number-nonblank --number --squeeze-blank -et -best -ent -TEsnv -bn; do
        echo "Test #$test_number"
        echo "Input check: s21_cat/cat $flag $file"
        ./s21_cat $flag $file > s21cat_result
        cat $flag $file > cat_result
        if diff -s s21cat_result cat_result; then
            successed_number=$((successed_number + 1))
            echo "Result: SUCCESS"
        else
            failed_number=$((failed_number + 1))
            echo "Result: FAIL"
        fi
        test_number=$((test_number + 1))
        echo "----------------------------------------------"
    done
done

for flag in -b -e -n -s -t -v -T -E --number-nonblank --number --squeeze-blank -et -best -ent -TEsnv -bn; do
    echo "Test #$test_number"
    echo "Input check: s21_cat/cat $test_data/ascii.txt1 $flag $test_data/test3.txt"
    ./s21_cat $test_data/ascii.txt1 $flag $test_data/test3.txt > s21cat_result
    cat $test_data/ascii.txt1 $flag $test_data/test3.txt > cat_result
    if diff -s s21cat_result cat_result; then
        successed_number=$((successed_number + 1))
        echo "Result: SUCCESS"
    else
        failed_number=$((failed_number + 1))
        echo "Result: FAIL"
    fi
    test_number=$((test_number + 1))
    echo "----------------------------------------------"
done

rm s21cat_result cat_result
echo "Summary:"
echo "Number of successed tests: $successed_number"
echo "Number of failed tests: $failed_number"