/* ------------------------------------------------------------ *
 * 																*
 * file:        log.h	                                    	*
 * purpose:     Provides high level logs APIs to user app	    *
 * author:      Sachin Rajput, Harsh Dave                       *
 *                                                              *
 * ------------------------------------------------------------ */
#ifndef INC_LOG_H_
#define INC_LOG_H_

#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"

#define BOOT_LOG(args) printf(KGRN args KNRM)
#define BOOT_ERR(args) printf(KRED args KNRM)
#define APP_LOG(args) printf(args)

#endif /* INC_LOG_H_ */
