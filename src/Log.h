#pragma once

#include "logging/Logger.h"
#include "logging/OperationDataFormatter.h"

#ifdef USE_NULL_LOGGER
#    include "logging/NullLogger.h"
#    define LOGGER NullLogger
#else
#    include "logging/SpdLogger.h"
#    define LOGGER SpdLogger
#endif

using Log = LOGGER;