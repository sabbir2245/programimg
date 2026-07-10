#include <iostream>
#include <vector>
#include <string>

class Product {
public:
    Product(const std::string& name, double price) : name(name), price(price), available(true) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    bool isAvailable() const { return available; }
    void markUnavailable() { available = false; }

private:
    std::string name;
    double price;
    bool available;
};

class CartItem {
public:
    CartItem(const Product& product, int quantity) : product(product), quantity(quantity) {}

    const Product& getProduct() const { return product; }
    int getQuantity() const { return quantity; }

private:
    Product product;
    int quantity;
};

class User {
public:
    User(const std::string& username, const std::string& password) : username(username), password(password) {}

    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }

private:
    std::string username;
    std::string password;
};

class Order {
public:
    Order(const std::vector<CartItem>& items) : items(items), orderStatus("Pending") {}

    const std::vector<CartItem>& getItems() const { return items; }
    std::string getStatus() const { return orderStatus; }
    void setStatus(const std::string& status) { orderStatus = status; }

private:
    std::vector<CartItem> items;
    std::string orderStatus;
};

class ShoppingCart {
public:
    void addItem(const Product& product, int quantity) {
        items.emplace_back(product, quantity);
    }

    const std::vector<CartItem>& getItems() const { return items; }
    void clear() { items.clear(); }

private:
    std::vector<CartItem> items;
};

int main() {
    Product product1("Item 1", 10.0);
    Product product2("Item 2", 20.0);

    User user("username", "password");

    ShoppingCart cart;
    cart.addItem(product1, 2);
    cart.addItem(product2, 1);

    Order order(cart.getItems());
    order.setStatus("Placed");

    std::cout << "Order details:\n";
    for (const CartItem& item : order.getItems()) {
        std::cout << item.getProduct().getName() << " - Quantity: " << item.getQuantity() << "\n";
    }

    return 0;
}
