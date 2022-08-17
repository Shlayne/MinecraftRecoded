#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#if defined(_WIN32) && (defined(UNICODE) || defined(_UNICODE))
	#define STBIW_WINDOWS_UTF8
#endif
#include "stb_image_write.h"
