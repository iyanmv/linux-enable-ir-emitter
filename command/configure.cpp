#include "commands.hpp"

#include <memory>
using namespace std;

#include "globals.hpp"
#include "../driver/finder.hpp"
#include "../driver/driver.hpp"
#include "../camera/camera.hpp"
#include "../camera/autocamera.hpp"
#include "../utils/logger.hpp"

void enableDebug()
{
    Logger::enableDebug();
}

/**
 * @brief Find a driver for the infrared camera.
 *
 * @param device path to the infrared camera, empty string for automatic detection
 * @param manual true for enabling the manual configuration
 * @param emitters number of emitters on the device
 * @param negAnswerLimit number of negative answer before the pattern is skiped. Use -1 for unlimited
 *
 * @return exit code
 */
ExitCode configure(const char *device_char_p, bool manual, unsigned emitters, unsigned negAnswerLimit)
{
    const string device = string(device_char_p);

    Logger::info("Stand in front of and close to the camera and make sure the room is well lit.");
    Logger::info("Ensure to not use the camera during the execution.");
    Logger::info("Warning to do not kill the process !");

    shared_ptr<Camera> camera;
    if (manual)
    {
        if (device.empty())
            camera = Camera::findGrayscaleCamera();
        else
            camera = make_shared<Camera>(device);
    }
    else
    {
        if (device.empty())
            camera = AutoCamera::findGrayscaleCamera();
        else
            camera = make_shared<AutoCamera>(device);
    }

    if (camera == nullptr)
        Logger::critical(ExitCode::FAILURE, "Impossible to find an infrared camera.");

    Logger::info("Configuring the camera:", camera->device, ".");

    const string deviceName = device.substr(device.find_last_of("/") + 1);
    const string excludedPath = SAVE_DRIVER_FOLDER_PATH + deviceName + ".excluded";
    Finder finder(*camera, emitters, negAnswerLimit, excludedPath);

    try
    {
        if (camera->Camera::isEmitterWorking())
        {
            Logger::error("Your emiter is already working, skipping the configuration.");
            return ExitCode::FAILURE;
        }

        auto drivers = finder.find();
        if (drivers->empty())
        {
            Logger::error("The configuration has failed.");
            Logger::error("Please retry in manual mode by adding the '-m' option.");
            Logger::info("Do not hesitate to visit the GitHub !");
            Logger::info("https://github.com/EmixamPP/linux-enable-ir-emitter/blob/master/docs/README.md");
            return ExitCode::FAILURE;
        }

        for (unsigned i = 0; i < drivers->size(); ++i)
        {
            string driverPath = SAVE_DRIVER_FOLDER_PATH + deviceName + "_emitter" + to_string(i) + ".driver";
            auto &driver = drivers->at(i);
            Driver::writeDriver(driverPath, driver);
        }
    }
    catch (CameraException &e)
    {
        Logger::critical(ExitCode::FILE_DESCRIPTOR_ERROR, e.what());
    }

    Logger::info("The driver has been successfully generated.");
    return ExitCode::SUCCESS;
}
