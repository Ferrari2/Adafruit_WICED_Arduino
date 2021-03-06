/*********************************************************************
 This is an example for our Feather WIFI modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include "adafruit_feather.h"

/* This example demonstrates how to get and set the WiFi country domain.
 *  
 * - The sketch will get the current country from non-volatile memory
 *   and print out its abbreviation (2 last bytes of the country code)
 * - If value is not the same as WLAN_COUNTRY, attempts to change the country 
 * 
 * Note:
 * - Complete list of country codes is in adafruit_constants.h file.
 * - setWifiCountry() will save the country to NVM, i.e it will
 *   persist through power loss or a device reset
 * 
 * WiFi Regulations
 * - US : channel 1-11
 * - EU : channel 1-13
 * - JP : channel 1-13
 * - Rest of the world mostly allows channel 1-13
 */

#define WLAN_SSID            "yourSSID"
#define WLAN_PASS            "yourPassword"

#define WLAN_COUNTRY          WIFI_COUNTRY_UNITED_STATES // See adafruit_constants.h for country list

/**************************************************************************/
/*!
    @brief  The setup function runs once when reset the board
*/
/**************************************************************************/
void setup()
{
  Serial.begin(115200);

  // Wait for the Serial Monitor to open
  while (!Serial)
  {
    /* Delay required to avoid RTOS task switching problems */
    delay(1);
  }

  Serial.println("WiFi Country Example\r\n");

  // Print all software versions
  Feather.printVersions();

  /* Get current country code
   * Note: The last 2 bytes of code containing Country Abbreviation
   */
  uint32_t country = Feather.getWifiCountry();
  char abbreviation[3] = { (country & 0xff), (country >> 8) & 0xff };

  Serial.print("Current configured Country: ");
  Serial.println(abbreviation);

  if ( WLAN_COUNTRY != country )
  {
    Serial.println("Change country to one defined by WLAN_COUNTRY");
    Feather.setWifiCountry(WLAN_COUNTRY);
  }
  
  while ( !connectAP() )
  {
    delay(500); // delay between each attempt
  }

  // Connected: Print network info
  Feather.printNetwork();
}

/**************************************************************************/
/*!
    @brief  The loop function runs over and over again forever
*/
/**************************************************************************/
void loop()
{
}

/**************************************************************************/
/*!
    @brief  Connect to defined Access Point
*/
/**************************************************************************/
bool connectAP(void)
{
  // Attempt to connect to an AP
  Serial.print("Please wait while connecting to: '" WLAN_SSID "' ... ");

  if ( Feather.connect(WLAN_SSID, WLAN_PASS) )
  {
    Serial.println("Connected!");
  }
  else
  {
    Serial.printf("Failed! %s (%d)", Feather.errstr(), Feather.errnum());
    Serial.println();
  }
  Serial.println();

  return Feather.connected();
}
