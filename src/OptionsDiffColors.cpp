/** 
 * @file  OptionsDiffColors.cpp
 *
 * @brief Implementation for OptionsDiffColors class.
 */
#include "OptionsDiffColors.h"
#include "OptionsDef.h"
#include "OptionsMgr.h"

#ifndef RGB
#define RGB(r,g,b)      (unsigned long)( 0x00ff & (r) | (0xff00 & (g<<8))|( 0x00ff0000 & (b <<16)))
#endif
namespace Options {
	namespace DiffColors {

		void SetDefaults(QOptionsMgr *pOptionsMgr)
		{
			pOptionsMgr->setDefault(OPT_CLR_DIFF, (int)RGB(239,203,5));
			pOptionsMgr->setDefault(OPT_CLR_DIFF_DELETED, (int)RGB(192, 192, 192));
			pOptionsMgr->setDefault(OPT_CLR_DIFF_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_DIFF, (int)RGB(239,119,116));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_DIFF_DELETED, (int)RGB(240, 192, 192));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_DIFF_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_TRIVIAL_DIFF, (int)RGB(251,242,191));
			pOptionsMgr->setDefault(OPT_CLR_TRIVIAL_DIFF_DELETED, (int)RGB(233,233,233));
			pOptionsMgr->setDefault(OPT_CLR_TRIVIAL_DIFF_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_MOVEDBLOCK, (int)RGB(228,155,82));
			pOptionsMgr->setDefault(OPT_CLR_MOVEDBLOCK_DELETED, (int)RGB(192, 192, 192));
			pOptionsMgr->setDefault(OPT_CLR_MOVEDBLOCK_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_MOVEDBLOCK, (int)RGB(248,112,78));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_MOVEDBLOCK_DELETED, (int)RGB(252, 181, 163));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_MOVEDBLOCK_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_SNP, (int)RGB(251,250,223));
			pOptionsMgr->setDefault(OPT_CLR_SNP_DELETED, (int)RGB(233, 233, 233));
			pOptionsMgr->setDefault(OPT_CLR_SNP_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_SNP, (int)RGB(239,183,180));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_SNP_DELETED, (int)RGB(240, 224, 224));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_SNP_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_WORDDIFF, (int)RGB(241,226,173));
			pOptionsMgr->setDefault(OPT_CLR_WORDDIFF_DELETED, (int)RGB(255,170,130));
			pOptionsMgr->setDefault(OPT_CLR_WORDDIFF_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_WORDDIFF, (int)RGB(255,160,160));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_WORDDIFF_DELETED, (int)RGB(200,129,108));
			pOptionsMgr->setDefault(OPT_CLR_SELECTED_WORDDIFF_TEXT, (int)RGB(0,0,0));
			pOptionsMgr->setDefault(OPT_CLR_DEFAULT_TEXT_COLORING, true);
		}

		void Load(const QOptionsMgr *pOptionsMgr, COLORSETTINGS& colors)
		{
			colors.clrDiff = pOptionsMgr->value(OPT_CLR_DIFF).toInt();
			colors.clrSelDiff = pOptionsMgr->value(OPT_CLR_SELECTED_DIFF).toInt();
			colors.clrDiffDeleted = pOptionsMgr->value(OPT_CLR_DIFF_DELETED).toInt();
			colors.clrSelDiffDeleted = pOptionsMgr->value(OPT_CLR_SELECTED_DIFF_DELETED).toInt();
			colors.clrDiffText = pOptionsMgr->value(OPT_CLR_DIFF_TEXT).toInt();
			colors.clrSelDiffText = pOptionsMgr->value(OPT_CLR_SELECTED_DIFF_TEXT).toInt();
			colors.clrTrivial = pOptionsMgr->value(OPT_CLR_TRIVIAL_DIFF).toInt();
			colors.clrTrivialDeleted = pOptionsMgr->value(OPT_CLR_TRIVIAL_DIFF_DELETED).toInt();
			colors.clrTrivialText = pOptionsMgr->value(OPT_CLR_TRIVIAL_DIFF_TEXT).toInt();
			colors.clrMoved = pOptionsMgr->value(OPT_CLR_MOVEDBLOCK).toInt();
			colors.clrMovedDeleted = pOptionsMgr->value(OPT_CLR_MOVEDBLOCK_DELETED).toInt();
			colors.clrMovedText = pOptionsMgr->value(OPT_CLR_MOVEDBLOCK_TEXT).toInt();
			colors.clrSelMoved = pOptionsMgr->value(OPT_CLR_SELECTED_MOVEDBLOCK).toInt();
			colors.clrSelMovedDeleted = pOptionsMgr->value(OPT_CLR_SELECTED_MOVEDBLOCK_DELETED).toInt();
			colors.clrSelMovedText = pOptionsMgr->value(OPT_CLR_SELECTED_MOVEDBLOCK_TEXT).toInt();
			colors.clrSNP = pOptionsMgr->value(OPT_CLR_SNP).toInt();
			colors.clrSNPDeleted = pOptionsMgr->value(OPT_CLR_SNP_DELETED).toInt();
			colors.clrSNPText = pOptionsMgr->value(OPT_CLR_SNP_TEXT).toInt();
			colors.clrSelSNP = pOptionsMgr->value(OPT_CLR_SELECTED_SNP).toInt();
			colors.clrSelSNPDeleted = pOptionsMgr->value(OPT_CLR_SELECTED_SNP_DELETED).toInt();
			colors.clrSelSNPText = pOptionsMgr->value(OPT_CLR_SELECTED_SNP_TEXT).toInt();
			colors.clrWordDiff = pOptionsMgr->value(OPT_CLR_WORDDIFF).toInt();
			colors.clrWordDiffDeleted = pOptionsMgr->value(OPT_CLR_WORDDIFF_DELETED).toInt();
			colors.clrSelWordDiff = pOptionsMgr->value(OPT_CLR_SELECTED_WORDDIFF).toInt();
			colors.clrSelWordDiffDeleted = pOptionsMgr->value(OPT_CLR_SELECTED_WORDDIFF_DELETED).toInt();
			colors.clrWordDiffText = pOptionsMgr->value(OPT_CLR_WORDDIFF_TEXT).toInt();
			colors.clrSelWordDiffText = pOptionsMgr->value(OPT_CLR_SELECTED_WORDDIFF_TEXT).toInt();
		}

		void Save(QOptionsMgr *pOptionsMgr, const COLORSETTINGS& colors)
		{
			pOptionsMgr->setValue(OPT_CLR_DIFF, (int)colors.clrDiff);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_DIFF, (int)colors.clrSelDiff);
			pOptionsMgr->setValue(OPT_CLR_DIFF_DELETED, (int)colors.clrDiffDeleted);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_DIFF_DELETED, (int)colors.clrSelDiffDeleted);
			pOptionsMgr->setValue(OPT_CLR_DIFF_TEXT, (int)colors.clrDiffText);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_DIFF_TEXT, (int)colors.clrSelDiffText);
			pOptionsMgr->setValue(OPT_CLR_TRIVIAL_DIFF, (int)colors.clrTrivial);
			pOptionsMgr->setValue(OPT_CLR_TRIVIAL_DIFF_DELETED, (int)colors.clrTrivialDeleted);
			pOptionsMgr->setValue(OPT_CLR_TRIVIAL_DIFF_TEXT, (int)colors.clrTrivialText);
			pOptionsMgr->setValue(OPT_CLR_MOVEDBLOCK, (int)colors.clrMoved);
			pOptionsMgr->setValue(OPT_CLR_MOVEDBLOCK_DELETED, (int)colors.clrMovedDeleted);
			pOptionsMgr->setValue(OPT_CLR_MOVEDBLOCK_TEXT, (int)colors.clrMovedText);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_MOVEDBLOCK, (int)colors.clrSelMoved);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_MOVEDBLOCK_DELETED, (int)colors.clrSelMovedDeleted);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_MOVEDBLOCK_TEXT, (int)colors.clrSelMovedText);
			pOptionsMgr->setValue(OPT_CLR_SNP, (int)colors.clrSNP);
			pOptionsMgr->setValue(OPT_CLR_SNP_DELETED, (int)colors.clrSNPDeleted);
			pOptionsMgr->setValue(OPT_CLR_SNP_TEXT, (int)colors.clrSNPText);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_SNP, (int)colors.clrSelSNP);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_SNP_DELETED, (int)colors.clrSelSNPDeleted);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_SNP_TEXT, (int)colors.clrSelSNPText);
			pOptionsMgr->setValue(OPT_CLR_WORDDIFF, (int)colors.clrWordDiff);
			pOptionsMgr->setValue(OPT_CLR_WORDDIFF_DELETED, (int)colors.clrWordDiffDeleted);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_WORDDIFF, (int)colors.clrSelWordDiff);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_WORDDIFF_DELETED, (int)colors.clrSelWordDiffDeleted);
			pOptionsMgr->setValue(OPT_CLR_WORDDIFF_TEXT, (int)colors.clrWordDiffText);
			pOptionsMgr->setValue(OPT_CLR_SELECTED_WORDDIFF_TEXT, (int)colors.clrSelWordDiffText);
		}
	}
}
