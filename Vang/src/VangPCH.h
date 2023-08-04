#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <filesystem>
#include <format>
#include <functional>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <source_location>
#include <stdexcept>
#include <string_view>
#include <sstream>
#include <variant>
#include <vector>

#include "Vang/Utility/Logging/Log.h"

// TODO: Move this somewhere else for helper defines
#define BIT(x) (1 << x)

#define VANG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)