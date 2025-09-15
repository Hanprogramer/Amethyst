#pragma once
#include <memory>
#include <minecraft/src-deps/core/threading/TaskGroup.hpp>

namespace Bedrock::Threading {
    class EnableQueueForThread {
    public:
        std::unique_ptr<TaskGroup> mQueueForMainThreadTaskGroup;
        virtual ~EnableQueueForThread() = default;
    };

    class EnableQueueForMainThread : public EnableQueueForThread {

    };
}