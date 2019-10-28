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

struct Shop createAndStockShop()
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    read = getline(&line, &len, fp);
    double cashInShop = atof(line);
    struct Shop shop = { cashInShop };

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE\n", line); 
        char* n = strtok(line, ",");
        char* p = strtok(NULL, ",");
        char* q = strtok(NULL, ",");
        int quantity = atoi(q);
        double price = atof(p);
        char* name = malloc(sizeof(char) * 50);
        strcpy( name, n );

        struct Product product = { name, price };
        struct ProductStock stockItem = { product, quantity };
        shop.stock[shop.index++] = stockItem;
        // printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }

    return shop;
}

void printShop(struct Shop s)
{
    printf("Shop has %.2f in cash\n\n", s.cash);
    for (int i = 0; i < s.index; i++)
    {
        printProduct(s.stock[i].product);
        printf("THE SHOP HAS %d of the above\n\n", s.stock[i].quantity);
    }
}

double findProductPrice(struct Shop s, char* n)
{
    for (int i = 0; i < s.index; i++)
    {
        struct Product product = s.stock[i].product;
        char* name = product.name;
        if (strcmp(name,n) == 0 ){
            return product.price;
        }
    }

    return -1;
}

struct Shop fulfillorder(Customer c, shop s)
{
    // verify quantities are available
    // verify customer has enough budget
    // subtract / add transaction
    // include appropriate error messages
}

struct Customer readShoppingList(struct Shop s)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("customer.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

//read name
    read = getline(&line, &len, fp);
    char* nameC = strtok(line, ",");
    char* nameCustomer = malloc(sizeof(char) * 50);
    strcpy( nameCustomer, nameC );
//read budget
    // read = getline(&line, &len, fp);
    char* bC = strtok(NULL, ",");
    double budgetCustomer = atof(bC);

    struct Customer customer = { nameCustomer, budgetCustomer };

    // printf("The name of the customer is %s and their budget is %.2f\n", nameCustomer, budgetCustomer);

//read their shoppinglist 
    while ((read = getline(&line, &len, fp)) != -1) {
        char* n = strtok(line, ",");
        char* q = strtok(NULL, ",");
        int quantity = atoi(q);
        char* name = malloc(sizeof(char) * 50);
        strcpy( name, n );

        double price = findProductPrice(s, name);
        struct Product Item = { name, price };
        struct ProductStock listItem = { Item, quantity };
        customer.shoppingList[customer.index++] = listItem;
        // printf("Added Product %s Quantity %d price %.2f", name, quantity, price );


        // struct ProductStock stockItem = { product, quantity };
        // shop.stock[shop.index++] = stockItem;
        // printf("NAME OF PRODUCT %s QUANTITY %d\n", name, quantity);
    }

    return customer;
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

    struct Shop shop = createAndStockShop();
    // printShop(shop);
    // double price = findProductPrice(shop, "Tomato Sauce");
    // printf("Price is %.2f", price);

    struct Customer customer = readShoppingList(shop);
    printCustomer(customer);



    return 0;
}