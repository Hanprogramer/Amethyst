#pragma once

namespace mce {
class Camera;
class RenderContext;
class GlobalConstantBuffers;
};

namespace mce {
	#pragma pack(push, 1)
    class MeshContext {
    public:
        /* this + 0  */ mce::RenderContext& renderContext;
        /* this + 8  */ mce::Camera* camera;
		mce::GlobalConstantBuffers& constantBuffers;
    };
	#pragma pack(pop)
}