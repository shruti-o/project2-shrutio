#include "WebServer.h"

/**
 * @brief Constructs a WebServer with a unique server ID.
 *
 * The server is initialized in an available (idle) state with
 * no active request and zero remaining processing time.
 *
 * @param id Unique identifier for the web server.
 */
WebServer::WebServer(int id)
    : serverID(id),
      isAvailable(true),
      currentRequest("", "", false, 0, 0),
      timeRemaining(0)
{
}

/**
 * @brief Checks whether the web server is currently available.
 *
 * @return true if the server is idle and can accept a request,
 *         false if it is currently processing a request.
 */
bool WebServer::isNotActive() const {
    return isAvailable;
}

/**
 * @brief Assigns a request to the web server for processing.
 *
 * The server becomes unavailable until the request has completed.
 * The remaining processing time is initialized based on the request.
 *
 * @param request The Request object to be processed.
 */
void WebServer::processRequest(const Request& request) {
    currentRequest = request;
    timeRemaining = request.getProcessingTime();
    isAvailable = false;
}

/**
 * @brief Advances request processing by one clock cycle.
 *
 * Decrements the remaining processing time if the server is busy.
 * When processing completes, the server becomes available again.
 */
void WebServer::handleRequest() {
    if (!isAvailable && timeRemaining > 0) {
        timeRemaining--;

        if (timeRemaining == 0) {
            isAvailable = true;
        }
    }
}

/**
 * @brief Returns the request currently being processed.
 *
 * @return The active Request object.
 */
Request WebServer::getCurrentRequest() const {
    return currentRequest;
}

/**
 * @brief Gets the remaining processing time for the current request.
 *
 * @return Number of clock cycles remaining.
 */
int WebServer::getTimeRemaining() const {
    return timeRemaining;
}
