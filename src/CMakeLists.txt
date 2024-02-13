

include_directories(
        ${PROJECT_SOURCE_DIR}/src/character
        ${PROJECT_SOURCE_DIR}/src/db
)

set(HEADER ${HEADER}
        ${PROJECT_SOURCE_DIR}/src/db/UserDb.h
        ${PROJECT_SOURCE_DIR}/src/db/UserModel.h

        ${PROJECT_SOURCE_DIR}/src/character/common.h
        ${PROJECT_SOURCE_DIR}/src/character/Character.h
        ${PROJECT_SOURCE_DIR}/src/character/Archer.h
)

set(SOURCE ${SOURCE}
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/db/UserDb.cpp

        ${PROJECT_SOURCE_DIR}/src/character/common.cpp
        ${PROJECT_SOURCE_DIR}/src/character/Character.cpp
        ${PROJECT_SOURCE_DIR}/src/character/Archer.cpp
)

add_executable(${PROJECT_NAME}
        ${HEADER}
        ${SOURCE}
)