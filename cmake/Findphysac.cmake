if (NOT physac_FOUND)
	include(ExternalProject)
	ExternalProject_Add(physac
		PREFIX extern
		URL https://github.com/victorfisac/Physac
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		UPDATE_COMMAND ""
		INSTALL_COMMAND ""
	)
	SET(PHYSAC_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/extern/src)
	SET(physac_FOUND TRUE)
endif()