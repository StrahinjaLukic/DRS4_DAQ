include(${ROOT_USE_FILE})
include_directories( include ../drs4data/include )

ROOT_GENERATE_DICTIONARY( monitorDict MonitorFrame.h LINKDEF LinkDef.hh )

add_library ( drs4monitor SHARED src/WaveProcessor.cxx src/MonitorFrame.cxx monitorDict.cxx )

target_include_directories(drs4monitor PUBLIC include ../drs4data/include ../drs4daq/include ${DRS4_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS} )
target_link_libraries ( drs4monitor PRIVATE drs4 drs4data ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})

install( TARGETS drs4monitor LIBRARY DESTINATION lib )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/monitorDict_rdict.pcm DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
