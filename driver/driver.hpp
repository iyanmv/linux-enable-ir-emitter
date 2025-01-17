#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Driver
{
public:
    const string device;
    const uint8_t unit;
    const uint8_t selector;
    const vector<uint8_t> control;

    Driver() = delete;

    explicit Driver(const string &device, uint8_t unit, uint8_t selector, const vector<uint8_t> &control);

    ~Driver() = default;

    Driver &operator=(const Driver &) = delete;

    Driver(const Driver &) = delete;

    Driver &operator=(Driver &&other) = delete;

    Driver(Driver &&other) = delete;

    static void writeDriver(const string &driverFile, const unique_ptr<Driver> &driver);

    static unique_ptr<Driver> readDriver(const string &driverFile);
};

#endif
