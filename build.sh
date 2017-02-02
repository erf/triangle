#!/bin/bash
# build on macOS ( requires GLFW )
cc -o triangle main.c -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo