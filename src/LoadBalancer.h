#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include <string>
#include "Request.h"
#include "WebServer.h"
#include <fstream>

/**
 * @class LoadBalancer
 * @brief Simulates a dynamic load balancer for web servers.
 *
 * The LoadBalancer distributes incoming requests across a pool
 * of web servers, dynamically scaling the number of servers
 * based on request queue size. It also blocks requests from
 * restricted IP ranges and logs system state over time.
 */
class LoadBalancer {
private:
    /** Queue of incoming requests awaiting processing */
    std::queue<Request> requestQueue;

    /** Collection of active web servers */
    std::vector<WebServer> webServers;

    /** Current simulation clock cycle */
    int currentClockCycle;

    /** Total number of cycles the simulation will run */
    int runningTime;

    /** Initial number of web servers at startup */
    int initialNumServers;

    /** Cooldown counter to prevent rapid scaling */
    int scaleCooldown;

    /** Number of cycles to wait between scaling events */
    const int SCALE_WAIT = 3;

    /** Total number of successfully processed requests */
    int totalRequestsProcessed;

    /** Total number of blocked requests */
    int blockedRequests;

    /**
     * @brief Populates the request queue with initial requests.
     *
     * The initial number of requests is proportional to the
     * number of web servers.
     *
     * @param numOfServers Initial number of web servers.
     */
    void populateReqQueue(int numOfServers);

    /**
     * @brief Creates and initializes web servers.
     *
     * @param numOfServers Number of web servers to create.
     */
    void createWebServers(int numOfServers);

    /**
     * @brief Dynamically scales the number of web servers.
     *
     * Adds or removes servers based on queue size thresholds
     * and enforces a cooldown between scaling events.
     */
    void scaleServers();

    /**
     * @brief Checks whether an IP address is blocked.
     *
     * @param ip IP address to check.
     * @return true if the IP is blocked, false otherwise.
     */
    bool isBlockedIP(const std::string& ip);

    /** Log file for recording simulation state */
    std::ofstream logFile;

    /**
     * @brief Logs the current system state to the log file.
     */
    void logState();

    /**
     * @brief Prints a summary of the system state to stdout.
     */
    void printSummary();

public:
    /**
     * @brief Constructs a LoadBalancer instance.
     *
     * Initializes web servers, populates the request queue,
     * and prepares logging.
     *
     * @param numServers Initial number of web servers.
     * @param runTime Number of clock cycles to simulate.
     */
    LoadBalancer(int numServers, int runTime);

    /**
     * @brief Generates a random IPv4 address.
     *
     * @return Random IP address as a string.
     */
    std::string generate_IP();

    /**
     * @brief Generates a random request.
     *
     * @return A randomly generated Request object.
     */
    Request genRandReq();

    /**
     * @brief Runs the load balancer simulation.
     *
     * Advances the simulation clock, assigns requests,
     * scales servers dynamically, and logs state.
     */
    void Run();
};

#endif
