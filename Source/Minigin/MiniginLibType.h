#pragma once

#ifdef MINIGIN_EXPORT
// dll library uses this one
#define MINIGIN_ENTRY __declspec(dllexport)
#else
#ifdef MINIGIN_IMPORT
// dll client uses this one
#define MINIGIN_ENTRY __declspec(dllimport)
#else
// this one's used for the statically linked library
#define MINIGIN_ENTRY
#endif
#endif
