#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "quicksort.h"

static void test_sorted_result_from_random_array(void **state) {
    (void) state;
    int arr[5];
    generateArray(arr, 5, 1);
    Quicksort(0, 4, arr);
    for (int i = 0; i < 4; i++) {
        assert_true(arr[i] <= arr[i + 1]);
    }
}

static void test_sorted_result_from_descending_array(void **state) {
    (void) state;
    int arr[5];
    generateArray(arr, 5, 0);
    Quicksort(0, 4, arr);
    for (int i = 0; i < 4; i++) {
        assert_true(arr[i] <= arr[i + 1]);
    }
}

static void test_sorted_result_from_ascending_array(void **state) {
    (void) state;
    int arr[5];
    generateArray(arr, 5, 2);
    Quicksort(0, 4, arr);
    for (int i = 0; i < 4; i++) {
        assert_true(arr[i] <= arr[i + 1]);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sorted_result_from_random_array),
        cmocka_unit_test(test_sorted_result_from_descending_array),
        cmocka_unit_test(test_sorted_result_from_ascending_array),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}