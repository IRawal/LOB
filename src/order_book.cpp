#include "order_book.h"

order_book::order_book() {
    this->orderTable = new std::unordered_map<int, Order*>();
    this->buyTree = new std::map<float, Limit*>();
    this->sellTree = new std::map<float, Limit*>();
}

void order_book::add_order(int id, Direction direction, int volume, float limitPrice, float entryTime) {
    /*
    Initialize new order
    Add it to the order table
    Add it to the buy/sell tree
    if limit exists add order, otherwise create new limit and add order
    correctly relink list
    update limit volume
    link limit to order
    */
    Order* newOrder = new Order();

    orderTable->insert({id, newOrder});

    newOrder->id = id;
    newOrder->direction = direction;
    newOrder->volume = volume;
    newOrder->limitPrice = limitPrice;
    newOrder->entryTime = entryTime;

    std::map<float, Limit*>* tree = (direction == Direction::BUY) ? this->buyTree : this->sellTree;

    Limit* limit;

    if (tree->count(limitPrice) == 0) {
        limit = new Limit();

        limit->limitPrice = limitPrice;
        limit->volume;
        limit->headOrder = newOrder;
        limit->tailOrder = newOrder;
    }
    else {
        limit = tree->find(limitPrice)->second;
        
        limit->tailOrder->next = newOrder;
        newOrder->prev = limit->tailOrder;
        limit->tailOrder = newOrder;

        limit->volume += newOrder->volume;
    }
    newOrder->parent = limit;
}
void order_book::cancel_order(int id) {
    Order* order = this->orderTable->find(id)->second;
    Limit* limit = order->parent;

    // Fix limit pointsers
    if (limit->tailOrder == order)
        limit->tailOrder = order->prev;
    if (limit->headOrder == order)
        limit->headOrder = order->next;
    
    // Fix order linked list
    if (order->prev != nullptr)
        order->prev->next = order->next;
    if (order->next != nullptr)
        order->next->prev = order->prev;
    
    // Update volume
    limit->volume -= order->volume;

    // Actually remove order
    this->orderTable->erase(id);
    delete order;
}
void order_book::execute_order(int id, Direction direction, int quantity, float price) {
    Order* order = this->orderTable->find(id)->second;
    if (quantity < order->volume) {
        order->volume -= quantity;
        return;
    }
    cancel_order(id);
}