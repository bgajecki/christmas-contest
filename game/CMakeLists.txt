
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Gameplay GAMEPLAY)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Intro INTRO)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Menu MENU)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Outro OUTRO)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Scene SCENE)

set (GAME_SRCS
	${GAMEPLAY}
	${INTRO}
	${MENU}
	${OUTRO}
	${SCENE}
	PARENT_SCOPE
)