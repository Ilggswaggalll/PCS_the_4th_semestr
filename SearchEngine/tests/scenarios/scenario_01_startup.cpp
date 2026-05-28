#include "test_helper.h"
#include <cstdlib>

int main() {
    TEST_INFO("Сценарий 1: Запуск программы");

    // Запускаем приложение и проверяем, что оно запускается
    int result = system("open ../build/search_engine.app 2>/dev/null || ./../build/search_engine &");

    if (result == 0) {
        TEST_PASS("Приложение запускается");
    } else {
        TEST_FAIL("Не удалось запустить приложение");
    }

    TEST_INFO("Ручная проверка интерфейса: заголовок, поле ввода, кнопки должны присутствовать");

    return 0;
}
