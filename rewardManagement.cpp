//rewardManagement.cpp

#include "header.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>  //for std::find_if

void RewardSystem::setPointsPerAmount(int points) {
    pointsPerAmount = points;
}

void RewardSystem::addGift(int pointsRequired, const std::string& giftName) {
    gifts.push_back(std::make_pair(pointsRequired, giftName));
}

void RewardSystem::displayGifts() const {
    std::cout << "Available gifts:" << std::endl;
    for (const auto& gift : gifts) {
        std::cout << "Points required: " << gift.first << ", Gift: " << gift.second << std::endl;
    }
}

std::string RewardSystem::redeemGift(int totalPoints) const {
    for (const auto& gift : gifts) {
        if (totalPoints >= gift.first) {
            return gift.second;
        } else {
            continue; // Continue the loop to check the next gift
        }
    }
    return "No gift available for the given points.";
}

void redeemRewards(std::vector<Customer>& customers, const RewardSystem& rewardSystem) {
    std::string userID;
    int pointsToRedeem;

    std::cout << "Enter your user ID: ";
    std::cin >> userID;

    auto customerIterator = std::find_if(customers.begin(), customers.end(),
                                        [userID](const Customer& c) { return c.userID == userID; });

    if (customerIterator != customers.end()) {
        std::cout << "Available reward points: " << customerIterator->rewardPoints << std::endl;
        std::cout << "Enter the number of reward points to redeem: ";
        std::cin >> pointsToRedeem;

        if (pointsToRedeem > 0 && pointsToRedeem <= customerIterator->rewardPoints) {
            // Deduct the reward points
            customerIterator->rewardPoints -= pointsToRedeem;

            // Use the redeemGift function to get the gift based on the redeemed points
            std::string redeemedGift = rewardSystem.redeemGift(pointsToRedeem);

            // Display the redeemed gift
            std::cout << "Redemption successful! Enjoy your reward: " << redeemedGift << std::endl;
        } else {
            std::cout << "Invalid number of reward points. Please enter a valid amount." << std::endl;
        }
    } else {
        std::cout << "User with ID " << userID << " not found." << std::endl;
    }
}
