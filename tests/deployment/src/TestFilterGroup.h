

#ifndef NGREST_TESTFILTERGROUP_H
#define NGREST_TESTFILTERGROUP_H

#include <ngrest/engine/FilterGroup.h>

namespace ngrest {

class TestFilterGroup: public FilterGroup
{
public:
    TestFilterGroup();
    ~TestFilterGroup();
    const std::string& getName() const override;
    const FiltersMap& getFilters() const override;

private:
    Filter* filter;
    FiltersMap filters;
};

}

#endif // NGREST_TESTFILTERGROUP_H
