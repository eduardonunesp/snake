
#ifndef __ENUMS_H__
#define __ENUMS_H__

#define CHECKER_INIT(result) game_status_e g_result = result

#define CHECKER_RUN(checker) {           \
	g_result = checker;                    \
	if (g_result != GAME_STATUS_SUCCESS) { \
		return g_result;                     \
	}                                      \
}

#define CHECKER_END() return g_result;

typedef enum {
	GAME_STATUS_SUCCESS,
	GAME_STATUS_FAILED,
	GAME_STATUS_INVALID_MEMORY,
	GAME_STATUS_VIDEO_FAILED,
	GAME_STATUS_FAILE_LOAD_SURFACE,
	GAME_STATUS_MEMORY_ALLOC_FAILED,
	GAME_STATUS_FAILE_LOAD_TEXTURE,
	GAME_STATUS_BAD_ALLOC,
} game_status_e;

#endif // __ENUMS_H__
