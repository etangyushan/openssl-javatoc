#define __debug__  
  
#ifdef __debug__  
#define debug(format,...) printf("file: "__FILE__", line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)  
#else  
#define debug(format,...)  
#endif  


