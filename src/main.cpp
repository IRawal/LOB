#include <iostream>
#include <chrono>
#include <ctime>

#include "order_book.h"

/* Simulate recieving a million orders */
void test_book() {
    order_book* orderBook = new order_book();
    for (int i = 0; i < 10e6; i++) {
        orderBook->add_order(i, Direction::BUY, 1, 10, 0);
    }
}
int main() {
    test_book();
}

