# Over-The-Air firmware upgrades for Internet of Things devices with JFrog Bintray

* [Example of Bintray OTA Repository](https://bintray.com/ivankravets/platformio-ota/bintray-secure-ota)
* [swampUp 2018: Presentation](https://www.slideshare.net/ivankravets/swampup-overtheair-ota-firmware-upgrades-for-internet-of-things-devices-with-platformio-and-jfrog-bintray)

[<img src="https://user-images.githubusercontent.com/558053/84576259-993ec380-adb3-11ea-97a2-d89db9ee1de2.jpg" width="400">](https://www.youtube.com/watch?v=SrK9Yq_Wh1A)

## Step-by-Step Guide

### Preparations

Before we start, just follow the instructions below so you can later work alongside the step-by-step instructions.

* installed, working and updated PlatformIO
* your own fork of this *bintray-secure-ota* repository on [GitHub](https://github.com/platformio/bintray-secure-ota)
* network enabled microcontroller (we will be using a WIFI enabled [WEMOS LOLIN D32 PRO](https://docs.platformio.org/en/latest/boards/espressif32/lolin_d32_pro.html#id1)) + suitable usb cable for first-time firmware upload
* Bintray Setup
  * Create account at bintray.com
    * We will need the username later, mine is *r0oland*
  * Click **Add New Repository**
    * **Name**: Ours will be called *OTA_Github_Example_Repository*, we will need this name later in our platformio.ini file as well
    * **Type**: Generic
    * Click **Create**, now you are redirected to your new repository
  * Click **Add New Package**
    * This is where we will upload our actual, compiled firmwares binary files to which are then used for the OTA update by the microcontroller(s) directly
    * **Name** Ours will be called *OTA_Github_Example_Package*, we will need this name later in our platformio.ini file as well
    * **Licenses** Platformio uses Apache License 2.0, I like GNU General Public License v3.0 but you can pick your poison
    * **Version Control** Point this to your own github fork, in my case:
    *<https://github.com/r0oland/bintray-secure-ota>*
    * Click **Create Package**
  * Generate/find API token 
    * at bintray.com, hover over your user avatar in the top right, then click **Edit Profile**
    * in the left panel, click **API Key**
    * Generate / show API key
* *Optional* Setup environmental variables
  * These are an easy way to not worry about pushing our secrets to github when sharing our code
  * Create three variables
    * **BIN_TOKEN** - contains your bintray API key from above
    * **WIFI_SSID** - name of the wifi your uC will login to
    * **WIFI_PWD** - password for said wifi network
  * For Windows users
    * open command prompt, then enter
      * SetX BIN_TOKEN *your token*
      * SetX WIFI_SSID *your ssid*
      * SetX WIFI_PWD *your password*
    * This creates three, persistent user variables, see *Control Panel | System | Environment | System/User Variables*
    * Save yourself 2 hours of debugging attempts and restart your PC NOW

### Flashing the Firmware via USB

Before our uC can fetch it's firmware updates over the air (OTA), we need to compile and flash the firmware which includes the OTA libaries. This works just like any conventional firmware update via PlatformIO. First, we navigate to our fork of the bintray-secure-ota repository and edit the platformio.ini file to match our microcontroller and other settings.

You will have to adjust the following settings to match your Bintray account:

* `user = r0oland`
* `repository = OTA_Github_Example_Repository`
* `package = OTA_Github_Example_Package`
* `api_token = $env:BIN_TOKEN`
  * Either use environmental variables or replace *$env:BIN_TOKEN* directly with your API code...
* `ssid = $env:WIFI_SSID` & `password =  $env:WIFI_PWD`
  * same as `$env:BIN_TOKEN`, either make sure they are set correctly or replace directly with your info
* `platform = espressif32` 
* `upload_port = COM3`

You might also have to adjust some or all of the following, depending on your setup and operating system

[![Build Status](https://travis-ci.org/platformio/bintray-secure-ota.svg?branch=master)](https://travis-ci.org/platformio/bintray-secure-ota)