#include <Arduino.h>
#include <unity.h>

#include <BintrayClient.h>
#include <WiFi.h>

const BintrayClient bintray(BINTRAY_USER, BINTRAY_REPO, BINTRAY_PACKAGE);

// void setUp(void) {

// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_wifi_connection(void) {
    const int RESPONSE_TIMEOUT_MS = 5000;
    unsigned long timeout = millis();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - timeout > RESPONSE_TIMEOUT_MS) {
            TEST_FAIL_MESSAGE("WiFi connection timeout. Please check your settings!");
        }

        delay(500);
    }

    TEST_ASSERT_TRUE(WiFi.isConnected());
}

void test_bintray_client_credentials(void) {
    TEST_ASSERT_EQUAL_STRING(BINTRAY_USER, bintray.getUser().c_str());
    TEST_ASSERT_EQUAL_STRING(BINTRAY_REPO, bintray.getRepository().c_str());
    TEST_ASSERT_EQUAL_STRING(BINTRAY_PACKAGE, bintray.getPackage().c_str());
}

void test_bintray_latest_version_is_not_empty(void) {
    const String version = bintray.getLatestVersion();
    TEST_ASSERT_TRUE(version.length() > 0);
    TEST_ASSERT_TRUE(atoi(version.c_str()) !=  0);
}

void test_bintray_binary_path_is_valid(void) {
    const String binaryPath = bintray.getBinaryPath(bintray.getLatestVersion());
    TEST_ASSERT_TRUE(binaryPath.length() > 0);
    TEST_ASSERT_TRUE(binaryPath.endsWith(".bin"));
    TEST_ASSERT_TRUE(binaryPath.indexOf(BINTRAY_USER) > 0);
}


void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_bintray_client_credentials);
    RUN_TEST(test_wifi_connection);
    RUN_TEST(test_bintray_latest_version_is_not_empty);
    RUN_TEST(test_bintray_binary_path_is_valid);
    UNITY_END();
}

void loop() {}
