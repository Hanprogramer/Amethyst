#pragma once
#include <memory>

class TaskGroup;

namespace Bedrock::Threading {
class EnableQueueForMainThread {
public:
    std::unique_ptr<TaskGroup> mQueueForMainThreadTaskGroup;
    virtual ~EnableQueueForMainThread() = default;
};
}