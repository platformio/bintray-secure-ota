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
  * Checkout this website regarding the overall structure of Bintray, i.e. repositories vs. packages www.jfrog.com/confluence/display/BT/Key+Concepts
  * Click **Add New Repository**
    * **Name**: Ours will be called *OTA_Repo*, we will need this name later in our platformio.ini file as well
    * **Type**: Generic
    * Click **Create**, now you are redirected to your new repository
  * Click **Add New Package**
    * This is where we will upload our actual, compiled firmwares binary files to which are then used for the OTA update by the microcontroller(s) directly
    * **Name** Ours will be called *OTA_Tutorial*, we will need this name later in our platformio.ini file as well
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
    * open command prompt with admin rights
      * press Windows key
      * search for CMD
      * right click -> run as Administrator
    * in the prompt enter
      * SetX BIN_TOKEN *your token*
      * SetX WIFI_SSID *your ssid*
      * SetX WIFI_PWD *your password*
    * This creates three, persistent user variables, see *Control Panel | System | Environment | System/User Variables*
    * Save yourself 2 hours of debugging attempts and restart your PC NOW
    * Really, trust me, you want to restart. NOW.

### Flashing the Firmware via USB

Before our uC can fetch it's firmware updates over the air (OTA), we need to compile and flash the firmware which includes the OTA libaries. This works just like any conventional firmware update via PlatformIO. First, we navigate to our fork of the bintray-secure-ota repository and edit the platformio.ini file to match our microcontroller and other settings.

You will have to adjust the following settings to match your Bintray account:

* `user = {your user name}, e.g. r0oland`
* `repository = {your_bintray_repo_name}, e.g. OTA_Repo`
* `package = {your_bintray_repo_name}, e.g. OTA_Tutorial`
* `api_token = $env:BIN_TOKEN`
  * Either use environmental variables or replace *$env:BIN_TOKEN* directly with your API code...
* `ssid = $env:WIFI_SSID`
  * see `$env:BIN_TOKEN`, either make sure your environmental variables are set correctly or replace directly with your info
* `password =  $env:WIFI_PWD`
  * see `$env:BIN_TOKEN`, either make sure your environmental variables are set correctly or replace directly with your info
* `platform = {your platfrom}, e.g. espressif32` 
* `board = {your uC board}, e.g. lolin_d32_pro`
* `upload_port = {your COM port}, e.g. COM6`

Once all those changes have been made, compile and upload the firmware to your uC using Platformio in the "old" way, i.e. click **Upload** in the PlatformIO GUI. Once the upload was successful, you should see the following output on the Serial port:

```
Device version: v.0
Connecting to {your wifi ssid here}...connected!
Warning: Could not find any version info. Have you uploaded a firmware yet?
Could not load info about the latest firmware, so nothing to update. Continue ..
```

### Flashing the firmware Over The Air (OTA)

Now your uC is checking bintray constantly for new firmware, so let's upload a new version there, so we can get our first OTA update. In your `platformio.ini` file, you have to change only two lines of code:
* Change `default_envs = debug` to `default_envs = release`
* Change `release_version = 0` to `release_version = 1`

*Optional* Change the delays in `main.cpp` from 1000 ms to something shorter / longer so you can immediately see if the firmware was updated. 

Upload the new code via the Platformio upload command or upload button. The code will compile from scratch, but at the end of the complie process, the code will be uploaded to bintray rather than to your uC. This should look something like this
```
Uploading .pio\build\release\firmware_v_1.bin
Uploading firmware_v_1.bin to Bintray. Version: 1
The firmware has been successfuly published at Bintray.com!
```  

Now open your serial monitor, sit back and relax while you wait for your uC to notice the new firmware. In your serial monitor, you should eventually (after a few seconds) see
```
There is a new version of firmware available: v.1
Got application/octet-stream payload.
Starting Over-The-Air update. This may take some time to complete ...
``` 

This took around 15-20 seconds in my case, but I guess this depends a lot on the size of your firmware, uC, etc... Your uC will eventuall restart, after which you should see:
``` 
Device version: v.1
Connecting to {your wifi ssid }. connected!
The current firmware is up to date. Continue ...
``` 
Congrats, you just successfully did your first OTA update.

[![Build Status](https://travis-ci.org/platformio/bintray-secure-ota.svg?branch=master)](https://travis-ci.org/platformio/bintray-secure-ota)

