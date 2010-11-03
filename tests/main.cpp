#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextTestRunner.h>

int main(int argc, char* argv[])
{
    using CppUnit::TestFactoryRegistry;
    CppUnit::TextTestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();
    return 0;
}
