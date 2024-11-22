#include "snowflake.h"
#include <chrono>
#include <stdexcept>

// Constructor
Snowflake::Snowflake(int64_t datacenterId, int64_t workerId)
    : datacenterId(datacenterId), workerId(workerId), sequence(0), lastTimestamp(-1)
{
    if (datacenterId > maxDatacenterId || datacenterId < 0)
    {
        throw std::invalid_argument("Datacenter ID out of range");
    }
    if (workerId > maxWorkerId || workerId < 0)
    {
        throw std::invalid_argument("Worker ID out of range");
    }
}

// Get the current time in milliseconds
int64_t Snowflake::currentTimeMillis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

// Block until the next millisecond
int64_t Snowflake::waitUntilNextMillis(int64_t lastTimestamp)
{
    int64_t timestamp = currentTimeMillis();
    while (timestamp <= lastTimestamp)
    {
        timestamp = currentTimeMillis();
    }
    return timestamp;
}

// Generate the next unique ID
int64_t Snowflake::nextId()
{
    std::lock_guard<std::mutex> lock(mutex);

    int64_t timestamp = currentTimeMillis();

    if (timestamp < lastTimestamp)
    {
        throw std::runtime_error("Clock moved backwards. Refusing to generate ID.");
    }

    if (timestamp == lastTimestamp)
    {
        sequence = (sequence + 1) & sequenceMask;
        if (sequence == 0)
        {
            timestamp = waitUntilNextMillis(lastTimestamp);
        }
    }
    else
    {
        sequence = 0;
    }

    lastTimestamp = timestamp;

    return ((timestamp - epoch) << timestampShift) |
           (datacenterId << datacenterIdShift) |
           (workerId << workerIdShift) |
           sequence;
}
