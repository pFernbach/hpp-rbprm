SET(${PROJECT_NAME}_PROJECTION_HEADERS
  projection.hh
  )

INSTALL(FILES
  ${${PROJECT_NAME}_PROJECTION_HEADERS}
  DESTINATION include/hpp/rbprm/projection
  )
