// GMIT Data Analytics 
// Adapted from: Multi-paradigm programming - Dr. Dominic Carr


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    int index;
};

struct Shop {
    double cash;
    struct ProductStock stock[20];
    int index;
};

void printProduct(struct Product p)
{
    printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);   
    printf("----------------\n");
};

void printCustomer(struct Customer c)
{
    printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);   
    printf("----------------\n");
    for(int i = 0; i < c.index; i++)
    {
        printProduct(c.shoppingList[i].product);
        printf("%s ORDERS %d of ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
        double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
        printf("The cost to %s will be E%.2f\n", c.name, cost);
        printf("----------------\n");
    }
};

void createAndStockShop()
{
    struct Shop shop = { 200 };
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE\n", line); 
        char* name = strtok(line, ",");
        char* price = strtok(NULL, ",");
        char* quantity = strtok(NULL, ",");
        printf("NAME OF PRODUCT %s PRICE %s QUANTITY %s\n", name, price, quantity);
    }
}

int main(void)
{
    // struct Customer sarah = { "Sarah", 100.0 };
    
    // struct Product coke = { "Can Coke", 1.10 };
    // struct Product bread = { "Bread", 0.7 };
    // // printProduct(coke);

    // struct ProductStock cokeStock = { coke, 20};
    // struct ProductStock breadStock = { bread, 2};
    // sarah.shoppingList[sarah.index++] = cokeStock;
    // sarah.shoppingList[sarah.index++] = breadStock;
    // printCustomer(sarah);
    // printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);

    createAndStockShop();

    return 0;
}