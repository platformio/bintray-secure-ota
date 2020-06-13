# Over-The-Air firmware upgrades for Internet of Things devices with JFrog Bintray

* [Example of Bintray OTA Repository](https://bintray.com/ivankravets/platformio-ota/bintray-secure-ota)
* [swampUp 2018: Presentation](https://www.slideshare.net/ivankravets/swampup-overtheair-ota-firmware-upgrades-for-internet-of-things-devices-with-platformio-and-jfrog-bintray)

[<img src="https://user-images.githubusercontent.com/558053/84576259-993ec380-adb3-11ea-97a2-d89db9ee1de2.jpg" width="400">](https://www.youtube.com/watch?v=SrK9Yq_Wh1A)

## Step-by-Step Guide

### Preparations

Before we start, just follow the instructions below so you can later work alongside the step-by-step instructions. 

* installed, working and updated PlatformIO
* your own fork of this repository on GitHub
* network enabled microcontroller (we will be using a WIFI enabled [WEMOS LOLIN D32 PRO](https://docs.platformio.org/en/latest/boards/espressif32/lolin_d32_pro.html#id1)) + suitable usb cable for first-time firmware upload
* Bintray Setup
  * Create account at bintray.com
  * Click **Add New Repository**
    * **Name**: Ours will be called *OTA_Github_Example_Repository*
    * **Type**: Generic
    * Click **Create**, now you are redirected to your new repository
  * Click **Add New Package**
    * This is where we will upload our actual, compiled firmwares binary files to which are then used for the OTA update by the microcontroller(s) directly
    * Ours will be call *OTA_Github_Example_Package*

### Flashing the Firmware via USB

Before our uC can fetch it's firmware updates over the air (OTA), we need to compile and flash the firmware which includes the OTA libaries. This works just like any conventional firmware update via PlatformIO:



[![Build Status](https://travis-ci.org/platformio/bintray-secure-ota.svg?branch=master)](https://travis-ci.org/platformio/bintray-secure-ota)