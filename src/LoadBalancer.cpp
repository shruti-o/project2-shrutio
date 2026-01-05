/**
 * @file LoadBalancer.cpp
 * @brief Implementation of a dynamic load balancer simulation for web servers.
 *
 * This file defines the LoadBalancer class, which manages multiple WebServer instances,
 * processes incoming Request objects, dynamically scales the number of servers based
 * on queue size, and logs the simulation state.
 */

#include "LoadBalancer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

/**
 * @brief Constructs a LoadBalancer with the specified number of servers and runtime.
 *
 * Initializes random seed, creates the initial web servers, populates the request queue,
 * and opens a log file for recording simulation events.
 *
 * @param numServers Initial number of web servers.
 * @param runTime Number of clock cycles to run the simulation.
 */
LoadBalancer::LoadBalancer(int numServers, int runTime)
    : currentClockCycle(0),
      runningTime(runTime),
      initialNumServers(numServers),
      scaleCooldown(0),
      totalRequestsProcessed(0),
      blockedRequests(0)
{
    std::srand(static_cast<unsigned>(time(nullptr)));
    createWebServers(numServers);
    populateReqQueue(numServers);

    logFile.open("loadbalancer.log");
    logFile << "Clock,Servers,QueueSize,Processed,Blocked\n";
}

/**
 * @brief Populates the request queue with an initial set of random requests.
 *
 * @param numOfServers Number of servers to determine the initial number of requests.
 */
void LoadBalancer::populateReqQueue(int numOfServers) {
    int initialRequests = numOfServers * 20;
    for (int i = 0; i < initialRequests; i++) {
        requestQueue.push(genRandReq());
    }
}

/**
 * @brief Creates the initial web servers and assigns each a unique server ID.
 *
 * @param numOfServers Number of servers to create.
 */
void LoadBalancer::createWebServers(int numOfServers) {
    for (int i = 0; i < numOfServers; i++) {
        webServers.emplace_back(i);
    }
}

/**
 * @brief Generates a random IPv4 address as a string.
 *
 * @return Random IP address in the format "x.x.x.x".
 */
std::string LoadBalancer::generate_IP() {
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
}

/**
 * @brief Generates a random request with a random IP, streaming flag, and processing time.
 *
 * @return Randomly generated Request object.
 */
Request LoadBalancer::genRandReq() {
    std::string ipIn = generate_IP();
    std::string ipOut = generate_IP();

    bool isStreaming = (rand() % 2 == 0);
    int processingTime = isStreaming ? (rand() % 4 + 10) : (rand() % 11 + 20);

    return Request(ipIn, ipOut, isStreaming, processingTime, currentClockCycle);
}

/**
 * @brief Checks if an IP address falls within a blocked range.
 *
 * @param ip IP address to check.
 * @return true if the IP is blocked, false otherwise.
 */
bool LoadBalancer::isBlockedIP(const std::string& ip) {
    return ip.rfind("192.", 0) == 0; // Example blocked range: 192.*.*.*
}

/**
 * @brief Dynamically scales the number of servers based on the queue size.
 *
 * If the queue is too large, a new server is added. If the queue is too small, a server
 * is removed, respecting a cooldown period to avoid frequent scaling.
 */
void LoadBalancer::scaleServers() {
    if (scaleCooldown > 0) {
        scaleCooldown--;
        return;
    }

    int queueSize = requestQueue.size();
    int numServers = webServers.size();

    if (queueSize > 25 * numServers) {
        webServers.emplace_back(numServers);
        scaleCooldown = SCALE_WAIT;
    } 
    else if (queueSize < 15 * numServers && numServers > 1) {
        webServers.pop_back();
        scaleCooldown = SCALE_WAIT;
    }
}

/**
 * @brief Runs the main simulation loop for the load balancer.
 *
 * Each cycle:
 * - Randomly adds new requests.
 * - Processes requests on active servers.
 * - Assigns queued requests to available servers.
 * - Scales servers up or down if necessary.
 * - Logs state to a file and prints summary every 50 cycles.
 */
void LoadBalancer::Run() {
    while (currentClockCycle < runningTime) {
        currentClockCycle++;

        if (rand() % 100 < 90) {
            Request req = genRandReq();
            if (!isBlockedIP(req.getIpIn())) {
                requestQueue.push(req);
            } else {
                blockedRequests++;
            }
        }

        for (auto& server : webServers) {
            server.handleRequest();
        }

        for (auto& server : webServers) {
            if (server.isNotActive() && !requestQueue.empty()) {
                Request req = requestQueue.front();
                requestQueue.pop();
                server.processRequest(req);
                totalRequestsProcessed++;
            }
        }

        scaleServers();
        logState();

        if (currentClockCycle % 50 == 0) {
            printSummary();
        }
    }

    std::cout << "\nSimulation complete\n";
    std::cout << "Initial Servers: " << initialNumServers << "\n";
    std::cout << "Final Servers: " << webServers.size() << "\n";
    std::cout << "Requests Processed: " << totalRequestsProcessed << "\n";
    std::cout << "Blocked Requests: " << blockedRequests << "\n";

    logFile << "Simulation complete\n";
    logFile << "Initial Servers: " << initialNumServers << "\n";
    logFile << "Final Servers: " << webServers.size() << "\n";
    logFile << "Requests Processed: " << totalRequestsProcessed << "\n";
    logFile << "Blocked Requests: " << blockedRequests << "\n";

    logFile.close();
}

/**
 * @brief Logs the current simulation state to the log file.
 */
void LoadBalancer::logState() {
    logFile << "[Cycle " << currentClockCycle << "] "
            << "Servers: " << webServers.size()
            << ", Queue: " << requestQueue.size()
            << ", Processed: " << totalRequestsProcessed
            << ", Blocked: " << blockedRequests
            << "\n";
}

/**
 * @brief Prints a summary of the current simulation state to the console.
 */
void LoadBalancer::printSummary() {
    std::cout << "[Cycle " << currentClockCycle << "] "
              << "Servers: " << webServers.size()
              << ", Queue: " << requestQueue.size()
              << ", Processed: " << totalRequestsProcessed
              << ", Blocked: " << blockedRequests
              << "\n";
}