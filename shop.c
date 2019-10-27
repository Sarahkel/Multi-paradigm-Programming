#include <stdio.h>
#include <string.h>

struct Product {
    char* name;
    double price;
};

struct ProductStock {
    struct Product product;
    int quantity;
};

struct Customer {
    char* name;
    double budget;
    struct ProductStock shoppingList[10];
};

struct Shop {
    double cash;
    struct ProductStock stock[20];
};

void printProduct(struct Product p)
{
    printf("----------------\n");
    printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);   
    printf("----------------\n");
};

int main(void)
{
    struct Customer sarah = { "Sarah", 100.0 };
    printf("Customer name is %s\n",sarah.name);
    
    struct Product coke = { "Can Coke", 1.10 };
    printProduct(coke);

    struct ProductStock cokeStock = { coke, 20};
    printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);

    return 0;
}