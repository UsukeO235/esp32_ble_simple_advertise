set( include_dirs
	$ENV{IDF_PATH}/components/bt/include
	$ENV{IDF_PATH}/components/bt/host/bluedroid/api/include/api
)

idf_component_register( SRCS "main.cpp"
	INCLUDE_DIRS "." ${include_dirs}
)