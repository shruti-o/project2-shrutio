#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @brief Represents a single web server in the load balancer system.
 *
 * A WebServer processes one request at a time. It tracks availability,
 * remaining processing time, and the current request being handled.
 */
class WebServer {
private:
    int serverID;
    bool isAvailable;
    Request currentRequest;
    int timeRemaining;

public:
    /**
     * @brief Constructs a WebServer with a given ID.
     *
     * @param id Unique identifier for the server
     */
    WebServer(int serverID);

    /**
     * @brief Checks whether the server is available.
     *
     * @return true if the server is idle
     */
    bool isNotActive() const;

    /**
     * @brief Assigns a request to the server for processing.
     *
     * @param request The request to process
     */
    void processRequest(const Request& request);

    /**
     * @brief Processes one clock cycle.
     *
     * Decrements remaining processing time and frees the server
     * when the request finishes.
     */
    void handleRequest();

    /**
     * @brief Returns the request currently being processed.
     *
     * @return The active Request
     */
    Request getCurrentRequest() const;

    /**
     * @brief Returns remaining processing time.
     *
     * @return Time remaining in clock cycles
     */
    int getTimeRemaining() const;
};

#endif // WEBSERVER_H
