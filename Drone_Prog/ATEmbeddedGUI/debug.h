#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define ENTER_FCT()  fprintf(stderr, "[DEBUG] In  --> %s\n", __FUNCTION__);
#define EXIT_FCT()   fprintf(stderr, "[DEBUG] Out <-- %s\n", __FUNCTION__);
#define PRINT_LOG(mess, ...) fprintf(stderr, "[DEBUG] %s : " mess "\n", __FUNCTION__, ##__VA_ARGS__);
#else
#define ENTER_FCT()
#define EXIT_FCT()
#define PRINT_LOG(mess, ...) 
#endif

#define ERROR_LOG(mess) fprintf(stderr, "[ERROR] (%s:%d) in function %s : "mess"\n", __FILE__, __LINE__, __FUNCTION__);

#endif //DEBUG_H

#ifdef __cplusplus
}
#endif
