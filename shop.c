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
    // printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);   
    //printf("----------------\n");
};

void printCustomer(struct Customer c)
{
    printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);   
    printf("----------------\n");

    for(int i = 0; i < c.index; i++)
    {
        //printProduct(c.shoppingList[i].product);
        printf("%s ORDERS %d of %s\n", c.name, c.shoppingList[i].quantity, c.shoppingList[i].product.name);
        double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
        // printf("The cost to %s will be E%.2f\n", c.name, cost);
        // printf("----------------\n");
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
        //printf("THE SHOP HAS %d of the above\n\n", s.stock[i].quantity);
    }
}

double findProductPrice(struct Shop s, char* n)
{
    for (int i = 0; i < s.index; i++)
    {

        struct Product product = s.stock[i].product;
        char* name = product.name;
        //contains
        if (strstr(n,name) != NULL ){
            return product.price;
        }
    }

    return -1;
}

int requestMode()
{

    printf("Please choose 1 or 2\n");
    printf("1. I have submitted my order in advance. Please process my .csv\n");
    printf("2. I would like to order now\n");
    char mode[2];
    fgets(mode, sizeof(mode), stdin);
    // https://stackoverflow.com/questions/53900369/fgets-keeps-getting-skipped-before-entering-loop
    mode[strcspn(mode, "\n")] = 0;

    
    if (strcmp(mode,"1") == 0) {
        printf("You entered 1");
        int modeI = atoi(mode);
        return modeI;
    }
    else if (strcmp(mode,"2") == 0) {
        printf("You entered 2\n");
        int modeI = atoi(mode);
        return modeI;
    }
    else {
        printf("Sorry, we don't do that here. Please come again some other time \n\n");
        int modeI = atoi(mode);
        return modeI;        
    }
}

//struct Shop fulfillOrder(struct* Customer c, struct* Shop s)
void fulfillOrder(struct Customer* c, struct Shop* s)
{

    for (int i = 0; i < c->index; i++)

    {
        //printf("\n\n THE CUSTOMER %s WANTS %d of %s priced at %.2f each \n", c->name, c->shoppingList[i].quantity, c->shoppingList[i].product.name, c->shoppingList[i].product.price);

        // check the ShopStock by looping through shopstock and matching it with current item on shoppinglist
        for (int n = 0; n < s->index; n++)
        {
            printProduct(s->stock[n].product);
            
            if (strcmp(s->stock[n].product.name, c->shoppingList[i].product.name) == 0)
            {
                if (s->stock[n].quantity >= c->shoppingList[i].quantity) {
                    printf("The shop has enough of said product and will fulfill the order\n");
                    double cost = c->shoppingList[i].quantity * c->shoppingList[i].product.price;
                    // printf("Cost of item on shoppinglist is %.2f \n", cost);

                    // verify customer has enough budget
                    if (c->budget > cost) {
                        printf("Customers budget is %.2f and customer can aford cost %.2f\n", c->budget, cost);
                        c->budget -= cost;
                        printf("Customers budget has reduced to %.2f \n", c->budget);
                    }

                    s->cash += cost;
                    printf("THE SHOP'S CASH has increased to %.2f \n", s->cash);
                    // diminish the productstock accordingly
                    //s.stock[n].product.name

                    break;                   
                }
                else {
                    printf("The shop DOES NOT HAVE enough of said product \n");
                }
            }
        }

    }

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

    }

    return customer;
}

struct Customer recordOrder(struct Shop s)
{

    //get name
    printf("What is your name?\n");
    char nameC[20];
    //https://www.gamedev.net/forums/topic/589620-why-is-my-program-skipping-fgets/
    fgetc(stdin);
    fgets(nameC, sizeof(nameC), stdin);
    nameC[strcspn(nameC, "\n")] = 0;

    //get budget
    printf("What is your budget?\n");
    char bC[20];
    fgets(bC, sizeof(bC), stdin);
    // https://stackoverflow.com/questions/53900369/fgets-keeps-getting-skipped-before-entering-loop
    //bC[strcspn(bC, "\n")] = 0;
    double budgetCustomer = atof(bC);

    struct Customer customer = { nameC, budgetCustomer };
    printf("The name of the customer is %s and their budget is %.2f\n", nameC, budgetCustomer);


    int i=0;
    while (i < 3) {

        //get order
        printf("What would you like?\n");
        char productName[20];
        fgets(productName, sizeof(productName), stdin);
        productName[strcspn(productName, "\n")] = 0;

        printf("How many?\n");
        char pN[20];
        fgets(pN, sizeof(pN), stdin);
        int productNumber = atoi(pN);


        double price = findProductPrice(s, productName);
        struct Product Item = { productName, price };
        struct ProductStock listItem = { Item, productNumber };
        customer.shoppingList[customer.index++] = listItem;
        printf("Added Product %s Quantity %d price %.2f\n", productName, productNumber, price );
        i++;
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

    int mode = requestMode();
    
    if (mode == 1){
        struct Customer customer = readShoppingList(shop);
        struct Customer* CustomerCSV = &customer;
        struct Shop* ShopP = &shop;

        fulfillOrder(CustomerCSV,ShopP);
        printShop(shop);
        printCustomer(customer);
    }
    else if (mode == 2){
        struct Customer customerL = recordOrder(shop);
        printCustomer(customerL);
        struct Customer* CustomerLive = &customerL;
        struct Shop* ShopP = &shop;

        fulfillOrder(CustomerLive, ShopP);
        printShop(shop);
        printCustomer(customerL);
    }
    else
    {
        
    }
    

    // printCustomer(customer);

    // struct Shop shopAfter = fulfillOrder(customer, shop);
    // printShop(shopAfter);


    // return 0;
}