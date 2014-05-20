#ifndef MYDEBUG_H_
#define MYDEBUG_H_

#define __debug__  
  
#ifdef __debug__  
#define debug(format,...) printf("file: "__file__", line: %05d: "format"\n", __line__, ##__va_args__)  
#else  
#define debug(format,...)  
#endif  

#endif
