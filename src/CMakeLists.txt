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

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer)