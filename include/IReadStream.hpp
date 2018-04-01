#pragma once
#include <future>
#include <functional>

template<typename Derived, typename TStream>
class IReadStream
{
public:
    IReadStream() = default;
    virtual ~IReadStream() = default;
    std::future<const TStream*> get() const{
        return std::move(std::async(std::launch::async, [this] {
            return static_cast<const TStream*>(static_cast<const Derived*>(this)->getStream());
        }));
    }
};
