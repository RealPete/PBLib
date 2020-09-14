cmake_minimum_required(VERSION 3.11)

PROJECT(
  PBLib
  VERSION 1.2.1
  LANGUAGES CXX C
)

include(CMakePackageConfigHelpers)
include(FetchContent)
include(GNUInstallDirs)

# ------------- Compiler Configuration -------------

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug"
    "Release"
    "MinSizeRel"
    "RelWithDebInfo"
  )
endif()

set(CMAKE_CXX_STANDARD 11)

# ------------- Find/Load External Dependencies -------------

find_package(Threads)
find_package(ZLIB)

# Load MiniSAT if its dependencies are available
if(Threads_FOUND AND ZLIB_FOUND)
  # Note: this seems to be the most up-to-date fork of MiniSAT
  FetchContent_Declare(
    minisat
    GIT_REPOSITORY    https://github.com/MontyThibault/minisat.git
    GIT_TAG           origin/master
  )

  #TODO: From CMake 3.14 this should be replaced by FetchContent_MakeAvailable(minisat)
  FetchContent_GetProperties(minisat)
  if(NOT minisat_POPULATED)
    FetchContent_Populate(minisat)
    add_subdirectory(${minisat_SOURCE_DIR} ${minisat_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()

# ------------- PBLib Library Definition -------------

add_library(pblib
  src/IncSimplePBConstraint.cpp
  src/IncrementalData.cpp
  src/PBConfig.cpp
  src/PBParser.cpp
  src/SimplePBConstraint.cpp
  src/VectorClauseDatabase.cpp
  src/auxvarmanager.cpp
  src/clausedatabase.cpp
  src/formula.cpp
  src/helper.cpp
  src/incpbconstraint.cpp
  src/pb2cnf.cpp
  src/pbconstraint.cpp
  src/preencoder.cpp

  src/encoder/BDD_Seq_Amo.cpp
  src/encoder/BinaryMerge.cpp
  src/encoder/Encoder.cpp
  src/encoder/SWC.cpp
  src/encoder/SortingNetworks.cpp
  src/encoder/adderencoding.cpp
  src/encoder/amo.cpp
  src/encoder/bdd.cpp
  src/encoder/bimander_amo_encoding.cpp
  src/encoder/binary_amo.cpp
  src/encoder/cardencoding.cpp
  src/encoder/commander_encoding.cpp
  src/encoder/k-product.cpp
  src/encoder/naive_amo_encoder.cpp
  src/encoder/sorting_merging.cpp
)
target_include_directories(pblib PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ------------- PBLib Executables -------------

add_executable(pbo2maxsat EXCLUDE_FROM_ALL src/bin/pbo2maxsat.cpp)
target_link_libraries(pbo2maxsat pblib)

add_executable(pbencoder EXCLUDE_FROM_ALL src/bin/pbencoder.cpp)
target_link_libraries(pbencoder pblib)

# ------------- PBLib Fuzzer -------------

if(Threads_FOUND AND ZLIB_FOUND)
  add_executable(fuzzer EXCLUDE_FROM_ALL
    src/bin/fuzzer/fuzzer.cpp
    src/bin/fuzzer/PBFuzzer.cpp
    src/bin/BasicPBSolver/BasicSATSolver.cpp
    src/bin/BasicPBSolver/SATSolverClauseDatabase.cpp
  )
  target_include_directories(fuzzer PRIVATE ${minisat_SOURCE_DIR})
  target_link_libraries(fuzzer
    pblib
    Threads::Threads
    ZLIB::ZLIB
    minisat-lib-static
  )
endif()

# ------------- PBLib Solver -------------

if(Threads_FOUND AND ZLIB_FOUND)
  add_executable(pbsolver EXCLUDE_FROM_ALL
    src/bin/BasicPBSolver/main.cpp
    src/bin/BasicPBSolver/BasicSATSolver.cpp
    src/bin/BasicPBSolver/SATSolverClauseDatabase.cpp
  )
  target_include_directories(pbsolver PRIVATE ${minisat_SOURCE_DIR})
  target_link_libraries(pbsolver
    pblib
    Threads::Threads
    ZLIB::ZLIB
    minisat-lib-static
  )
endif()

# ------------- Installation Target -------------

install(TARGETS pblib EXPORT PBLibTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  DIRECTORY include/pblib
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ------------- Generate CMake Package -------------

configure_file(cmake/PBLibConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfig.cmake
  COPYONLY
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
)
export(EXPORT PBLibTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibTargets.cmake
  NAMESPACE PBLib::
)

set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/PBLib)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfigVersion.cmake
  DESTINATION ${ConfigPackageLocation}
)

install(EXPORT PBLibTargets
  FILE PBLibTargets.cmake
  NAMESPACE PBLib::
  DESTINATION ${ConfigPackageLocation}
)
