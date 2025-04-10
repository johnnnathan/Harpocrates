# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Harpocrates_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Harpocrates_autogen.dir/ParseCache.txt"
  "Harpocrates_autogen"
  )
endif()
