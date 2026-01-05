/**
 * @file Request.cpp
 * @brief Implementation of the Request class.
 *
 * This file implements the Request class, which represents
 * a single client request handled by the load balancer.
 */

#include "Request.h"
#include <string>

/**
 * @class Request
 * @brief Represents a single request entering the load balancer.
 *
 * Each request includes source and destination IP addresses,
 * a processing time measured in clock cycles, a job type
 * (streaming or processing), and an arrival timestamp.
 */

/**
 * @brief Constructs a Request object.
 *
 * Represents a single client request entering the load balancer.
 * Each request contains source and destination IP addresses,
 * a processing time measured in clock cycles, and a job type
 * (streaming or processing).
 *
 * @param ipIn Source IP address of the request.
 * @param ipOut Destination IP address of the request.
 * @param isStreaming True if the request is a streaming job.
 * @param processingTime Number of clock cycles required to process the request.
 * @param arrivalTime Clock cycle when the request arrived.
 */
Request::Request(const std::string& ipIn,
                 const std::string& ipOut,
                 bool isStreaming,
                 int processingTime,
                 int arrivalTime)
    : ipIn(ipIn),
      ipOut(ipOut),
      processingTime(processingTime),
      isStreaming(isStreaming),
      arrivalTime(arrivalTime)
{
}

/**
 * @brief Gets the processing time of the request.
 *
 * @return Number of clock cycles required to complete the request.
 */
int Request::getProcessingTime() const {
    return processingTime;
}

/**
 * @brief Gets the source IP address of the request.
 *
 * @return Source IP address as a string.
 */
std::string Request::getIpIn() const {
    return ipIn;
}

/**
 * @brief Gets the destination IP address of the request.
 *
 * @return Destination IP address as a string.
 */
std::string Request::getIpOut() const {
    return ipOut;
}
