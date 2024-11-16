# E-commerce Platform with a Recommendation System

### Objective: 
- To understand C programming language and its various applications. To also explore C's customizability and flexibility.
- To leverage data structures and algorithms for efficient data processing and storage.

## Compilation

```bash
gcc -o main main.c
./main 
```

## Features
- Supports User Registration and Login
- Supports Product Information as Inventory Catalogue. Products can be added too.
- Browsing and Purchase History can be tracked
- Recommendation Engine to suggest personalized recommendations
---

## Code Flow

### Main Functions

1. **`main()`**:
   - Initializes the hash table.
   - Starts the main menu loop.

2. **`mainMenu()`**:
   - Provides an interactive menu to navigate features like login, viewing products, and managing history.

3. **User Functions**:
   - `addUser()`: Adds a new user to the hash table.
   - `getUserByID()`: Retrieves a user by their userID.
   - `userLogin()`: Validates user credentials and logs in the user.

4. **Product Functions**:
   - `addProduct()`: Adds a new product to the hash table.
   - `getProductByName()`: Retrieves a product by name.
   - `displayProductsByCategory()`: Displays products in a specified category.

5. **History Management**:
   - `recordBrowsingHistory()`: Adds a product to the user's browsing history.
   - `recordPurchaseHistory()`: Adds a product to the user's purchase history.

6. **Recommendation Engine**
    - Products are linked using `addProductRelationship()` and the `generateRecommendations()` function integrates these strategies to create a ranked list of recommended products for each user

---

## How It Works

### 1. **Initialization**
- The program initializes a hash tables `USER_TABLE_SIZE` and `PRODUCT_TABLE_SIZE` to store user and product data.
- The `initHashTable()` function sets up the data structure.

### 2. **Adding Users and Products and Login System**
- The `addUser()` and `addProduct()` functions allow adding users and products to the hash table
- Users and Products are stored in the `users` array of the hash table and `products` array with `ProductNode` structures respectively.
- The Login System checks if the user is registered in the platform.

### 4. **Product Browsing**
- Users can search for products by name or category using the `displayProduct()` and `displayProductsByCategory()` functions.

### 5. **Activity Tracking**
- **Browsing History**: The program records products viewed by a user in their `browsingHistory` list.
- **Purchase History**: The program records purchased products in the user's `purchaseHistory` list.

### 6. **Recommendation Engine**
- Suggests products based on the user's purchase history.

### 7. **Main Menu**
The `mainMenu()` function provides a command-line interface which includes a catalogue of options for the users to choose from.

---
