set(SRC ../includes)

AUX_SOURCE_DIRECTORY(${SRC}/ TARGET_SRC)
add_library(includes OPF.c ${TARGET_SRC})
