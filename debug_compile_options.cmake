MACRO(debug_compile_options target)

    TARGET_COMPILE_OPTIONS(
            ${target} PRIVATE
            "$<$<CONFIG:DEBUG>:-W>"
            "$<$<CONFIG:DEBUG>:-Wall>"
            "$<$<CONFIG:DEBUG>:-g>"
    )

    if (ASAN)
        message("--compiling with asan ${ASAN}")
        TARGET_COMPILE_OPTIONS(
                ${target} PRIVATE
                "$<$<CONFIG:DEBUG>:-O1>"
                "$<$<CONFIG:DEBUG>:-fsanitize=${ASAN}>"
                "$<$<CONFIG:DEBUG>:-fno-omit-frame-pointer>"
        )
        if (${ASAN} MATCHES "address")
            TARGET_LINK_LIBRARIES(${target} PRIVATE debug asan)
        elseif(${ASAN} MATCHES "thread")
            TARGET_LINK_LIBRARIES(${target} PRIVATE debug tsan)
        endif()
    endif()

    if (COVERAGE)
        message("--compiling with coverage")
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
        TARGET_COMPILE_OPTIONS(
                ${target} PRIVATE
                "$<$<CONFIG:DEBUG>:--coverage>"
                "$<$<CONFIG:DEBUG>:-O0>"
                "$<$<CONFIG:DEBUG>:-fno-inline>"
                "$<$<CONFIG:DEBUG>:-fno-inline-small-functions>"
                "$<$<CONFIG:DEBUG>:-fno-default-inline>"
                "$<$<CONFIG:DEBUG>:-fno-elide-constructors>"
        )
        TARGET_LINK_LIBRARIES(${target} PRIVATE debug gcov)
    endif()

ENDMACRO()
