#include <iostream>
#include "LoadBalancer.h"

/**
 * @brief Entry point for the load balancer simulation.
 *
 * Prompts the user for simulation parameters, initializes
 * the load balancer, and runs the simulation for the
 * specified number of clock cycles.
 *
 * @return Exit status of the program.
 */
int main() {
    int numServers;
    int runTime;

    std::cout << "Enter initial number of web servers: ";
    std::cin >> numServers;

    while (numServers < 1) {
        std::cout << "Number of servers must be at least 1. Try again: ";
        std::cin >> numServers;
    }

    std::cout << "Enter number of clock cycles to run the load balancer: ";
    std::cin >> runTime;

    while (runTime < 1) {
        std::cout << "Runtime must be at least 1. Try again: ";
        std::cin >> runTime;
    }

    std::cout << "\nStarting load balancer...\n\n";

    LoadBalancer lb(numServers, runTime);
    lb.Run();

    std::cout << "\nLoad Balancer completed.\n";

    return 0;
}
