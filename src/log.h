
#ifndef __LOG_H__
#define __LOG_H__

#define DBG(msg) fprintf(stdout, "%s\n", msg)
#define DBGF(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)

#define ERR(msg) fprintf(stderr, "%s\n", msg)
#define ERRF(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

#endif // __LOG_H__
