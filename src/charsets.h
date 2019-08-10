/* charsets.h -- character set information and mappings

  (c) 1998-2003 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

* Changes 2005-01-09 Jochen Tucht
  This file originates from the Tidy library (tidy.sourceforge.net).
  Dependencies on other parts of the library have been removed to make it
  easily plug into a Win32 application that does not use Tidy elsewhere.
  Runtime-allocated index arrays have been added to improve lookup speed.
*/

#pragma once

#ifdef __cplusplus
#define extern extern "C"
#endif

extern unsigned GetEncodingIdFromName(const char *name);
extern unsigned GetEncodingIdFromCodePage(unsigned cp);
extern unsigned GetEncodingCodePageFromName(const char *name);
extern unsigned GetEncodingCodePageFromId(unsigned id);
extern const char *GetEncodingNameFromId(unsigned id);
extern const char *GetEncodingNameFromCodePage(unsigned cp);

extern void charsets_init(void);
extern void charsets_cleanup(void);

#undef extern
