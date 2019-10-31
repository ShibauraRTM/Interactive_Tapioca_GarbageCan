set(comp_srcs CreateTapioca.cpp MultiBodySoftContact.cpp) #
set(standalone_srcs CreateTapiocaComp.cpp MultiBodySoftContact.cpp) #

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT") #
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd") #

if(${OPENRTM_VERSION_MAJOR} LESS 2)
  set(OPENRTM_CFLAGS ${OPENRTM_CFLAGS} ${OMNIORB_CFLAGS})
  set(OPENRTM_INCLUDE_DIRS ${OPENRTM_INCLUDE_DIRS} ${OMNIORB_INCLUDE_DIRS})
  set(OPENRTM_LIBRARY_DIRS ${OPENRTM_LIBRARY_DIRS} ${OMNIORB_LIBRARY_DIRS})
endif()

if (DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif (DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/idl)
include_directories(${OPENRTM_INCLUDE_DIRS})
add_definitions(${OPENRTM_CFLAGS})
include_directories("C:/Users/enshu/Downloads/bullet3-2.88/bullet3-2.88/src") #

add_definitions(${OPENRTM_CFLAGS} -DBT_THREADSAFE=1 -DBT_USE_DOUBLE_PRECISION) #

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS} "C:/Users/enshu/Downloads/bullet3-2.88/bullet3-2.88/bin") #

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
 add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} glu32.lib; opengl32.lib; optimized Bullet3Common_vs2010_x64_release.lib; optimized BulletCollision_vs2010_x64_release.lib; optimized BulletDynamics_vs2010_x64_release.lib; optimized LinearMath_vs2010_x64_release.lib; optimized OpenGL_Window_vs2010_x64_release.lib; optimized BulletExampleBrowserLib_vs2010_x64_release.lib; debug Bullet3Common_vs2010_x64_debug.lib; debug BulletCollision_vs2010_x64_debug.lib; debug BulletDynamics_vs2010_x64_debug.lib; debug LinearMath_vs2010_x64_debug.lib; debug OpenGL_Window_vs2010_x64_debug.lib; debug BulletExampleBrowserLib_vs2010_x64_debug.lib; ${OPENRTM_LIBRARIES}) #

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
add_dependencies(${PROJECT_NAME}Comp ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME}Comp glu32.lib; opengl32.lib; optimized Bullet3Common_vs2010_x64_release.lib; optimized BulletCollision_vs2010_x64_release.lib; optimized BulletDynamics_vs2010_x64_release.lib; optimized LinearMath_vs2010_x64_release.lib; optimized OpenGL_Window_vs2010_x64_release.lib; optimized BulletExampleBrowserLib_vs2010_x64_release.lib; debug Bullet3Common_vs2010_x64_debug.lib; debug BulletCollision_vs2010_x64_debug.lib; debug BulletDynamics_vs2010_x64_debug.lib; debug LinearMath_vs2010_x64_debug.lib; debug OpenGL_Window_vs2010_x64_debug.lib; debug BulletExampleBrowserLib_vs2010_x64_debug.lib; ${OPENRTM_LIBRARIES}) #

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${INSTALL_PREFIX} COMPONENT component
    LIBRARY DESTINATION ${INSTALL_PREFIX} COMPONENT component
    ARCHIVE DESTINATION ${INSTALL_PREFIX} COMPONENT component)

install(FILES ${PROJECT_SOURCE_DIR}/RTC.xml DESTINATION ${INSTALL_PREFIX}
        COMPONENT component)
