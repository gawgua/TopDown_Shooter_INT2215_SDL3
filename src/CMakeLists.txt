add_executable(${PROJECT_NAME} main.cpp 
	Game/Game.cpp
	Game/Entity.cpp 
	Game/Player.cpp
	Game/Enemy.cpp 
	Game/Bullet.cpp 

	UI/Button.cpp 
	UI/ScoreText.cpp
	UI/UI.cpp
	UI/MainMenu.cpp
	UI/GameOver.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
    target_compile_options(${PROJECT_NAME} PRIVATE /MT)
    target_link_options(${PROJECT_NAME} PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer)