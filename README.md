# linux-enable-ir-emitter
Provides support for infrared cameras that are not directly supported.

This program was originally designed by PetePriority (https://github.com/PetePriority/chicony-ir-toggle). However, the handling of the error codes was not correct, which made it difficult to modify it.
I also provide in the readme a complete tutorial to help you adapt it to your camera.

This script was created to use Howdy, a Windows Hello for linux <https://github.com/boltgolt/howdy>.

## Setting up the script
1. Download enable-ir-emitter.c
2. Run the command `lsusb` to find your camera bus and write it down for later (step 7).
3. List your camera path with `v4l2-ctl --list-devices` and try to find the ir camera with `ffplay /dev/videoX` (ffmpeg package).
When you have found the path corresponding to the ir camera, write it down later (step 11).
4. Install Windows in a VM and allow Windows access to the camera.
5. Install Wireshark on your distro
6. Run the command `sudo modprob usbmon` to allow Wireshark to observe the bus and start it with sudo.
8. In Wireshark and go to the usbmon corresponding to the number of the bus and use the filter `usb.transfer_type == 0x02 && usb.bmRequestType == 0x21` (to only display camera control packets)
9. Go in the security options tab of the Windows settings and click on launch an improvement of the recognition of Windows Hello. A pop up is displayed and asks if we want to start the test, you can go back to Wireshark without having to go any further.
10. You can stop the reccording in Wireshark. Now you will have to find the right wValue and wIndex associated with the emitter in Wireshark. For this you will have to test each different proposal of the Wireshark logs.
11. Open the Setup Data section, and note the wValue, the wIndex, the wLength and the Data fragment for the next step.
12. Open the enable-ir-emitter.c file and modify my information with yours (the file is commented to help you).
13. Disconnect the camera from the vm and run `gcc enable-ir-emitter.c -o enable-ir-emitter` followed by `./enable-ir-emitter`
14. If you don't have an error code, try if it work with `ffplay /dev/videoX` ! (or `sudo howdy test`)
15. If not go back to step 11 to test the next entry.

For howdy, set the dark_threshold to 100 in `sudo howdy config`

## Launch the script at each startup (with systemd)
1. Download enable-ir-emitter.service.
2. Copy enable-ir-emitter to /usr/local/bin : `sudo cp enable-ir-emitter /usr/local/bin`.
3. Copy `enable-ir-emitter.service` to /etc/systemd/system/ : `sudo cp enable-ir-emitter.service /etc/systemd/system/`.
4. Run `sudo systemctl enable enable-ir-emitter && sudo systemctl start enable-ir-emitter` to launch the script each time the system is opened.

## Note
However, at the step 8-9, to find the packet that activates the emitter may be sent at another time. For example, it may be sent at the beginning of the test, so you have to launch it. Or at the moment when Windows start because with my camera Windows turns off the transmitter every time it is no longer needed but maybe not with your camera.

I can therefore only advise you to test as many cases as possible where the emitter could receive a packet asking it to prepare to emit when the camera is turned on. I remain available if you need more details !

## Documentation
* <https://www.kernel.org/doc/html/v5.7/media/v4l-drivers/uvcvideo.html>
* <https://wiki.wireshark.org/CaptureSetup/USB>
