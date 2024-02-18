#!/bin/bash

test_data="./test"
successed_number=0
failed_number=0
test_number=1

#testing of -i -v -c -l -n -o flags
for file in $test_data/*.txt; do
    for flag in -i -v -c -l -n -o -iv -vc -vn -vl -cin -cinv -onc -nocvi; do
        for pattern in he step was at; do
            echo "Test #$test_number"
            echo "Input check: s21_grep/grep $flag $pattern $file"
            ./s21_grep $flag $pattern $file > s21grep_result
            grep $flag $pattern $file > grep_result
            if diff -s s21grep_result grep_result; then
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
done

#testing of -h -e -f flags
for flag in -i -v -c -l -n -h -iv -vho -vc -vnh -vl -cino -cinv -nco -ncvoi -lh -hnoc -ncvih; do
    for pattern in when both master seemed; do
        echo "Test #$test_number"
        echo "Input check: s21_grep/grep -e $pattern -f $test_data/pattern.txt $test_data/test1.txt $flag $test_data/test4.txt"
        ./s21_grep -e $pattern -f $test_data/pattern.txt $test_data/test1.txt $flag $test_data/test4.txt > s21grep_result
        grep -e $pattern -f $test_data/pattern.txt $test_data/test1.txt $flag $test_data/test4.txt > grep_result
        if diff -s s21grep_result grep_result; then
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

#testing of -s flag
for flag in -s -ivs -vohs -vcs -vnhs -vls -lcins -cinvs -oncs -nocvis -nocvils -lhs -honcs -oncvihs -conhilvs; do
    for pattern in black some seven; do
        echo "Test #$test_number"
        echo "Input check: s21_grep/grep -e $pattern -f $test_data/pattern.txt $test_data/test21.txt $flag"
        ./s21_grep -e $pattern -f $test_data/pattern.txt $test_data/test21.txt $flag > s21grep_result
        grep -e $pattern -f $test_data/pattern.txt $test_data/test21.txt $flag > grep_result
        if diff -s s21grep_result grep_result; then
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

rm s21grep_result grep_result
echo "Summary:"
echo "Number of successed tests: $successed_number"
echo "Number of failed tests: $failed_number"