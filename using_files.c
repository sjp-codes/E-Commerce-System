#include <stdio.h>
#include <string.h>

// requires cart.txt , products.txt, users.txt

// Structure for User
struct User {
    char Name[60];
    char Email[30];
    char Mobileno[15];
    char Address[20];
    char UserId[20];
    char Password[10];
};

// Structure for Product
struct Product {
    char Name[50];
    int Price;
    int Quantity;
    char Description[50];
    char Category[20];
};

// Function Prototypes for User
void UserRegistration();
int UserLogin();

// Function Prototypes for Product
void AddProduct();
void UpdateProduct();
void DeleteProduct();
void CategoryProduct();
void AvailabilityProduct();
void DisplayAll();
void SearchItem();

// Function Prototypes for Shopping Cart
void UserShoppingCart();
void UserShoppingCartCheckout();
void YourCart();
void AddToCart();

int main() {
    int a, b, c, d;

    while (1) {
        printf("\n>>>> MAIN MENU <<<<\n");
        printf("1. Users\n");
        printf("2. Administration\n");
        printf("3. Quit\n");
        printf("Enter your choice(1/2/3): ");
        scanf("%d", &a);
        printf("====================================================================\n");

        switch (a) {
            case 1:
                printf(">>>> OPTIONS <<<<\n");
                printf("1. User Registration\n");
                printf("2. Login\n");
                printf("3. Shopping Cart\n");
                printf("4. Back\n");
                printf("Enter your choice(1/2/3/4): ");
                scanf("%d", &b);
                printf("====================================================================\n");
                switch (b) {
                    case 1:
                        printf("Option 1: User Registration\n");
                        UserRegistration();
                        break;
                    case 2:
                        printf("Option 2: Login\n");
                        UserLogin();
                        break;
                    case 3:
                        printf("Option 3: Shopping Cart\n");
                        UserShoppingCart();
                        break;
                    case 4:
                        break; 
                    default:
                        printf("Invalid option\n");
                        break;
                }
                break; 
            case 2:
                printf(">>>> OPTIONS <<<<\n");
                printf("1. Products\n");
                printf("2. Stats\n");
                printf("3. Back\n");
                printf("Enter your choice(1/2/3): ");
                scanf("%d", &c);
                printf("====================================================================\n");
                switch (c) {
                    case 1:
                        printf("Option 1: Products\n");
                        printf(">>>> OPTIONS <<<<\n");
                        printf("1. Add Products\n");
                        printf("2. Update Products\n");
                        printf("3. Delete Products\n");
                        printf("4. Back\n");
                        printf("Enter your choice(1/2/3/4): ");
                        scanf("%d", &d);
                        printf("====================================================================\n");
                        switch (d) {
                            case 1:
                                printf("Option 1: Add Products\n");
                                AddProduct();
                                break;
                            case 2:
                                printf("Option 2: Update Products\n");
                                UpdateProduct();
                                break;
                            case 3:
                                printf("Option 3: Delete Products\n");
                                DeleteProduct();
                                break;
                            case 4:
                                break; 
                            default:
                                printf("Invalid option\n");
                                break;
                        }
                        break;
                    case 2:
                        printf("Option 2: Stats\n");
                        printf("Module to be skipped.");
                        break;
                    case 3:
                        break; 
                    default:
                        printf("Invalid option\n");
                        break;
                }
                break; 
            case 3:
                return 0; 
            default:
                printf("Invalid option\n");
                break;
        }
    }

    return 0;
}

// User Functions
void UserRegistration() {
    FILE *usersFile;
    usersFile = fopen("users.txt", "a"); // Open file in append mode

    if (usersFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct User newUser;

    printf("Enter Name: ");
    scanf("%s", newUser.Name);

    printf("Enter Email: ");
    scanf("%s", newUser.Email);

    printf("Enter Mobile no: ");
    scanf("%s", newUser.Mobileno);

    printf("Enter UserID: ");
    scanf("%s", newUser.UserId);

    printf("Enter Password: ");
    scanf("%s", newUser.Password);

    printf("Enter Address: ");
    scanf("%s", newUser.Address);

    fprintf(usersFile, "%s %s %s %s %s %s\n", newUser.Name, newUser.Email, newUser.Mobileno, newUser.UserId, newUser.Password, newUser.Address);

    fclose(usersFile);
}

int UserLogin() {
    char login_uname[20];
    char login_psw[10];
    printf("Enter your User ID: ");
    scanf("%s", login_uname);
    printf("Enter your Password: ");
    scanf("%s", login_psw);

    FILE *usersFile;
    usersFile = fopen("users.txt", "r");

    if (usersFile == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    struct User currentUser;

    while (fscanf(usersFile, "%s %s %s %s %s %s\n", currentUser.Name, currentUser.Email, currentUser.Mobileno, currentUser.UserId, currentUser.Password, currentUser.Address) != EOF) {
        if (strcmp(login_uname, currentUser.UserId) == 0 && strcmp(login_psw, currentUser.Password) == 0) {
            printf("Welcome!! You are logged in as %s\n", login_uname);
            fclose(usersFile);
            return 1;
        }
    }

    fclose(usersFile);
    printf("Wrong User ID or PIN entered\n");
    return 0;
}

// Product Functions

void AddProduct() {
    FILE *productsFile;
    productsFile = fopen("products.txt", "a");

    if (productsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Product newProduct;

    printf("Enter Product Name: ");
    scanf("%s", newProduct.Name);

    printf("Enter Category: ");
    scanf("%s", newProduct.Category);

    printf("Enter Product Description: ");
    scanf("%s", newProduct.Description);

    printf("Enter Product Price: ");
    scanf("%d", &newProduct.Price);

    printf("Enter Product Quantity: ");
    scanf("%d", &newProduct.Quantity);

    fprintf(productsFile, "%s %s %s %d %d\n", newProduct.Name, newProduct.Category, newProduct.Description, newProduct.Price, newProduct.Quantity);

    fclose(productsFile);
}

void UpdateProduct() {
    FILE *productsFile;
    FILE *tempFile;
    productsFile = fopen("products.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (productsFile == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char prod_upd[50];
    printf("Enter the product to be updated: ");
    scanf("%s", prod_upd);

    struct Product currentProduct;

    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        if (strcmp(currentProduct.Name, prod_upd) == 0) {
            printf("Enter Product Name: ");
            scanf("%s", currentProduct.Name);
            printf("Enter Category: ");
            scanf("%s", currentProduct.Category);
            printf("Enter Product Description: ");
            scanf("%s", currentProduct.Description);
            printf("Enter Product Price: ");
            scanf("%d", &currentProduct.Price);
            printf("Enter Product Quantity: ");
            scanf("%d", &currentProduct.Quantity);
        }
        fprintf(tempFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, currentProduct.Price, currentProduct.Quantity);
    }

    fclose(productsFile);
    fclose(tempFile);

    remove("products.txt");
    rename("temp.txt", "products.txt");

    printf("Product updated successfully!\n");
}

void DeleteProduct() {
    FILE *productsFile;
    FILE *tempFile;
    productsFile = fopen("products.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (productsFile == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char prod_del[50];
    printf("Enter the product to be deleted: ");
    scanf("%s", prod_del);

    struct Product currentProduct;

    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        if (strcmp(currentProduct.Name, prod_del) != 0) {
            fprintf(tempFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, currentProduct.Price, currentProduct.Quantity);
        }
    }

    fclose(productsFile);
    fclose(tempFile);

    remove("products.txt");
    rename("temp.txt", "products.txt");

    printf("Product deleted successfully!\n");
}

void CategoryProduct() {
    char category[20];
    printf("Enter the category: ");
    scanf("%s", category);

    FILE *productsFile;
    productsFile = fopen("products.txt", "r");

    if (productsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Product currentProduct;

    printf("Products in category '%s':\n", category);
    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        if (strcmp(currentProduct.Category, category) == 0) {
            printf("Name: %s, Description: %s, Price: %d, Quantity: %d\n", currentProduct.Name, currentProduct.Description, currentProduct.Price, currentProduct.Quantity);
        }
    }

    fclose(productsFile);
}

void AvailabilityProduct() {
    char productName[50];
    printf("Enter the product name: ");
    scanf("%s", productName);

    FILE *productsFile;
    productsFile = fopen("products.txt", "r");

    if (productsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Product currentProduct;

    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        if (strcmp(currentProduct.Name, productName) == 0) {
            printf("Product '%s' is available.\n", productName);
            printf("Name: %s, Description: %s, Price: %d, Quantity: %d\n", currentProduct.Name, currentProduct.Description, currentProduct.Price, currentProduct.Quantity);
            fclose(productsFile);
            return;
        }
    }

    fclose(productsFile);
    printf("Product '%s' is not available.\n", productName);
}


void DisplayAll() {
    FILE *productsFile;
    productsFile = fopen("products.txt", "r");

    if (productsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Product currentProduct;

    printf("All Products:\n");
    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        printf("Name: %s, Category: %s, Description: %s, Price: %d, Quantity: %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, currentProduct.Price, currentProduct.Quantity);
    }

    fclose(productsFile);
}

void SearchItem() {
    char productName[50];
    printf("Enter the product name to search: ");
    scanf("%s", productName);

    FILE *productsFile;
    productsFile = fopen("products.txt", "r");

    if (productsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Product currentProduct;

    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        if (strcmp(currentProduct.Name, productName) == 0) {
            printf("Product Found:\n");
            printf("Name: %s, Category: %s, Description: %s, Price: %d, Quantity: %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, currentProduct.Price, currentProduct.Quantity);
            fclose(productsFile);
            return;
        }
    }

    fclose(productsFile);
    printf("Product '%s' not found.\n", productName);
}

// Shopping Cart Functions

void UserShoppingCart() {
    int c;

    while (1) {
        printf(">>>> Shopping Cart Options <<<<\n");
        printf("1. Display All Products\n");
        printf("2. Search Item\n");
        printf("3. Search by Category\n");
        printf("4. Check Availability\n");
        printf("5. Add to Cart\n");
        printf("6. View Your Cart\n");
        printf("7. Checkout\n");
        printf("8. Back\n");
        printf("Enter your choice(1/2/3/4/5/6/7/8): ");
        scanf("%d", &c);
        printf("====================================================================\n");

        switch (c) {
            case 1:
                DisplayAll();
                break;
            case 2:
                SearchItem();
                break;
            case 3:
                CategoryProduct();
                break;
            case 4:
                AvailabilityProduct();
                break;
            case 5:
                AddToCart();
                break;
            case 6:
                YourCart();
                break;
            case 7:
                UserShoppingCartCheckout();
                break;
            case 8:
                return;
            default:
                printf("Invalid option\n");
                break;
        }
    }
}

void AddToCart() {
    char productName[50];
    int quantity;

    printf("Enter the product name to add to cart: ");
    scanf("%s", productName);

    FILE *productsFile;
    productsFile = fopen("products.txt", "r");

    if (productsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Product currentProduct;
    int productFound = 0;

    while (fscanf(productsFile, "%s %s %s %d %d\n", currentProduct.Name, currentProduct.Category, currentProduct.Description, &currentProduct.Price, &currentProduct.Quantity) != EOF) {
        if (strcmp(currentProduct.Name, productName) == 0) {
            productFound = 1;
            break;
        }
    }

    fclose(productsFile);

    if (!productFound) {
        printf("Product '%s' not found.\n", productName);
        return;
    }

    printf("Enter the quantity to add to cart: ");
    scanf("%d", &quantity);

    if (quantity > currentProduct.Quantity) {
        printf("Not enough quantity available. Available quantity: %d\n", currentProduct.Quantity);
        return;
    }

    FILE *cartFile;
    cartFile = fopen("cart.txt", "a");

    if (cartFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(cartFile, "%s %d %d\n", currentProduct.Name, currentProduct.Price, quantity);

    fclose(cartFile);

    printf("Product '%s' added to cart with quantity %d.\n", productName, quantity);
}

void YourCart() {
    FILE *cartFile;
    cartFile = fopen("cart.txt", "r");

    if (cartFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char productName[50];
    int price;
    int quantity;

    printf("Your Cart:\n");
    while (fscanf(cartFile, "%s %d %d\n", productName, &price, &quantity) != EOF) {
        printf("Name: %s, Price: %d, Quantity: %d\n", productName, price, quantity);
    }

    fclose(cartFile);
}

void UserShoppingCartCheckout() {
    FILE *cartFile;
    cartFile = fopen("cart.txt", "r");

    if (cartFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char productName[50];
    int price;
    int quantity;
    int totalAmount = 0;

    printf("Checkout:\n");
    while (fscanf(cartFile, "%s %d %d\n", productName, &price, &quantity) != EOF) {
        totalAmount += price * quantity;
        printf("Name: %s, Price: %d, Quantity: %d, Subtotal: %d\n", productName, price, quantity, price * quantity);
    }

    fclose(cartFile);

    printf("Total Amount: %d\n", totalAmount);
    printf("Checkout successful!\n");

    cartFile = fopen("cart.txt", "w");
    fclose(cartFile);
}
