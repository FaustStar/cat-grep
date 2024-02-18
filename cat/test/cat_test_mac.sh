#!/bin/bash

test_data="./test"
successed_number=0
failed_number=0
test_number=1

for file in $test_data/*.txt; do
    for flag in -b -e -n -s -t -v -et -best -ent -tesnv -bn; do
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

for flag in -b -e -n -s -t -v -et -best -ent -tesnv -bn; do
    echo "Test #$test_number"
    echo "Input check: s21_cat/cat $flag $test_data/ascii-mac.txt1"
    ./s21_cat $flag $test_data/ascii-mac.txt1 > s21cat_result
    cat $flag $test_data/ascii-mac.txt1 > cat_result
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