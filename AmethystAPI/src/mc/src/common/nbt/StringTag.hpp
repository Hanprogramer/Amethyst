#pragma once
#include "mc/src/common/nbt/Tag.hpp"

class StringTag : public Tag {
public:
    std::string data;

    StringTag();
    StringTag(std::string);
    virtual void write(IDataOutput&) const;
    virtual void load(IDataInput&);
    virtual Type getId() const;
    virtual std::string toString() const;
    virtual std::unique_ptr<Tag> copy() const;
    virtual bool equals(const Tag&) const;
    virtual size_t hash() const;
};