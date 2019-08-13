#pragma once


struct DIFFOPTIONS;
class QOptionsMgr;

namespace Options { namespace DiffOptions {

void SetDefaults(QOptionsMgr *pOptionsMgr);
void Load(const QOptionsMgr *pOptionsMgr, DIFFOPTIONS& options);
void Save(QOptionsMgr *pOptionsMgr, const DIFFOPTIONS& options);

}}
