/* Phuc Nguyen
Nicolas Duong
Sean Gascon */

//header.h
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>

struct Customer {
    std::string username;
    std::string firstName;
    std::string lastName;
    int age;
    std::string creditCardNumber;
    std::string userID;
    int rewardPoints;
};

struct Product
{
    std::string productID;
    std::string productName;
    double productPrice;
    int availableItems;
};

struct RewardSystem {
    int pointsPerAmount;
    std::vector<std::pair<int, std::string>> gifts;

    void setPointsPerAmount(int points);

    void addGift(int pointsRequired, const std::string& giftName);

    void displayGifts() const;

    std::string redeemGift(int totalPoints) const;

};

bool isUniqueCreditCard(const std::string& creditCardNumber, const std::vector<Customer>& customer);

bool validateCustomer(const Customer& customer, const std::vector<Customer>& existingCustomers);

void registerCustomer(std::vector<Customer>& customers);

void saveCustomerData(const std::vector<Customer>& customers);

bool isValidProductID(const std::string& productID, const std::vector<Product>& products);

void saveProductData(const std::vector<Product>& products);

void addProduct(std::vector<Product>& products);

void removeProduct(std::vector<Product>& products, const std::string& productID);

void listProducts(const std::vector<Product>& products);

int calculateRewardPoints(double totalAmount);

void recordTransaction(const Customer& customer, const std::vector<Product>& purchasedProducts);

void displayAllCustomers(const std::vector<Customer>& customers);

void removeCustomer(std::vector<Customer>& customers, const std::string& customerID);

void viewCustomerByID(const std::vector<Customer>& customers, const std::string& userID);

void makePurchase(std::vector<Product>& products, Customer& customer);

void shopping(std::vector<Product>& products, std::vector<Customer>& customers);

#endif
