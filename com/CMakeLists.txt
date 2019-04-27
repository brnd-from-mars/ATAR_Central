target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DataSourceAlpha.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DataSourceBeta.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DataDestinationUSB.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DataDestinationAlpha.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DataDestinationBeta.cpp)
