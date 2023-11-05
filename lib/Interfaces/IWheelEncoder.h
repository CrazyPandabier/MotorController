#pragma once
#include <cstdint>

class IWheelEncoder
{
public:
    virtual ~IWheelEncoder() = default;
    /**
     * @brief           Get count of wheel encoder
     */
    virtual uint32_t GetCount() = 0;
};