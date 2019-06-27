cmake_minimum_required(VERSION 3.14)
project(Testing_Enviornment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(.)

add_executable(Testing_Enviornment
        DirectoryManager.cpp
        DirectoryManager.h
        ExpectedData.cpp
        ExpectedData.h
        main.cpp
        OutData.cpp
        OutData.h
        OUTReader.cpp
        OUTReader.h
        ReaderBase.cpp
        ReaderBase.h
        ReadMode.cpp
        ReadMode.h
        TestComparator.cpp
        TestComparator.h
        TestFilePair.cpp
        TestFilePair.h
        XPCTReader.cpp
        XPCTReader.h
        TestResult.h
        TestResult.cpp
        TestTracker.h
        TestTracker.cpp)
