cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(lzw LANGUAGES C)

# Definición de la biblioteca lzw
add_library(lzw
  "src/darray.c"
  "src/lzw.c"
  "src/lzw_bits.c"
  "src/lzw_table.c"
)

# Dependencias y opciones de compilación para lzw
target_include_directories(lzw PUBLIC "src/")
target_compile_options(lzw
  PRIVATE "-std=c11"
  PRIVATE "-Wall"
  PRIVATE "-Wconversion"
)

# Definición del ejecutable para compresión
add_executable(lzw_comprimir "src/comprimir.c")
target_link_libraries(lzw_comprimir PRIVATE lzw)


