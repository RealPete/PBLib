cmake_minimum_required(VERSION 3.1)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

PROJECT(
  PBLib
  VERSION 0.1.0
  LANGUAGES CXX C
)

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

find_package(Threads)
find_package(ZLIB REQUIRED)

# ------------- PBLib Library Definition -------------

add_library(pblib
  "IncSimplePBConstraint.cpp"
  "IncrementalData.cpp"
  "PBConfig.cpp"
  "PBFuzzer.cpp"
  "PBParser.cpp"
  "SimplePBConstraint.cpp"
  "VectorClauseDatabase.cpp"
  "auxvarmanager.cpp"
  "clausedatabase.cpp"
  "formula.cpp"
  "helper.cpp"
  "incpbconstraint.cpp"
  "pb2cnf.cpp"
  "pbconstraint.cpp"
  "preencoder.cpp"

  "encoder/adderencoding.cpp"
  "encoder/amo.cpp"
  "encoder/bdd.cpp"
  "encoder/BDD_Seq_Amo.cpp"
  "encoder/bimander_amo_encoding.cpp"
  "encoder/binary_amo.cpp"
  "encoder/BinaryMerge.cpp"
  "encoder/cardencoding.cpp"
  "encoder/commander_encoding.cpp"
  "encoder/Encoder.cpp"
  "encoder/k-product.cpp"
  "encoder/naive_amo_encoder.cpp"
  "encoder/sorting_merging.cpp"
  "encoder/SortingNetworks.cpp"
  "encoder/SWC.cpp"
)

# ------------- PBLib Executables -------------

add_executable(pbo2maxsat EXCLUDE_FROM_ALL pbo2maxsat.cpp)
target_link_libraries(pbo2maxsat pblib)

add_executable(pbencoder EXCLUDE_FROM_ALL pbencoder.cpp)
target_link_libraries(pbencoder pblib)

# ------------- PBLib Fuzzer -------------

if(Threads_FOUND AND ZLIB_FOUND)
  # TODO: Currrently does not link correctly
  add_executable(fuzzer EXCLUDE_FROM_ALL fuzzer.cpp BasicPBSolver/SATSolverClauseDatabase.cpp)
  target_link_libraries(fuzzer pblib Threads::Threads ZLIB::ZLIB minisat)
  include_directories(fuzzer ${CMAKE_CURRENT_SOURCE_DIR}/BasicPBSolver/minisat/)
  link_directories(fuzzer ${CMAKE_CURRENT_SOURCE_DIR}/BasicPBSolver/minisat/)
endif()

# ------------- PBLib Solver -------------

# TODO: Integrate into top level CMakeList.txt

# ------------- Installation Target -------------

install(TARGETS pblib EXPORT PBLibTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ------------- Generate CMake Package -------------

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfigVersion.cmake"
  VERSION ${PBLib_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT PBLibTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibTargets.cmake"
  NAMESPACE Upstream::
)
configure_file(cmake/PBLibConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/PBLib)
install(EXPORT PBLibTargets
  FILE PBLibTargets.cmake
  NAMESPACE PBLib::
  DESTINATION ${ConfigPackageLocation}
)
install(
  FILES cmake/PBLibConfig.cmake "${CMAKE_CURRENT_BINARY_DIR}/PBLib/PBLibConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation}
  COMPONENT Devel
)
