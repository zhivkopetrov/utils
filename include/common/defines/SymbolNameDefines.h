#ifndef UTILS_INCLUDE_COMMON_DEFINES_SYMBOLNAMEDEFINES_H_
#define UTILS_INCLUDE_COMMON_DEFINES_SYMBOLNAMEDEFINES_H_

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

// Forward declarations

#if defined(__WIN32__) || defined(__WINRT__)
#define SYMBOL_EXPORT __declspec(dllexport)
#define SYMBOL_IMPORT __declspec(dllimport)
#else  // linux and mac
#if defined(__GNUC__) && __GNUC__ >= 4
#define SYMBOL_EXPORT __attribute__((__visibility__("default")))
#define SYMBOL_IMPORT
#else
#define SYMBOL_EXPORT
#define SYMBOL_IMPORT
#endif
#endif

#endif /* UTILS_INCLUDE_COMMON_DEFINES_SYMBOLNAMEDEFINES_H_ */
