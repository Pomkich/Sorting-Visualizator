add_executable(main 
    ./cpp/GraphicSort.cpp 
    ./cpp/main.cpp 
)

set(MY_SFML_PATH D:\\Development\\Libs\\SFML-2.6.0\\lib\\cmake\\SFML)
set(SFML_DIR ${MY_SFML_PATH})
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)
target_include_directories(main PRIVATE ./hdr)