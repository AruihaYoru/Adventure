@echo off
echo Building Peaceful Edition...
emcc main.cpp Adventure.cpp -o adventure_peaceful.js -s EXPORTED_RUNTIME_METHODS="[\"ccall\", \"cwrap\"]" -s EXPORTED_FUNCTIONS="[\"_main\", \"_set_key\", \"_get_screen_buffer\"]" -O3 -DPEACEFUL_MODE
echo Done!
