#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define ENTER_FCT()  fprintf(stderr, "[DEBUG] In  --> %s\n", __FUNCTION__);
#define EXIT_FCT()   fprintf(stderr, "[DEBUG] Out <-- %s\n", __FUNCTION__);
#define PRINT_LOG(mess) fprintf(stderr, "[DEBUG] " mess "\n");
#else
#define ENTER_FCT(fct)
#define EXIT_FCT(fct)
#define PRINT_LOG(mess)
#endif

#define ERROR_LOG(mess) fprintf(stderr, "[ERROR] (%s:%d) "mess"\n", __FILE__, __LINE__);

#endif //DEBUG_H
