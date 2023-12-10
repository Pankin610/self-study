set (CMAKE_CXX_STANDARD 14)

cmake_minimum_required(VERSION 3.0)

project(TypeLists)

add_executable(MyExecutable Tests.C)

target_sources(MyExecutable PRIVATE
    Erase.H
    IndexOf.H
    Length.H
    SortedBySize.H
    TypeList.H
)