# TopDown_Shooter_INT2215_SDL3
Game Project for INT2215 (Advanced Programming) in Semester 24252 

## How to build from source?
1. Clone this repo:\
   Run this command
   ```bash
   mkdir TopDownShooter
   cd TopDownShooter
   git clone --recurse-submodules https://github.com/gawgua/TopDown_Shooter_INT2215_SDL3.git
   ```
2. Build:\
	Run this command (add `-G "MinGW Makefiles"` if using MinGW on Windows)
	```bash
	cmake -S . -B build
	cmake --build build
	```

The build should be located on ./build/src/Debug or ./build/src/Release
