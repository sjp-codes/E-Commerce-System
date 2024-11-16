#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 50
#define MAX_USERID_LEN 20
#define MAX_PSW_LEN 20
#define MAX_EMAIL_LEN 50
#define MAX_ADDR_LEN 50
#define MAX_MOBILE_LEN 20
#define MAX_PRODUCT_NAME_LEN 50
#define MAX_CATEGORY_LEN 20
#define MAX_DESC_LEN 50
#define MAX_PRICE_LEN 20
#define USER_TABLE_SIZE 100
#define PRODUCT_TABLE_SIZE 100

// Structures
typedef struct {
    char userID[MAX_USERID_LEN];
    char userName[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];
    char mobile[MAX_MOBILE_LEN];
    char address[MAX_ADDR_LEN];
    char password[MAX_PSW_LEN];
} User;

typedef struct ProductNode {
    char productID[MAX_PRODUCT_NAME_LEN];
    char productName[MAX_PRODUCT_NAME_LEN];
    char category[MAX_CATEGORY_LEN];
    float price;
    char description[MAX_DESC_LEN];
    float quantity;
    struct ProductNode* next;  // For related products
} ProductNode;

typedef struct {
    ProductNode* browsingHistory;
    ProductNode* purchaseHistory;
} UserHistory;

typedef struct {
    User* users[USER_TABLE_SIZE];
    ProductNode* products[PRODUCT_TABLE_SIZE];
    UserHistory* userHistories[USER_TABLE_SIZE];
} HashTable;

// Hash function
unsigned int hashString(const char* str, unsigned int tableSize) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % tableSize;
}

// Initialize hash table
void initHashTable(HashTable* table) {
    for (int i = 0; i < USER_TABLE_SIZE; i++) {
        table->users[i] = NULL;
        table->userHistories[i] = NULL;
    }
    for (int i = 0; i < PRODUCT_TABLE_SIZE; i++) {
        table->products[i] = NULL;
    }
}

// Add user
void addUser(HashTable* table, char userID[], char userName[], char email[], 
             char mobile[], char address[], char password[]) {
    unsigned int index = hashString(userID, USER_TABLE_SIZE);
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->userID, userID);
    strcpy(newUser->userName, userName);
    strcpy(newUser->email, email);
    strcpy(newUser->mobile, mobile);
    strcpy(newUser->address, address);
    strcpy(newUser->password, password);

    table->users[index] = newUser;

    // Initialize user history
    UserHistory* newUserHistory = (UserHistory*)malloc(sizeof(UserHistory));
    newUserHistory->browsingHistory = NULL;
    newUserHistory->purchaseHistory = NULL;
    table->userHistories[index] = newUserHistory;

    printf("User %s added successfully!\n", userID);
}

// Create product node
ProductNode* createProductNode(char productID[], char productName[], char category[], 
                             float price, char description[], float quantity) {
    ProductNode* newNode = (ProductNode*)malloc(sizeof(ProductNode));
    strcpy(newNode->productID, productID);
    strcpy(newNode->productName, productName);
    strcpy(newNode->category, category);
    newNode->price = price;
    strcpy(newNode->description, description);
    newNode->quantity = quantity;
    newNode->next = NULL;
    return newNode;
}

// Add product
void addProduct(HashTable* table, char productID[], char productName[], char category[], 
                float price, char description[], float quantity) {
    unsigned int index = hashString(productID, PRODUCT_TABLE_SIZE);
    ProductNode* newProduct = createProductNode(productID, productName, category, 
                                              price, description, quantity);
    table->products[index] = newProduct;
    printf("Product %s added successfully!\n", productID);
}

// Get product by ID
ProductNode* getProductByID(HashTable* table, char productID[]) {
    for (int i = 0; i < PRODUCT_TABLE_SIZE; i++) {
        ProductNode* current = table->products[i];
        while (current != NULL) {
            if (strcmp(current->productID, productID) == 0) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

// Get product by name
ProductNode* getProductByName(HashTable* table, char productName[]) {
    for (int i = 0; i < PRODUCT_TABLE_SIZE; i++) {
        ProductNode* current = table->products[i];
        while (current != NULL) {
            if (strcmp(current->productName, productName) == 0) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

// Display product
void displayProduct(ProductNode* product) {
    if (product != NULL) {
        printf("\nProduct ID: %s\n", product->productID);
        printf("Name: %s\n", product->productName);
        printf("Category: %s\n", product->category);
        printf("Price: %.2f\n", product->price);
        printf("Description: %s\n", product->description);
        printf("Quantity: %.2f\n", product->quantity);
        printf("------------------------\n");
    }
}

// Display products by category
void displayProductsByCategory(HashTable* table, char category[]) {
    printf("\nProducts in category '%s':\n", category);
    for (int i = 0; i < PRODUCT_TABLE_SIZE; i++) {
        ProductNode* current = table->products[i];
        while (current != NULL) {
            if (strcmp(current->category, category) == 0) {
                displayProduct(current);
            }
            current = current->next;
        }
    }
}

// Record browsing history
void recordBrowsingHistory(HashTable* table, User* loggedInUser, char productName[]) {
    if (loggedInUser != NULL) {
        unsigned int userIndex = hashString(loggedInUser->userID, USER_TABLE_SIZE);
        UserHistory* userHistory = table->userHistories[userIndex];
        ProductNode* product = getProductByName(table, productName);
        if (product != NULL) {
            ProductNode* newNode = createProductNode(product->productID, product->productName,
                                                   product->category, product->price,
                                                   product->description, product->quantity);
            newNode->next = userHistory->browsingHistory;
            userHistory->browsingHistory = newNode;
        }
    }
}

// Record purchase history
void recordPurchaseHistory(HashTable* table, User* loggedInUser, char productName[]) {
    if (loggedInUser != NULL) {
        unsigned int userIndex = hashString(loggedInUser->userID, USER_TABLE_SIZE);
        UserHistory* userHistory = table->userHistories[userIndex];
        ProductNode* product = getProductByName(table, productName);
        if (product != NULL) {
            ProductNode* newNode = createProductNode(product->productID, product->productName,
                                                   product->category, product->price,
                                                   product->description, product->quantity);
            newNode->next = userHistory->purchaseHistory;
            userHistory->purchaseHistory = newNode;
        }
    }
}

// User login
int userLogin(HashTable* table, char userID[], char password[], User** loggedInUser) {
    unsigned int index = hashString(userID, USER_TABLE_SIZE);
    if (table->users[index] != NULL && strcmp(table->users[index]->password, password) == 0) {
        *loggedInUser = table->users[index];
        return 1;
    }
    return 0;
}

// Add product relationship
void addProductRelationship(HashTable* table, char productID1[], char productID2[]) {
    ProductNode* product1 = getProductByID(table, productID1);
    ProductNode* product2 = getProductByID(table, productID2);

    if (product1 != NULL && product2 != NULL) {
        ProductNode* relatedNode1 = createProductNode(product2->productID, product2->productName,
                                                    product2->category, product2->price,
                                                    product2->description, product2->quantity);
        relatedNode1->next = product1->next;
        product1->next = relatedNode1;

        ProductNode* relatedNode2 = createProductNode(product1->productID, product1->productName,
                                                    product1->category, product1->price,
                                                    product1->description, product1->quantity);
        relatedNode2->next = product2->next;
        product2->next = relatedNode2;

        printf("Products %s and %s are now related.\n", productID1, productID2);
    } else {
        printf("One or both products not found.\n");
    }
}

// Check if product is in browsing history
int isInBrowsingHistory(UserHistory* userHistory, char* productID) {
    ProductNode* current = userHistory->browsingHistory;
    while (current != NULL) {
        if (strcmp(current->productID, productID) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Generate recommendations
void generateRecommendations(HashTable* table, User* loggedInUser, char* productID) {
    ProductNode* currentProduct = getProductByID(table, productID);
    if (currentProduct == NULL || loggedInUser == NULL) {
        printf("Product or user not found.\n");
        return;
    }

    unsigned int userIndex = hashString(loggedInUser->userID, USER_TABLE_SIZE);
    UserHistory* userHistory = table->userHistories[userIndex];
    
    printf("\nRecommended Products:\n");
    printf("--------------------\n");
    
    int recommendationsFound = 0;
    
    // Recommend products from same category
    for (int i = 0; i < PRODUCT_TABLE_SIZE && recommendationsFound < 5; i++) {
        ProductNode* product = table->products[i];
        while (product != NULL && recommendationsFound < 5) {
            if (strcmp(product->productID, productID) != 0 && 
                !isInBrowsingHistory(userHistory, product->productID)) {
                
                if (strcmp(product->category, currentProduct->category) == 0) {
                    printf("\nBased on your current selection:\n");
                    displayProduct(product);
                    recommendationsFound++;
                }
            }
            product = product->next;
        }
    }
    
    // Add related products if needed
    if (recommendationsFound < 5) {
        ProductNode* related = currentProduct->next;
        while (related != NULL && recommendationsFound < 5) {
            if (!isInBrowsingHistory(userHistory, related->productID)) {
                printf("\nRelated product:\n");
                displayProduct(related);
                recommendationsFound++;
            }
            related = related->next;
        }
    }
    
    if (recommendationsFound == 0) {
        printf("No recommendations found.\n");
    }
}

// Main menu
void mainMenu(HashTable* table) {
    int choice;
    User* loggedInUser = NULL;

    while (1) {
        if (loggedInUser != NULL) {
            printf("\nHello, %s\n", loggedInUser->userName);
        }

        printf("\n>> MAIN MENU <<\n");
        printf("1. User Login\n");
        printf("2. View Product\n");
        printf("3. View Products by Category\n");
        printf("4. Billing (Record Purchase)\n");
        printf("5. View Browsing History\n");
        printf("6. View Purchase History\n");
        printf("7. Add Product Relationship\n");
        printf("8. Generate Recommendations\n");
        printf("9. Logout\n");
        printf("10. Add User\n");
        printf("11. Add Product\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char userID[MAX_USERID_LEN], password[MAX_PSW_LEN];
                printf("Enter User ID: ");
                scanf("%s", userID);
                printf("Enter Password: ");
                scanf("%s", password);
                if (userLogin(table, userID, password, &loggedInUser)) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid credentials.\n");
                }
                break;
            }
            case 2: {
                if (loggedInUser != NULL) {
                    char productName[MAX_PRODUCT_NAME_LEN];
                    printf("Enter product name: ");
                    scanf("%s", productName);
                    ProductNode* product = getProductByName(table, productName);
                    if (product != NULL) {
                        displayProduct(product);
                        recordBrowsingHistory(table, loggedInUser, productName);
                    } else {
                        printf("Product not found.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 3: {
                if (loggedInUser != NULL) {
                    char category[MAX_CATEGORY_LEN];
                    printf("Enter category: ");
                    scanf("%s", category);
                    displayProductsByCategory(table, category);
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 4: {
                if (loggedInUser != NULL) {
                    char productName[MAX_PRODUCT_NAME_LEN];
                    printf("Enter product name to purchase: ");
                    scanf("%s", productName);
                    recordPurchaseHistory(table, loggedInUser, productName);
                    printf("Purchase recorded successfully.\n");
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 5: {
                if (loggedInUser != NULL) {
                    unsigned int userIndex = hashString(loggedInUser->userID, USER_TABLE_SIZE);
                    UserHistory* userHistory = table->userHistories[userIndex];
                    printf("\nBrowsing History:\n");
                    ProductNode* current = userHistory->browsingHistory;
                    while (current != NULL) {
                        displayProduct(current);
                        current = current->next;
                    }
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 6: {
                if (loggedInUser != NULL) {
                    unsigned int userIndex = hashString(loggedInUser->userID, USER_TABLE_SIZE);
                    UserHistory* userHistory = table->userHistories[userIndex];
                    printf("\nPurchase History:\n");
                    ProductNode* current = userHistory->purchaseHistory;
                    while (current != NULL) {
                        displayProduct(current);
                        current = current->next;
                    }
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 7: {
                if (loggedInUser != NULL) {
                    char productID1[MAX_PRODUCT_NAME_LEN], productID2[MAX_PRODUCT_NAME_LEN];
                    printf("Enter Product ID 1: ");
                    scanf("%s", productID1);
                    printf("Enter Product ID 2: ");
                    scanf("%s", productID2);
                    addProductRelationship(table, productID1, productID2);
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 8: {
                if (loggedInUser != NULL) {
                    char productID[MAX_PRODUCT_NAME_LEN];
                    unsigned int userIndex = hashString(loggedInUser->userID, USER_TABLE_SIZE);
                    UserHistory* userHistory = table->userHistories[userIndex];
                    ProductNode* current = userHistory->purchaseHistory;
                    if (current != NULL) {
                        strcpy(productID, current->productID);
                        generateRecommendations(table, loggedInUser, productID);
                    } else {
                        printf("No purchase history found for the user.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                break;
            }
            case 9: {
                loggedInUser = NULL;
                printf("Logged out successfully.\n");
                break;
            }
            case 10: {
                char userID[MAX_USERID_LEN], userName[MAX_NAME_LEN], email[MAX_EMAIL_LEN];
                char mobile[MAX_MOBILE_LEN], address[MAX_ADDR_LEN], password[MAX_PSW_LEN];
                printf("Enter User ID: ");
                scanf("%s", userID);
                printf("Enter User Name: ");
                scanf("%s", userName);
                printf("Enter Email: ");
                scanf("%s", email);
                printf("Enter Mobile: ");
                scanf("%s", mobile);
                printf("Enter Address: ");
                scanf("%s", address);
                printf("Enter Password: ");
                scanf("%s", password);
                addUser(table, userID, userName, email, mobile, address, password);
                break;
            }
            case 11: {
                char productID[MAX_PRODUCT_NAME_LEN], productName[MAX_PRODUCT_NAME_LEN], category[MAX_CATEGORY_LEN];
                char description[MAX_DESC_LEN];
                float price, quantity;

                printf("Enter Product ID: ");
                scanf("%s", productID);
                printf("Enter Product Name: ");
                scanf("%s", productName);
                printf("Enter Category: ");
                scanf("%s", category);
                printf("Enter Price: ");
                scanf("%f", &price);
                printf("Enter Description: ");
                scanf(" %[^\n]", description);  
                printf("Enter Quantity: ");
                scanf("%f", &quantity);

                addProduct(table, productID, productName, category, price, description, quantity);
                break;
            }
            case 12: {
                printf("Exiting...\n");
                return;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

int main() {
    HashTable table;
    initHashTable(&table);
    mainMenu(&table);
    return 0;
}