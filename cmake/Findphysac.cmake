if (NOT physac_FOUND)
	include(ExternalProject)
	ExternalProject_Add(physac
		PREFIX extern
		GIT_REPOSITORY https://github.com/victorfisac/Physac
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		UPDATE_COMMAND ""
		INSTALL_COMMAND ""
	)
	ExternalProject_Get_Property(physac source_dir)

	SET(PHYSAC_INCLUDE_DIR ${source_dir}/src)
	SET(physac_FOUND TRUE)
endif()