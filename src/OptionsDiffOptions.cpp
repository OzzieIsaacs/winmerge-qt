/** 
 * @file  OptionsDiffOptions.cpp
 *
 * @brief Implementation for OptionsDiffOptions class.
 */
#define NOMINMAX
#include "OptionsDiffOptions.h"
#include "CompareOptions.h"
#include "OptionsDef.h"
#include "QOptionsMgr.h"

namespace Options {
	namespace DiffOptions {

		/**
		 * @brief Set default diff option values.
		 */
		void SetDefaults(QOptionsMgr *pOptionsMgr)
		{
			pOptionsMgr->setDefault(OPT_CMP_IGNORE_WHITESPACE, (int)0);
			pOptionsMgr->setDefault(OPT_CMP_IGNORE_BLANKLINES, false);
			pOptionsMgr->setDefault(OPT_CMP_FILTER_COMMENTLINES, false);
			pOptionsMgr->setDefault(OPT_CMP_IGNORE_CASE, false);
			pOptionsMgr->setDefault(OPT_CMP_IGNORE_EOL, false);
		}

		void Load(const QOptionsMgr *pOptionsMgr, DIFFOPTIONS& options)
		{
			options.nIgnoreWhitespace = pOptionsMgr->value(OPT_CMP_IGNORE_WHITESPACE).toInt();
			options.bIgnoreBlankLines = pOptionsMgr->value(OPT_CMP_IGNORE_BLANKLINES).toBool();
			options.bFilterCommentsLines = pOptionsMgr->value(OPT_CMP_FILTER_COMMENTLINES).toBool();
			options.bIgnoreCase = pOptionsMgr->value(OPT_CMP_IGNORE_CASE).toBool();
			options.bIgnoreEol = pOptionsMgr->value(OPT_CMP_IGNORE_EOL).toBool();
		}

		void Save(QOptionsMgr *pOptionsMgr, const DIFFOPTIONS& options)
		{
			pOptionsMgr->setValue(OPT_CMP_IGNORE_WHITESPACE, options.nIgnoreWhitespace);
			pOptionsMgr->setValue(OPT_CMP_IGNORE_BLANKLINES, options.bIgnoreBlankLines);
			pOptionsMgr->setValue(OPT_CMP_FILTER_COMMENTLINES, options.bFilterCommentsLines);
			pOptionsMgr->setValue(OPT_CMP_IGNORE_CASE, options.bIgnoreCase);
			pOptionsMgr->setValue(OPT_CMP_IGNORE_EOL, options.bIgnoreEol);
		}

	}
}
