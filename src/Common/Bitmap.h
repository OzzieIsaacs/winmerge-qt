/** 
 * @file  Bitmap.h
 *
 * @brief Declaration file for Bitmap helper functions.
 *
 */
#pragma once

class CBitmap;
class CDC;
class CRect;

CBitmap *CopyRectToBitmap(CDC *pDC, const CRect & rect);
void DrawBitmap(CDC *pDC, int x, int y, CBitmap *pBitmap);
CBitmap *GetDarkenedBitmap(CDC *pDC, CBitmap *pBitmap);
bool GrayScale(CBitmap *pBitmap);
