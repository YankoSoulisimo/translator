 
PROJECT(translator)

cmake_minimum_required(VERSION 2.6)

cmake_minimum_required(VERSION 2.6)

#set(CMAKE_BUILD_TYPE Debug)
add_definitions("-std=c++0x")
add_definitions("-Wall")
set(BOOST_INCLUDEDIR "/home/vladimir/opt/include")
link_directories (/home/vladimir/opt/lib )

ADD_DEFINITIONS(-fpermissive)


include_directories(
${BOOST_INCLUDEDIR}
./
../
)

link_libraries (
  curl
  boost_program_options
)

ADD_EXECUTABLE(translator
./main.cpp
)

GET_TARGET_PROPERTY(EXE_NAME translator LOCATION)
SET(NEW_EXE_NAME translator)
