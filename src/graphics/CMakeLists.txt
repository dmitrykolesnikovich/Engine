SET(SOURCES_PUBLIC 
	"dll.h"
	"factory.h"
	"texture.h"
)

SET(SOURCES_PRIVATE 
	"private/factory.cpp"
	"private/texture.cpp"
)

SET(SOURCES_TESTS
	"tests/converter_tests.cpp"
	"tests/test_entry.cpp"
)

ADD_ENGINE_LIBRARY(graphics ${SOURCES_PUBLIC} ${SOURCES_PRIVATE} ${SOURCES_TESTS})
TARGET_LINK_LIBRARIES(graphics gpu job math resource)
TARGET_LINK_LIBRARIES(graphics_test client)

# Plugins
SET(SOURCES_TEXTURE_CONVERTER
	"converters/converter_texture.cpp"
	"converters/dds.h"
	"converters/dds.cpp"
	"converters/image.h"
	"converters/image.cpp"
)

INCLUDE_DIRECTORIES(
	# 3rd party includes.
	"${ENGINE_3RDPARTY_PATH}/stb"
	"${ENGINE_3RDPARTY_PATH}/squish"
)

ADD_LIBRARY(converter_graphics_texture SHARED ${SOURCES_TEXTURE_CONVERTER})
SET_TARGET_PROPERTIES(converter_graphics_texture PROPERTIES FOLDER Libraries/Plugins)
TARGET_LINK_LIBRARIES(converter_graphics_texture core graphics resource squish)
SOURCE_GROUP("Public" FILES ${SOURCES_TEXTURE_CONVERTER})

