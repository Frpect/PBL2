cmake_minimum_required(VERSION 3.16)
project(PBL2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/UI/*.cpp"
    "${CMAKE_SOURCE_DIR}/storage/*.cpp"
    "${CMAKE_SOURCE_DIR}/services/*.cpp"
    "${CMAKE_SOURCE_DIR}/models/*.cpp"
    "${CMAKE_SOURCE_DIR}/utils/*.cpp"
)
add_executable(PBL2 ${SRC})

find_package(SDL2 CONFIG REQUIRED)
find_library(SDL2_MIXER_LIB SDL2_mixer REQUIRED)
find_library(SDL2_IMAGE_LIB SDL2_image REQUIRED)
find_library(SDL2_TTF_LIB SDL2_ttf REQUIRED)
# Thêm thư mục include (đặc biệt quan trọng nếu bạn dùng header SDL_image, SDL_ttf)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/services
    ${CMAKE_SOURCE_DIR}/storage
    ${CMAKE_SOURCE_DIR}/UI
    ${CMAKE_SOURCE_DIR}/models
    ${CMAKE_SOURCE_DIR}/utils
)
include_directories("C:/msys64/mingw64/include/SDL2")

# Liên kết các thư viện - thứ tự rất quan trọng
link_directories("C:/msys64/mingw64/lib")

target_link_libraries(PBL2
    PRIVATE
        -lmingw32
        -lSDL2main
        -lSDL2
        -lSDL2_image
        -lSDL2_ttf
        -lSDL2_mixer
)