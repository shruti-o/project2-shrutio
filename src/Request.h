#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @brief Represents a single request handled by the load balancer.
 *
 * A request contains source and destination IP addresses,
 * a processing time measured in clock cycles, and a job type
 * indicating whether the request is streaming or processing.
 */
class Request {
private:
    std::string ipIn;
    std::string ipOut;
    int processingTime;
    bool isStreaming;
    int arrivalTime;

public:
    /**
     * @brief Constructs a Request object.
     *
     * @param ipIn Source IP address
     * @param ipOut Destination IP address
     * @param processingTime Time required to process the request (clock cycles)
     * @param isStreaming True if type of request is streaming
     * @param arrivalTime Clock cycle when request was created
     */
    Request(const std::string& ipIn,
            const std::string& ipOut,
            bool isStreaming,
            int processingTime,
            int arrivalTime);

    /**
     * @brief Gets the processing time of the request.
     *
     * @return Number of clock cycles required to complete the request.
     */
    int getProcessingTime() const;

    /**
     * @brief Gets the source IP address of the request.
     *
     * @return Source IP address as a string.
     */
    std::string getIpIn() const;

    /**
     * @brief Gets the destination IP address of the request.
     *
     * @return Destination IP address as a string.
     */
    std::string getIpOut() const;

};

#endif // REQUEST_H
