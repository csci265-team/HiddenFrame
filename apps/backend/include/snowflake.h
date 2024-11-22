#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <mutex>
#include <cstdint>
#include <stdexcept>

class Snowflake
{
private:
    // Constants
    static constexpr int64_t epoch = 1726012800000; // Epoch of HiddenFrame
    static constexpr int64_t datacenterIdBits = 5;
    static constexpr int64_t workerIdBits = 5;
    static constexpr int64_t sequenceBits = 12;

    static constexpr int64_t maxDatacenterId = (1 << datacenterIdBits) - 1;
    static constexpr int64_t maxWorkerId = (1 << workerIdBits) - 1;
    static constexpr int64_t sequenceMask = (1 << sequenceBits) - 1;

    static constexpr int64_t workerIdShift = sequenceBits;
    static constexpr int64_t datacenterIdShift = sequenceBits + workerIdBits;
    static constexpr int64_t timestampShift = sequenceBits + workerIdBits + datacenterIdBits;

    // Variables
    int64_t datacenterId;
    int64_t workerId;
    int64_t sequence;
    int64_t lastTimestamp;
    std::mutex mutex;

    // Private helper functions
    int64_t currentTimeMillis();
    int64_t waitUntilNextMillis(int64_t lastTimestamp);

public:
    // Constructor
    Snowflake(int64_t datacenterId, int64_t workerId);

    // Generate the next unique ID
    int64_t nextId();
};

#endif // SNOWFLAKE_H
