#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "Serialapi.h"
#include "sdk_versioning.h" 

const char* GenerateSdkVersionFromProtocolVersion(const char* version_string)
{
  const char* sdk_version = "0.00.00"; // Unknown version

  if (version_string)
  {
    int major = 0;
    int minor = 0;

    // The version string is encoded as "Z-Wave M.mm"
    int args_processed = sscanf(version_string, "Z-Wave %1d.%2d", &major, &minor);
    if (2 == args_processed)
    {
      /* Mapping major protocol version to SDK versions
      * See Z-Wave protocol versions table in:
      * "Z-Wave 700 Series Appl. Programmers Guide" (INS14258)
      */
      switch (major * 100 + minor)
      {
        case 412:
        case 414:
          sdk_version = "6.60.00"; break;
        case 433:
          sdk_version = "6.61.00"; break;
        case 462:
          sdk_version = "6.61.01"; break;
        case 428:
          sdk_version = "6.70.00"; break;
        case 445:
          sdk_version = "6.70.01"; break;
        case 460:
          sdk_version = "6.71.00"; break;
        case 461:
          sdk_version = "6.71.01"; break;
        case 502:
          sdk_version = "6.71.02"; break;
        case 503:
          sdk_version = "6.71.03"; break;
        case 601:
          sdk_version = "6.81.00"; break;
        case 602:
          sdk_version = "6.81.01"; break;
        case 603:
          sdk_version = "6.81.02"; break;
        case 604:
          sdk_version = "6.81.03"; break;
        case 605:
          sdk_version = "6.81.04"; break;
        case 606:
          sdk_version = "6.81.05"; break; // Unconfirmed
        case 700:
          sdk_version = "7.00.00"; break;
        case 711:
          sdk_version = "7.11.00"; break; 
        case 712:
          sdk_version = "7.12.00"; break; 
        case 713:
          sdk_version = "7.13.00"; break; 
        case 714:
          sdk_version = "7.14.00"; break; 
        default:
          /* Ideally the above table should be updated with every new release.
          * But in case this does not always happen we make a simple generic
          * fallback mapping from protocol version to sdk version
          */
          if (6 == major)
          {
            sdk_version = "6.8x.xx"; break;
          }
          if (7 == major)
          {
            sdk_version = "7.xx.xx"; break;
          }
          if (8 == major)
          {
            sdk_version = "8.xx.xx"; break;
          }
          break;
      }
    }
  }
  return sdk_version;
}

const char * GenerateNvmIdFromSdkVersion(const char* sdk_ver,
                                                uint8_t library_type)
{
  static char nvm_id_buf[20] = {};

  nvm_id_buf[0] = '\0';

  if (sdk_ver)
  {
    /* The SDK version is assumed as M.mm.pp, i.e. first digit is major
     * version number (see GenerateSdkVersionFromProtocolVersion())
     */
    if(strncmp("7.11.00",sdk_ver,7) == 0) {
      return "bridge7.11";
    } else if (sdk_ver[0] > '6')
    {
      /* For now we don't differentiate between the versions following
       * version 6, we simply assume they all use the nvm3 file system
       * driver.
       */
      return "bridge7.12";
    }
    else
    {
      const char *library_type_str = "";

      switch (library_type)
      {
       case ZW_LIB_CONTROLLER_BRIDGE:
          library_type_str = "bridge";
          break;
       case ZW_LIB_CONTROLLER_STATIC:
          library_type_str = "static";
          break;
       case ZW_LIB_CONTROLLER:
          library_type_str = "portable";
          break;
        default:
          library_type_str = "ERROR";
          break;
      }

      /* As the NVM layout for SDK 6.8x was only changed after 6.81.00, we handle 6.81.00 as a 6.7 controller. */
      if(strncmp( sdk_ver, "6.81.00", 7 ) == 0) {
        snprintf(nvm_id_buf, sizeof(nvm_id_buf), "%s6.7", library_type_str);
      } else {
        /* Only use the first three chars of the sdk version,
        * i.e. 6.81.03 becomes 6.8. End result e.g. "bridge6.8"
        */
        snprintf(nvm_id_buf, sizeof(nvm_id_buf), "%s%.3s", library_type_str, sdk_ver);
      }

    }
  }
  return nvm_id_buf; // Static buffer
}


