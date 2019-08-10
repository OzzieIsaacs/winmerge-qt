/** 
 * @file  OptionsDef.h
 *
 * @brief Constants for option-names
 */
#pragma once

// #include "UnicodeString.h"
#include <QString>


// User's language
const QString OPT_SELECTED_LANGUAGE ("Locale/LanguageId");

// View-menu
const QString OPT_SHOW_UNIQUE_LEFT ("Settings/ShowUniqueLeft");
const QString OPT_SHOW_UNIQUE_MIDDLE ("Settings/ShowUniqueMiddle");
const QString OPT_SHOW_UNIQUE_RIGHT ("Settings/ShowUniqueRight");
const QString OPT_SHOW_DIFFERENT ("Settings/ShowDifferent");
const QString OPT_SHOW_IDENTICAL ("Settings/ShowIdentical");
const QString OPT_SHOW_BINARIES ("Settings/ShowBinaries");
const QString OPT_SHOW_SKIPPED ("Settings/ShowSkipped");
const QString OPT_SHOW_DIFFERENT_LEFT_ONLY ("Settings/ShowDifferentLeftOnly");
const QString OPT_SHOW_DIFFERENT_MIDDLE_ONLY ("Settings/ShowDifferentMiddleOnly");
const QString OPT_SHOW_DIFFERENT_RIGHT_ONLY ("Settings/ShowDifferentRightOnly");
const QString OPT_TREE_MODE ("Settings/TreeMode");

// Show/hide toolbar/statusbar/tabbar
const QString OPT_SHOW_TOOLBAR ("Settings/ShowToolbar");
const QString OPT_SHOW_STATUSBAR ("Settings/ShowStatusbar");
const QString OPT_SHOW_TABBAR ("Settings/ShowTabbar");
const QString OPT_TOOLBAR_SIZE ("Settings/ToolbarSize");
const QString OPT_RESIZE_PANES ("Settings/AutoResizePanes");

const QString OPT_SYNTAX_HIGHLIGHT ("Settings/HiliteSyntax");
const QString OPT_VIEW_WHITESPACE ("Settings/ViewWhitespace");
const QString OPT_CONNECT_MOVED_BLOCKS ("Settings/ConnectMovedBlocks");
const QString OPT_SCROLL_TO_FIRST ("Settings/ScrollToFirst");

// Difference (in-line) highlight
const QString OPT_WORDDIFF_HIGHLIGHT ("Settings/HiliteWordDiff");
const QString OPT_BREAK_ON_WORDS ("Settings/BreakOnWords");
const QString OPT_BREAK_TYPE ("Settings/BreakType");
const QString OPT_BREAK_SEPARATORS ("Settings/HiliteBreakSeparators");

// Backup options
const QString OPT_BACKUP_FOLDERCMP ("Backup/EnableFolder");
const QString OPT_BACKUP_FILECMP ("Backup/EnableFile");
const QString OPT_BACKUP_LOCATION ("Backup/Location");
const QString OPT_BACKUP_GLOBALFOLDER ("Backup/GlobalFolder");
const QString OPT_BACKUP_ADD_BAK ("Backup/NameAddBak");
const QString OPT_BACKUP_ADD_TIME ("Backup/NameAddTime");

const QString OPT_DIRVIEW_SORT_COLUMN ("Settings/DirViewSortCol");
const QString OPT_DIRVIEW_SORT_COLUMN3 ("Settings/DirViewSortCol3");
const QString OPT_DIRVIEW_SORT_ASCENDING ("Settings/DirViewSortAscending");
const QString OPT_DIRVIEW_EXPAND_SUBDIRS ("Settings/DirViewExpandSubdirs");

// Window/Pane
const QString OPT_ACTIVE_FRAME_MAX ("Settings/ActiveFrameMax");
const QString OPT_ACTIVE_PANE ("Settings/ActivePane");

// Folder Compare Report
const QString OPT_REPORTFILES_REPORTTYPE ("ReportFiles/ReportType");
const QString OPT_REPORTFILES_COPYTOCLIPBOARD ("ReportFiles/CopyToClipboard");
const QString OPT_REPORTFILES_INCLUDEFILECMPREPORT ("ReportFiles/IncludeFileCmpReport");

// File compare
const QString OPT_AUTOMATIC_RESCAN ("Settings/AutomaticRescan");
const QString OPT_ALLOW_MIXED_EOL ("Settings/AllowMixedEOL");
const QString OPT_TAB_SIZE ("Settings/TabSize");
const QString OPT_TAB_TYPE ("Settings/TabType");
const QString OPT_WORDWRAP ("Settings/WordWrap");
const QString OPT_VIEW_LINENUMBERS ("Settings/ViewLineNumbers");
const QString OPT_VIEW_FILEMARGIN ("Settings/ViewFileMargin");
const QString OPT_DIFF_CONTEXT ("Settings/DiffContextV2");

const QString OPT_EXT_EDITOR_CMD ("Settings/alEditor");
const QString OPT_USE_RECYCLE_BIN ("Settings/UseRecycleBin");
const QString OPT_SINGLE_INSTANCE ("Settings/SingleInstance");
const QString OPT_MERGE_MODE ("Settings/MergingMode");
const QString OPT_CLOSE_WITH_ESC ("Settings/CloseWithEsc");
const QString OPT_CLOSE_WITH_OK ("Settings/CloseWithOK");
const QString OPT_VERIFY_OPEN_PATHS ("Settings/VerifyOpenPaths");
const QString OPT_AUTO_COMPLETE_SOURCE ("Settings/AutoCompleteSource");
const QString OPT_IGNORE_SMALL_FILETIME ("Settings/IgnoreSmallFileTime");
const QString OPT_ASK_MULTIWINDOW_CLOSE ("Settings/AskClosingMultipleWindows");
const QString OPT_PRESERVE_FILETIMES ("Settings/PreserveFiletimes");

const QString OPT_CP_DEFAULT_MODE ("Settings/CodepageDefaultMode");
const QString OPT_CP_DEFAULT_CUSTOM ("Settings/CodepageDefaultCustomValue");
const QString OPT_CP_DETECT ("Settings/CodepageDetection");

const QString OPT_PROJECTS_PATH ("Settings/ProjectsPath");
const QString OPT_USE_SYSTEM_TEMP_PATH ("Settings/UseSystemTempPath");
const QString OPT_CUSTOM_TEMP_PATH ("Settings/CustomTempPath");

const QString OPT_SPLIT_HORIZONTALLY ("Settings/SplitHorizontally");

// Color options
// The difference color
const QString OPT_CLR_DIFF ("Settings/DifferenceColor");
// The selected difference color
const QString OPT_CLR_SELECTED_DIFF ("Settings/SelectedDifferenceColor");
// The difference deleted color
const QString OPT_CLR_DIFF_DELETED ("Settings/DifferenceDeletedColor");
// The selected difference deleted color
const QString OPT_CLR_SELECTED_DIFF_DELETED ("Settings/SelectedDifferenceDeletedColor");
// The difference text color
const QString OPT_CLR_DIFF_TEXT ("Settings/DifferenceTextColor");
// The selected difference text color
const QString OPT_CLR_SELECTED_DIFF_TEXT ("Settings/SelectedDifferenceTextColor");
// The ignored lines color
const QString OPT_CLR_TRIVIAL_DIFF ("Settings/TrivialDifferenceColor");
// The ignored and deleted lines color
const QString OPT_CLR_TRIVIAL_DIFF_DELETED ("Settings/TrivialDifferenceDeletedColor");
// The ignored text color
const QString OPT_CLR_TRIVIAL_DIFF_TEXT ("Settings/TrivialDifferenceTextColor");
// The moved block color
const QString OPT_CLR_MOVEDBLOCK ("Settings/MovedBlockColor");
// The moved block deleted lines color
const QString OPT_CLR_MOVEDBLOCK_DELETED ("Settings/MovedBlockDeletedColor");
// The moved block text color
const QString OPT_CLR_MOVEDBLOCK_TEXT ("Settings/MovedBlockTextColor");
// The selected moved block color
const QString OPT_CLR_SELECTED_MOVEDBLOCK ("Settings/SelectedMovedBlockColor");
// The selected moved block deleted lines
const QString OPT_CLR_SELECTED_MOVEDBLOCK_DELETED ("Settings/SelectedMovedBlockDeletedColor");
// The selected moved block text color
const QString OPT_CLR_SELECTED_MOVEDBLOCK_TEXT ("Settings/SelectedMovedBlockTextColor");
// The SNP block color
const QString OPT_CLR_SNP ("Settings/SNPColor");
// The SNP block deleted lines color
const QString OPT_CLR_SNP_DELETED ("Settings/SNPDeletedColor");
// The SNP block text color
const QString OPT_CLR_SNP_TEXT ("Settings/SNPTextColor");
// The selected SNP block color
const QString OPT_CLR_SELECTED_SNP ("Settings/SelectedSNPColor");
// The selected SNP block deleted lines
const QString OPT_CLR_SELECTED_SNP_DELETED ("Settings/SelectedSNPDeletedColor");
// The selected SNP block text color
const QString OPT_CLR_SELECTED_SNP_TEXT ("Settings/SelectedSNPTextColor");
// The word difference color
const QString OPT_CLR_WORDDIFF ("Settings/WordDifferenceColor");
// The word difference deleted color
const QString OPT_CLR_WORDDIFF_DELETED ("Settings/WordDifferenceDeletedColor");
// The word difference text color
const QString OPT_CLR_WORDDIFF_TEXT ("Settings/WordDifferenceTextColor");
// The selected word difference color
const QString OPT_CLR_SELECTED_WORDDIFF ("Settings/SelectedWordDifferenceColor");
// The word difference deleted color
const QString OPT_CLR_SELECTED_WORDDIFF_DELETED ("Settings/SelectedWordDifferenceDeletedColor");
// The selected word difference text color
const QString OPT_CLR_SELECTED_WORDDIFF_TEXT ("Settings/SelectedWordDifferenceTextColor");
// Whether to use default (theme) text colors
const QString OPT_CLR_DEFAULOPT_TEXOPT_COLORING ("Settings/DefaultTextColoring");

// Compare options
const QString OPT_CMP_IGNORE_WHITESPACE ("Settings/IgnoreSpace");
const QString OPT_CMP_IGNORE_BLANKLINES ("Settings/IgnoreBlankLines");
const QString OPT_CMP_FILTER_COMMENTLINES ("Settings/FilterCommentsLines");
const QString OPT_CMP_IGNORE_CASE ("Settings/IgnoreCase");
const QString OPT_CMP_IGNORE_EOL ("Settings/IgnoreEol");
const QString OPT_CMP_IGNORE_CODEPAGE ("Settings/IgnoreCodepage");
const QString OPT_CMP_METHOD ("Settings/CompMethod2");
const QString OPT_CMP_MOVED_BLOCKS ("Settings/MovedBlocks");
const QString OPT_CMP_MATCH_SIMILAR_LINES ("Settings/MatchSimilarLines");
const QString OPT_CMP_STOP_AFTER_FIRST ("Settings/StopAfterFirst");
const QString OPT_CMP_QUICK_LIMIT ("Settings/QuickMethodLimit");
const QString OPT_CMP_COMPARE_THREADS ("Settings/CompareThreads");
const QString OPT_CMP_WALK_UNIQUE_DIRS ("Settings/ScanUnpairedDir");
const QString OPT_CMP_IGNORE_REPARSE_POINTS ("Settings/IgnoreReparsePoints");
const QString OPT_CMP_INCLUDE_SUBDIRS ("Settings/Recurse");

// Image Compare options
const QString OPT_CMP_IMG_FILEPATTERNS ("Settings/ImageFilePatterns");
const QString OPT_CMP_IMG_SHOWDIFFERENCES ("Settings/ImageShowDifferences");
const QString OPT_CMP_IMG_OVERLAYMOVE ("Settings/ImageOverlayMode");
const QString OPT_CMP_IMG_OVERLAYALPHA ("Settings/ImageOverlayAlpha");
const QString OPT_CMP_IMG_DRAGGING_MODE ("Settings/ImageDraggingMode");
const QString OPT_CMP_IMG_ZOOM ("Settings/ImageZoom");
const QString OPT_CMP_IMG_USEBACKCOLOR ("Settings/ImageUseBackColor");
const QString OPT_CMP_IMG_BACKCOLOR ("Settings/ImageBackColor");
const QString OPT_CMP_IMG_DIFFBLOCKSIZE ("Settings/ImageDiffBlockSize");
const QString OPT_CMP_IMG_DIFFCOLORALPHA ("Settings/ImageDiffColorAlpha");
const QString OPT_CMP_IMG_THRESHOLD ("Settings/ImageColorDistanceThreshold");

// Image Binary options
const QString OPT_CMP_BIN_FILEPATTERNS ("Settings/BinaryFilePatterns");

/// Are regular expression linefilters enabled?
const QString OPT_LINEFILTER_ENABLED ("Settings/IgnoreRegExp");
/// Currently selected filefilter
const QString OPT_FILEFILTER_CURRENT ("Settings/FileFilterCurrent");
const QString OPT_FILTER_USERPATH ("Settings/UserFilterPath");
const QString OPT_FILEFILTER_SHARED ("Settings/Filters/Shared");

// Archive support
const QString OPT_ARCHIVE_ENABLE ("Merge7z/Enable");
const QString OPT_ARCHIVE_PROBETYPE ("Merge7z/ProbeSignature");
const QString OPT_ARCHIVE_FILTER_INDEX ("Merge7z/FilterIndex");

// Patch Creator
const QString OPT_PATCHCREATOR_PATCH_STYLE ("PatchCreator/PatchStyle");
const QString OPT_PATCHCREATOR_CONTEXT_LINES ("PatchCreator/ContextLines");
const QString OPT_PATCHCREATOR_CASE_SENSITIVE ("PatchCreator/CaseSensitive");
const QString OPT_PATCHCREATOR_EOL_SENSITIVE ("PatchCreator/EOLSensitive");
const QString OPT_PATCHCREATOR_IGNORE_BLANK_LINES ("PatchCreator/IgnoreBlankLines");
const QString OPT_PATCHCREATOR_WHITESPACE ("PatchCreator/Whitespace");
const QString OPT_PATCHCREATOR_OPEN_TO_EDITOR ("PatchCreator/OpenToEditor");
const QString OPT_PATCHCREATOR_INCLUDE_CMD_LINE ("PatchCreator/IncludeCmdLine");

// Plugins
const QString OPT_PLUGINS_ENABLED ("Settings/PluginsEnabled");
const QString OPT_PLUGINS_DISABLED_LIST ("Settings/PluginsDisabledList");
const QString OPT_PLUGINS_UNPACKER_MODE ("Settings/UnpackerMode");
const QString OPT_PLUGINS_PREDIFFER_MODE ("Settings/PredifferMode");
const QString OPT_PLUGINS_UNPACK_DONT_CHECK_EXTENSION ("Plugins/UnpackDontCheckExtension");

// Startup options
const QString OPT_SHOW_SELECT_FILES_AT_STARTUP ("Settings/ShowFileDialog");

// MDI Tab Bar
const QString OPT_TABBAR_AUTO_MAXWIDTH ("Settings/TabBarAutoMaxWidth");

// MRU
const QString OPT_MRU_MAX ("Settings/MRUMax");

// Font options
const QString OPT_FONT_FILECMP ("Font/");
const QString OPT_FONT_DIRCMP ("FontDirCompare/");

const QString OPT_FONT_USECUSTOM ("Specified");
const QString OPT_FONT_POINTSIZE ("PointSize");
const QString OPT_FONT_HEIGHT ("Height");
const QString OPT_FONT_ESCAPEMENT ("Escapement");
const QString OPT_FONT_ORIENTATION ("Orientation");
const QString OPT_FONT_WEIGHT ("Weight");
const QString OPT_FONT_ITALIC ("Italic");
const QString OPT_FONT_UNDERLINE ("Underline");
const QString OPT_FONT_STRIKEOUT ("StrikeOut");
const QString OPT_FONT_CHARSET ("CharSet");
const QString OPT_FONT_OUTPRECISION ("OutPrecision");
const QString OPT_FONT_CLIPPRECISION ("ClipPrecision");
const QString OPT_FONT_QUALITY ("Quality");
const QString OPT_FONT_PITCHANDFAMILY ("PitchAndFamily");
const QString OPT_FONT_FACENAME ("FaceName");
