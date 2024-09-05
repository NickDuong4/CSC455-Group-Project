//productManagement.cpp

#include "header.h"
#include <regex>
#include <fstream>
#include <iostream>

// Function to check if a string represents a valid product ID
bool isValidProductID(const std::string& productID, const std::vector<Product>& products)
{
    // Check if it starts with 'Prod' and is followed by a five-digit number
    if (productID.length() != 9 || productID.substr(0, 4) != "Prod" || !std::regex_match(productID.substr(4), std::regex("^[0-9]{5}$")))
    {
        return false;
    }

    // Check if it's unique
    for (const Product& product : products) 
    {
        if (product.productID == productID) 
        {
            return false;
        }
    }

    return true;
}

// Function to add a new product
void addProduct(std::vector<Product>& products)
{
    Product newProduct;
    std::cout << "Enter product ID (e.g., 'Prod00001'): ";
    std::cin >> newProduct.productID;

    if (!isValidProductID(newProduct.productID, products))
    {
        std::cout << "Invalid product ID. It must start with 'Prod' followed by a five-digit number, and it must be unique." << std::endl;
        return;
    }

    std::cout << "Enter product name: ";
    std::cin >> newProduct.productName;

    std::cout << "Enter product price: ";
    std::cin >> newProduct.productPrice;

    std::cout << "Enter the number of available items: ";
    std::cin >> newProduct.availableItems;

    if (newProduct.availableItems <= 0)
    {
        std::cout << "Invalid number of available items. It must be a positive number." << std::endl;
        return;
    }

    products.push_back(newProduct);

    std::cout << "Product added to inventory." << std::endl;
}

// Function to remove product
void removeProduct(std::vector<Product>& products, const std::string& productID) 
{
    for (auto it = products.begin(); it != products.end(); ++it) 
    {
        if (it->productID == productID)
        {
            products.erase(it);
            std::cout << "Product removed from inventory." << std::endl;
            return;
        }
            
        else
        {
            std::cout << "Product with ID " << productID << " not found." << std::endl;
        }
    }
}

//Function list products
void listProducts(const std::vector<Product>& products) 
{
    std::cout << "List of Products in Inventory:\n";
    for (const Product& product : products) 
    {
        std::cout << "Product ID: " << product.productID << std::endl;
        std::cout << "Product Name: " << product.productName << std::endl;
        std::cout << "Product Price: $" << product.productPrice << std::endl;
        std::cout << "Available Items: " << product.availableItems << std::endl;
        std::cout << "--------------------------\n";
    }
}

//Function save product
void saveProductData(const std::vector<Product>& products)
{
    std::ofstream productsFile("products.txt");
    if (productsFile.is_open())
    {
        for (const Product& product : products)
        {
            productsFile << product.productID << "\n"
                         << product.productName << "\n"
                         << product.productPrice << "\n"
                         << product.availableItems << "\n\n";
        }
        productsFile.close();
        std::cout << "Product data saved to 'products.txt'." << std::endl;
    } 

    else 
    {
        std::cerr << "Failed to open 'products.txt'" << std::endl;
    }
}

// Function to calculate the total reward points based on the total amount
int calculateRewardPoints(double totalAmount)
{
    //1 reward point for every $10 spent
    return static_cast<int>(totalAmount / 10);
}

// Function to record a transaction
void recordTransaction(const std::string& transactionID, const Customer& customer, const std::vector<Product>& purchasedProducts)
{
    std::ofstream transactionsFile("transactions.txt", std::ios::app);

    if (!transactionsFile.is_open())
    {
        std::cerr << "Error: Failed to open 'transactions.txt' for recording the transaction." << std::endl;
        return;
    }

    // Write the transaction data to the file
    transactionsFile << "Transaction ID: " << transactionID << "\n"
                     << "User ID: " << customer.userID << "\n";

    // Write product IDs
    transactionsFile << "Product IDs: ";
    for (const Product& product : purchasedProducts)
    {
        transactionsFile << product.productID << ", ";
    }
    transactionsFile << "\n";

    // Calculate and write the total amount
    double totalAmount = 0.0;
    for (const Product& product : purchasedProducts)
    {
        totalAmount += product.productPrice;
    }
    transactionsFile << "Total amount: $" << totalAmount << "\n";

    // Calculate and write the total reward points
    int totalRewardPoints = calculateRewardPoints(totalAmount);
    transactionsFile << "Total reward points: " << totalRewardPoints << "\n";

    transactionsFile << "--------------------------\n";

    transactionsFile.close();
    std::cout << "Transaction recorded." << std::endl;
}

// Function to make a purchase
void makePurchase(std::vector<Product>& products, Customer& customer) {
    std::vector<Product> shoppingCart;
    double totalAmount = 0.0;

    // Display available products
    listProducts(products);

    // Allow the user to add products to the shopping cart
    while (true) {
        std::string productID;
        std::cout << "Enter the product ID to add to your cart (or type 'done' to finish): ";
        std::cin >> productID;

        if (productID == "done") {
            break;
        }

        // Validate product ID
        if (!isValidProductID(productID, products)) {
            std::cout << "Invalid product ID. Please enter a valid ID." << std::endl;
            continue;
        }

        // Find the product in the inventory
        auto productIt = std::find_if(products.begin(), products.end(), [productID](const Product& p) { return p.productID == productID; });

        if (productIt != products.end() && productIt->availableItems > 0) {
            // Add the product to the shopping cart
            shoppingCart.push_back(*productIt);
            totalAmount += productIt->productPrice;
            // Reduce the available items in the inventory
            productIt->availableItems--;
        } else {
            std::cout << "Product not found or out of stock. Please choose another product." << std::endl;
        }
    }

    // Calculate reward points based on the total amount
    int rewardPoints = calculateRewardPoints(totalAmount);

    // Display the total amount and reward points
    std::cout << "Total Amount: $" << totalAmount << std::endl;
    std::cout << "Earned Reward Points: " << rewardPoints << std::endl;

    // Record the transaction
    std::string transactionID = "T" + std::to_string(time(0));
    recordTransaction(transactionID, customer, shoppingCart);

    // Update customer's reward points
    customer.rewardPoints += rewardPoints;

    std::cout << "Purchase successful! Transaction ID: " << transactionID << std::endl;
}

// Function to handle shopping
void shopping(std::vector<Product>& products, std::vector<Customer>& customers) {
    // Get user ID
    std::string userID;
    std::cout << "Enter your user ID: ";
    std::cin >> userID;

    auto customerIt = std::find_if(customers.begin(), customers.end(),
                                   [userID](const Customer& c) { return c.userID == userID; });

    if (customerIt != customers.end()) {
        // Perform the shopping
        makePurchase(products, *customerIt);
    } else {
        std::cout << "User with ID " << userID << " not found." << std::endl;
    }
}
