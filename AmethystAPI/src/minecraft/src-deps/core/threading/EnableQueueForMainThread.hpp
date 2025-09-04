#pragma once
#include <memory>

class TaskGroup;

namespace Bedrock::Threading {
    class EnableQueueForThread {
    public:
        std::unique_ptr<TaskGroup> mQueueForMainThreadTaskGroup;
        virtual ~EnableQueueForThread() = default;
    };

    class EnableQueueForMainThread : public EnableQueueForThread {

    };
}