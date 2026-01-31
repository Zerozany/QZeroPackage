target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    QZeroPackage
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/utf-8"
        "/FS"
    )
endif()
