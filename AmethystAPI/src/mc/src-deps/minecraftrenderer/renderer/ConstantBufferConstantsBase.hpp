#pragma once

namespace mce {

class ConstantBufferConstantsBase {
public:
	void* constantBuffer;

	virtual ~ConstantBufferConstantsBase();
	virtual void init();

	bool isDirty() const;
};

}