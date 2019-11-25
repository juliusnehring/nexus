#include "test.hh"

#include <nexus/tests/Test.hh>

#include <clean-core/unique_ptr.hh>
#include <clean-core/vector.hh>

using namespace nx;

cc::vector<cc::unique_ptr<Test>>& nx::detail::get_all_tests()
{
    static cc::vector<cc::unique_ptr<Test>> all_tests;
    return all_tests;
}

void nx::detail::configure(Test* t, before const& v) { t->addBeforePattern(v.pattern); }

void nx::detail::configure(Test* t, after const& v) { t->addAfterPattern(v.pattern); }

void nx::detail::configure(Test* t, exclusive_t const&) { t->setExclusive(); }

void nx::detail::configure(Test* t, should_fail_t const&) { t->setShouldFail(); }

Test* detail::register_test(const char* name, const char* file, int line, char const* fun_name, test_fun_t fun)
{
    auto t = cc::make_unique<Test>(name, file, line, fun_name, fun);
    auto t_ptr = t.get();
    get_all_tests().push_back(std::move(t));
    return t_ptr;
}
