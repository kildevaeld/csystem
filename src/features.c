#include <csystem/features.h>

static const char *_cs_platform_name = CS_PLATFORM_NAME;

const char *cs_platform_name() { return _cs_platform_name; }