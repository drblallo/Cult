ADD_LIBRARY(glad STATIC)

message("Compiling glad")
TARGET_INCLUDE_DIRECTORIES(glad PRIVATE src/ PUBLIC include/)
TARGET_SOURCES(glad PRIVATE src/glad.c)
message("Done compiling glad")
