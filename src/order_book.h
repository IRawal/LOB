#include <unordered_map>
#include <map>

enum Direction {
    BUY,
    SELL
};

struct Limit;

struct Order {
    int id;
    Direction direction;
    int volume;
    float limitPrice;
    float entryTime;
    Order* next;
    Order* prev;
    Limit* parent;
};

struct Limit {
    float limitPrice;
    int volume;
    Order *headOrder;
    Order *tailOrder;
};

class order_book {
    public:
        order_book();
        void add_order(int id, Direction direction, int volume, float limitPrice, float entryTime);
        void cancel_order(int id);
        void execute_order(int id, Direction direction, int quantity, float price);

    private:
        std::unordered_map<int, Order*>* orderTable;
        std::map<float, Limit*>* buyTree;
        std::map<float, Limit*>* sellTree;
};