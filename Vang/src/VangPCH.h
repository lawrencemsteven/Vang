#pragma once

#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
#include <concepts>
#include <filesystem>
#include <format>
#include <functional>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <memory>
#include <set>
#include <source_location>
#include <stdexcept>
#include <string_view>
#include <sstream>
#include <thread>
#include <variant>
#include <vector>

#include "Vang/Utility/Logging/Log.h"
#include "Vang/Utility/Time/Time.h"

// TODO: Move this somewhere else for helper defines
#define BIT(x) (1 << x)

#define VANG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)