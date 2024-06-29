#include <stdio.h>
#include <string.h>

// Parameters
#define max_users 100
#define max_name_len 50
#define max_userid_len 20
#define max_psw_len 20
#define max_email_len 50
#define max_addr_len 50
#define max_mobile_len 20

#define max_products 100
#define max_prodname_len 50
#define max_cat_len 20
#define max_desc_len 50
#define max_quan_len 50
#define max_price_len 20
#define max_cart_items 25

// Global Variables/Arrays
char UserName[max_users][max_name_len];
char UserID[max_users][max_userid_len];
char UserPassword[max_users][max_psw_len];
char UserMobile[max_users][max_mobile_len];
char UserEmail[max_users][max_email_len];
char UserAddress[max_users][max_addr_len];
int UserCount = 0;

char ProductName[max_products][max_prodname_len];
char ProductCategory[max_products][max_cat_len];
float ProductPrice[max_products];
char ProductDescription[max_products][max_desc_len];
float ProductQuantity[max_products];
int ProductCount = 0;

char CartItems[max_cart_items][max_prodname_len];
float PriceItems[max_cart_items];
float QuantityItems[max_cart_items];
float TotalCart[max_cart_items];

// Function Prototypes
void UserRegistration();
int UserLogin();

void AddProduct();
void UpdateProduct();
void DeleteProduct();

void CategoryProduct();
void AvailabilityProduct();
void UserShoppingCart();
void DisplayAll();
void UserShoppingCartCheckout();
void YourCart();
void SearchItem();

// Main
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
                printf("Invalid Entry\n");
                break;
        }
    }

    return 0;
}

// MODULE 1 FUNCTIONS

void UserRegistration() {
    if (UserCount >= max_users) {
        printf("Maximum users reached. Cannot register more users.\n");
        return;
    }
    else {
        printf("Enter Name: ");
        scanf("%s", UserName[UserCount]);

        printf("Enter Email: ");
        scanf("%s", UserEmail[UserCount]);

        printf("Enter Mobile no: ");
        scanf("%s", UserMobile[UserCount]);

        printf("Enter UserID: ");
        scanf("%s", UserID[UserCount]);

        printf("Enter Password: ");
        scanf("%s", UserPassword[UserCount]);

        printf("Enter Address: ");
        scanf("%s", UserAddress[UserCount]);

        printf("User registered successfully!\n");
        UserCount++;
    }
}

int UserLogin() {
    char login_uname[max_userid_len];
    char login_psw[max_psw_len];
    printf("Enter your User ID: ");
    scanf("%s", login_uname);
    printf("Enter your Password: ");
    scanf("%s", login_psw);
    int login = 0;
    for (int i = 0; i < UserCount; i++) {
        if (strcmp(login_uname, UserID[i]) == 0 && strcmp(login_psw, UserPassword[i]) == 0) {
            login = 1;
        }
    }
    if (login == 1) {
        printf("Welcome!! You are logged in as %s\n", login_uname);
        return 1;
    } else {
        printf("Wrong User ID or PIN entered\n");
        return 0;
    }
}

// MODULE 2 FUNCTIONS

void AddProduct() {
    if (ProductCount >= max_products) {
        printf("Maximum products reached. Cannot add more products.\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf("%s", ProductName[ProductCount]);

    printf("Enter Category: ");
    scanf("%s", ProductCategory[ProductCount]);

    printf("Enter Product Description: ");
    scanf("%s", ProductDescription[ProductCount]);

    printf("Enter Product Price: ");
    scanf("%f", &ProductPrice[ProductCount]);

    printf("Enter Product Quantity: ");
    scanf("%f", &ProductQuantity[ProductCount]);

    printf("Product registered successfully and Product ID is %d !\n", ProductCount);
    ProductCount++;
}

void UpdateProduct() {
    char prod_upd[max_prodname_len];
    printf("Enter the product to be updated: ");
    scanf("%s", prod_upd);
    for (int i = 0; i < ProductCount; i++) {
        if (strcmp(ProductName[i], prod_upd) == 0) {
            printf(">>> New product details <<<\n");
            printf("Enter Product Name: ");
            scanf("%s", ProductName[i]);
            printf("Enter Category: ");
            scanf("%s", ProductCategory[i]);
            printf("Enter Product Description: ");
            scanf("%s", ProductDescription[i]);
            printf("Enter Product Price: ");
            scanf("%f", &ProductPrice[i]);
            printf("Product was updated successfully!!\n");
            return;
        }
    }
    printf("Product Not Found!!\n");
}

void DeleteProduct() {
    char prod_del[max_prodname_len];
    printf("Enter the product to be deleted: ");
    scanf("%s", prod_del);
    for (int j = 0; j < ProductCount; j++) {
        if (strcmp(ProductName[j], prod_del) == 0) {
            for (int i = j; i < ProductCount - 1; i++) {
                strcpy(ProductName[i], ProductName[i + 1]);
                strcpy(ProductCategory[i], ProductCategory[i + 1]);
                strcpy(ProductDescription[i], ProductDescription[i + 1]);
                ProductPrice[i] = ProductPrice[i + 1];
                ProductQuantity[i] = ProductQuantity[i + 1];
            }
            ProductCount--;
            printf("Product deleted successfully!\n");
            return;
        }
    }
    printf("Product Not Found!!\n");
}

void CategoryProduct() {
    char prod_cat[max_cat_len];
    printf("Enter the category type: ");
    scanf("%s", prod_cat);
    int count = 0;
    for (int i = 0; i < ProductCount; i++) {
        if (strcmp(ProductCategory[i], prod_cat) == 0) {
            printf("%d. %s\n", count + 1, ProductName[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("Category Not Found!!\n");
    }
}

void AvailabilityProduct() {
    char prod_aval[max_cat_len];
    printf("Enter the product name to check for availability: ");
    scanf("%s", prod_aval);
    for (int i = 0; i < ProductCount; i++) {
        if (strcmp(ProductName[i], prod_aval) == 0) {
            if (ProductQuantity[i] > 0) {
                printf("%s is Available\n", ProductName[i]);
            } else {
                printf("%s is not Available\n", ProductName[i]);
            }
            return;
        }
    }
    printf("Product Not Found!!\n");
}

void UserShoppingCart() {
    int e, f;
    printf(">>>> OPTIONS <<<<\n");
    printf("1. Product Catalogue\n");
    printf("2. Your Cart\n");
    printf("3. Shopping Cart Checkout\n");
    printf("4. Back\n");
    printf("Enter your choice(1/2/3/4): ");
    scanf("%d", &e);
    printf("====================================================================\n");
    switch (e) {
        case 1:
            printf("Option 1: Product Catalogue\n");
            printf(">>>> OPTIONS <<<<\n");
            printf("1. All Products\n");
            printf("2. Category Based\n");
            printf("3. Search Item\n");
            printf("4. Check Availability\n");
            printf("5. Back\n");
            printf("Enter your choice(1/2/3/4/5): ");
            scanf("%d", &f);
            printf("====================================================================\n");
            switch (f) {
                case 1:
                    printf("1. All Products\n");
                    DisplayAll();
                    break;
                case 2:
                    printf("2. Category Based\n");
                    CategoryProduct();
                    break;
                case 3:
                    printf("3. Search Item\n");
                    SearchItem();
                    break;
                case 4:
                    printf("4. Check Availability\n");
                    AvailabilityProduct();
                    break;
                case 5:
                    break;
                default:
                    printf("Invalid option\n");
                    break;
            }
            break;
        case 2:
            printf("Option 2: Your Cart\n");
            YourCart();
            break;
        case 3:
            printf("Option 3: Shopping Cart Checkout\n");
            UserShoppingCartCheckout();
            break;
        case 4:
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

void SearchItem() {
    char search_item[max_prodname_len];
    printf("Enter the product to be searched: ");
    scanf("%s", search_item);
    for (int i = 0; i < ProductCount; i++) {
        if (strcmp(ProductName[i], search_item) == 0) {
            printf("Product Name: %s\n", ProductName[i]);
            printf("Category: %s\n", ProductCategory[i]);
            printf("Description: %s\n", ProductDescription[i]);
            printf("Price: %.2f\n", ProductPrice[i]);
            printf("Quantity: %.0f\n", ProductQuantity[i]);
            printf("--------------------------------------------------------------\n");
            return;
        }
    }
    printf("Product Not Found!!\n");
}

void DisplayAll() {
    printf(">>>> DISPLAYING ALL PRODUCTS <<<<\n");
    for (int i = 0; i < ProductCount; i++) {
        printf("Product %d\n", i + 1);
        printf("Name: %s\n", ProductName[i]);
        printf("Category: %s\n", ProductCategory[i]);
        printf("Description: %s\n", ProductDescription[i]);
        printf("Price: %.2f\n", ProductPrice[i]);
        printf("Quantity: %.0f\n", ProductQuantity[i]);
        printf("--------------------------------------------------------------\n");
    }
}

void YourCart() {
    char ProductNameItem[max_prodname_len];
    float quantity;
    int choice;

    printf(">>>> YOUR CART <<<<\n");

    printf("Enter the product name: ");
    scanf("%s", ProductNameItem);

    printf("Enter the quantity required: ");
    scanf("%f", &quantity);

    int ProductIndex = -1;
    for (int i = 0; i < ProductCount; i++) {
        if (strcmp(ProductName[i], ProductNameItem) == 0) {
            ProductIndex = i;
            break;
        }
    }

    if (ProductIndex == -1) {
        printf("Product not found in the catalogue.\n");
        return;
    }

    if (quantity > ProductQuantity[ProductIndex]) {
        printf("Sorry, the required quantity is not available.\n");
        return;
    }

    strcpy(CartItems[ProductCount], ProductNameItem);
    PriceItems[ProductCount] = ProductPrice[ProductIndex];
    QuantityItems[ProductCount] = quantity;
    TotalCart[ProductCount] = ProductPrice[ProductIndex] * quantity;

    printf("Product added to your cart.\n");

    printf("Do you want to view all products in your cart? (1 for Yes / 0 for No): ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf(">>>> PRODUCTS IN YOUR CART <<<<\n");
        for (int i = 0; i < ProductCount; i++) {
            printf("Item %d: %s, Price: %.2f, Quantity: %.2f, Total: %.2f\n", i + 1, CartItems[i+1], PriceItems[i+1], QuantityItems[i+1], TotalCart[i+1]);
        }
    }
}

void UserShoppingCartCheckout() {
    printf(">>>> SHOPPING CART CHECKOUT <<<<\n");
    float TotalAmount = 0.0;
    if (ProductCount == 0) {
        printf("Your cart is empty. No items to checkout.\n");
        return;
    }

    printf("Items in your cart:\n");
    for (int i = 0; i < ProductCount; i++) {
        printf("Item %d: %s, Price: %.2f, Quantity: %.0f\n", i + 1, CartItems[i+1], PriceItems[i+1], QuantityItems[i+1]);
        TotalAmount += TotalCart[i+1];
    }
    printf("Total Amount: %.2f\n", TotalAmount);
}
