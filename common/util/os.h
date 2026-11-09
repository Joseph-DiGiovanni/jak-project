#pragma once

#include <cstddef>
#include <optional>
#include <string>

size_t get_peak_rss();
void setup_cpu_info();

struct CpuInfo {
  bool initialized = false;
  bool has_avx = false;
  bool has_avx2 = false;
  bool has_neon = false;
  // ARM64 CRC32 instructions, required by ARM64 builds (common/util/crc32.h)
  bool has_crc32 = false;

  std::string brand;
  std::string model;
};

CpuInfo& get_cpu_info();

std::optional<double> get_macos_major_version();
