#ifndef _logging_utils_h
#define _logging_utils_h

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
void init_loggers(void);
void destroy_loggers(void);
void log_info(char *msg_id, char *fmt, ...);
void log_warning(char *msg_id, char *fmt, ...);
void log_error(char *msg_id, char *fmt, ...);

#endif
