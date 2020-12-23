// preprocessor macros to import or export functions

#ifdef ADD_EXPORTS
    #define ADDAPI __declspec(dllexport)
#else
    #define ADDAPI __declspec(dllimport)
#endif

// calling convention
#define ADDCALL __cdecl

// Make sure linkage is C style under C++ compilers
#ifdef __cplusplus
extern "C" {
#endif

    ADDAPI int ADDCALL Add(int a, int b);

#ifdef __cplusplus
} // __cplusplus defined
#endif