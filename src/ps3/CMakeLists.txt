cmake_minimum_required(VERSION 2.8)
project(ps3ldr)

cmake_policy(SET CMP0042 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../../cmake)
set(ELF_COMMON_PATH ${CMAKE_SOURCE_DIR}/../elf_common)
set(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/../../third_party)

set(SOURCES
    ${ELF_COMMON_PATH}/elf_reader.h
    ${ELF_COMMON_PATH}/elf.h
    ${THIRD_PARTY_PATH}/tinyxml/tinystr.cpp
    ${THIRD_PARTY_PATH}/tinyxml/tinystr.h
    ${THIRD_PARTY_PATH}/tinyxml/tinyxml.cpp
    ${THIRD_PARTY_PATH}/tinyxml/tinyxml.h
    ${THIRD_PARTY_PATH}/tinyxml/tinyxmlerror.cpp
    ${THIRD_PARTY_PATH}/tinyxml/tinyxmlparser.cpp
    cell_loader.cpp
    cell_loader.h
    ps3.cpp
    sce.h
)

find_package(IdaSdk REQUIRED)

add_ida_loader(ps3ldr EA64 ${SOURCES})

target_include_directories(ps3ldr${_llx}
    PUBLIC ${IdaSdk_INCLUDE_DIRS}
    PRIVATE ${ELF_COMMON_PATH} ${THIRD_PARTY_PATH}/tinyxml
)
target_include_directories(ps3ldr${_llx64}
    PUBLIC ${IdaSdk_INCLUDE_DIRS}
    PRIVATE ${ELF_COMMON_PATH} ${THIRD_PARTY_PATH}/tinyxml
)

target_include_directories(ps3ldr${_llx} PUBLIC ${IdaSdk_INCLUDE_DIRS})
target_include_directories(ps3ldr${_llx64} PUBLIC ${IdaSdk_INCLUDE_DIRS})

target_link_libraries(ps3ldr${_llx} ${IdaSdk_LIBRARIES})
target_link_libraries(ps3ldr${_llx64} ${IdaSdk_LIBRARIES})

set_target_properties(ps3ldr${_llx} ps3ldr${_llx64} PROPERTIES
    CXX_STANDARD 11
)
