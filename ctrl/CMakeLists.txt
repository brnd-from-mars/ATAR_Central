target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PIDController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SpeedController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AlignmentController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DriveController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TargetTranslationController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TargetRotationController.cpp)
