INCLUDE(ispc)

MACRO(ADD_ENGINE_LIBRARY name)
	SET(NAME_UPPERCASE "")
	STRING(TOUPPER ${name} NAME_UPPERCASE)

	SET(PRIVATE_SOURCES "")
	SET(PUBLIC_SOURCES "")
	SET(TEST_SOURCES "")
	SET(ISPC_SOURCES "")

	FOREACH(src ${ARGN})
		SET(PRIVATE_MATCH FALSE)
		SET(TEST_MATCH FALSE)
		SET(ISPC_MATCH FALSE)
		STRING(REGEX MATCH "^private/" PRIVATE_MATCH "${src}")
		STRING(REGEX MATCH "^tests/" TEST_MATCH "${src}")
		STRING(REGEX MATCH "^ispc/" ISPC_MATCH "${src}")

		IF(PRIVATE_MATCH)
			SET(PRIVATE_SOURCES ${PRIVATE_SOURCES} ${src})
		ELSEIF(TEST_MATCH)
			SET(TEST_SOURCES ${TEST_SOURCES} ${src})
		ELSEIF(ISPC_MATCH)
			SET(ISPC_SOURCES ${ISPC_SOURCES} ${src})
		ELSE()
			SET(PUBLIC_SOURCES ${PUBLIC_SOURCES} ${src})
		ENDIF()
	ENDFOREACH()

	MESSAGE("Adding Engine Library: ${name}")

	# Setup engine library.
	ADD_ISPC_LIBRARY(${name} SHARED ${PRIVATE_SOURCES} ${PUBLIC_SOURCES} ${ISPC_SOURCES})

	SOURCE_GROUP("Private" FILES ${PRIVATE_SOURCES})
	SOURCE_GROUP("Public" FILES ${PUBLIC_SOURCES})
	SOURCE_GROUP("ISPC" FILES ${ISPC_SOURCES})

	SET_TARGET_PROPERTIES(${name} PROPERTIES FOLDER Libraries)

	TARGET_COMPILE_DEFINITIONS(${name} PRIVATE ${NAME_UPPERCASE}_EXPORT=1)

	ADD_ISPC_EXECUTABLE(${name}_test ${TEST_SOURCES} ${ISPC_SOURCES})
	TARGET_LINK_LIBRARIES(${name}_test ${name})
	TARGET_INCLUDE_DIRECTORIES(${name}_test PRIVATE "${ENGINE_3RDPARTY_PATH}/Catch/include")

	SET_TARGET_PROPERTIES(${name}_test PROPERTIES FOLDER Tests)
	SOURCE_GROUP("Tests" FILES ${SOURCES_TESTS})

ENDMACRO()

MACRO(ADD_ENGINE_PLUGIN name)
	SET(NAME_UPPERCASE "")
	STRING(TOUPPER ${name} NAME_UPPERCASE)

	SET(PRIVATE_SOURCES "")
	SET(PUBLIC_SOURCES "")
	SET(TEST_SOURCES "")
	SET(ISPC_SOURCES "")

	FOREACH(src ${ARGN})
		SET(PRIVATE_MATCH FALSE)
		SET(TEST_MATCH FALSE)
		SET(ISPC_MATCH FALSE)
		STRING(REGEX MATCH "^private/" PRIVATE_MATCH "${src}")
		STRING(REGEX MATCH "^tests/" TEST_MATCH "${src}")
		STRING(REGEX MATCH "^ispc/" ISPC_MATCH "${src}")

		IF(PRIVATE_MATCH)
			SET(PRIVATE_SOURCES ${PRIVATE_SOURCES} ${src})
		ELSEIF(TEST_MATCH)
			SET(TEST_SOURCES ${TEST_SOURCES} ${src})
		ELSEIF(ISPC_MATCH)
			SET(ISPC_SOURCES ${ISPC_SOURCES} ${src})
		ELSE()
			SET(PUBLIC_SOURCES ${PUBLIC_SOURCES} ${src})
		ENDIF()
	ENDFOREACH()

	MESSAGE("Adding Engine Plugin: ${name}")

	# Setup engine plugin.
	ADD_ISPC_LIBRARY(${name} SHARED ${PRIVATE_SOURCES} ${PUBLIC_SOURCES} ${TEST_SOURCES})

	SOURCE_GROUP("Private" FILES ${PRIVATE_SOURCES})
	SOURCE_GROUP("Public" FILES ${PUBLIC_SOURCES})
	SOURCE_GROUP("Test" FILES ${TEST_SOURCES})
	SOURCE_GROUP("ISPC" FILES ${ISPC_SOURCES})

	IF(NOT TEST_SOURCES)
		SET_TARGET_PROPERTIES(${name} PROPERTIES FOLDER Libraries/Plugins)
	ELSE()
		SET_TARGET_PROPERTIES(${name} PROPERTIES FOLDER Tests/Plugins)
	ENDIF()

	TARGET_COMPILE_DEFINITIONS(${name} PRIVATE ${NAME_UPPERCASE}_EXPORT=1)	
ENDMACRO()

MACRO(ADD_ENGINE_EXECUTABLE name)
	SET(NAME_UPPERCASE "")
	STRING(TOUPPER ${name} NAME_UPPERCASE)

	SET(PRIVATE_SOURCES "")
	SET(PUBLIC_SOURCES "")
	SET(ISPC_SOURCES "")

	FOREACH(src ${ARGN})
		SET(PRIVATE_MATCH FALSE)
		SET(ISPC_MATCH FALSE)
		STRING(REGEX MATCH "^private/" PRIVATE_MATCH "${src}")
		STRING(REGEX MATCH "^ispc/" ISPC_MATCH "${src}")

		IF(PRIVATE_MATCH)
			SET(PRIVATE_SOURCES ${PRIVATE_SOURCES} ${src})
		ELSEIF(ISPC_MATCH)
			SET(ISPC_SOURCES ${ISPC_SOURCES} ${src})
		ELSE()
			SET(PUBLIC_SOURCES ${PUBLIC_SOURCES} ${src})
		ENDIF()
	ENDFOREACH()

	MESSAGE("Adding Engine Executable: ${name}")

	# Setup engine library.
	ADD_ISPC_EXECUTABLE(${name} ${PRIVATE_SOURCES} ${PUBLIC_SOURCES} ${ISPC_SOURCES})

	SOURCE_GROUP("Private" FILES ${PRIVATE_SOURCES})
	SOURCE_GROUP("Public" FILES ${PUBLIC_SOURCES})
	SOURCE_GROUP("ISPC" FILES ${ISPC_SOURCES})

	SET_TARGET_PROPERTIES(${name} PROPERTIES FOLDER Executables)
ENDMACRO()
