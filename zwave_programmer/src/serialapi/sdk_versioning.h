#ifndef SDK_VERSIONING_H
#define SDK_VERSIONING_H 

/**
 * Convert version string to sdk version as described below
 *
 *    @param version string created by (first argument of) ZW_Version(version_string) 
 *    @return sdk version for e.g. 6.81.00
 */
const char* GenerateSdkVersionFromProtocolVersion(const char* version_string);

/**
 * Convert sdk version to nvm id 
 *
 *    @param sdk_ver returned by GenerateSdkVersionFromProtocolVersion()
 *    @param library_type returned by ZW_Version()
 *
 *    @return nvm_id for e.g. bridge6.81 
 */
const char * GenerateNvmIdFromSdkVersion(const char* sdk_ver, uint8_t library_type);
#endif
