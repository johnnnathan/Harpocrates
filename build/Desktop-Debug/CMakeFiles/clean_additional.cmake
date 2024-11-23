# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Haprocrates_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Haprocrates_autogen.dir/ParseCache.txt"
  "Haprocrates_autogen"
  )
endif()
