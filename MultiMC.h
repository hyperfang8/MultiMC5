#pragma once

#include <QApplication>
#include "MultiMCVersion.h"
#include <memory>
#include "logger/QsLog.h"
#include "logger/QsLogDest.h"

class MinecraftVersionList;
class LWJGLVersionList;
class HttpMetaCache;
class SettingsObject;
class InstanceList;
class MojangAccountList;
class IconList;
class QNetworkAccessManager;
class ForgeVersionList;
class JavaVersionList;
class UpdateChecker;
class NewsChecker;

#if defined(MMC)
#undef MMC
#endif
#define MMC (static_cast<MultiMC *>(QCoreApplication::instance()))

// FIXME: possibly move elsewhere
enum InstSortMode
{
	// Sort alphabetically by name.
	Sort_Name,
	// Sort by which instance was launched most recently.
	Sort_LastLaunch,
};

class MultiMC : public QApplication
{
	Q_OBJECT
public:
	enum Status
	{
		Failed,
		Succeeded,
		Initialized,
	};

public:
	MultiMC(int &argc, char **argv, const QString &root = QString());
	virtual ~MultiMC();

	std::shared_ptr<SettingsObject> settings()
	{
		return m_settings;
	}

	std::shared_ptr<InstanceList> instances()
	{
		return m_instances;
	}

	std::shared_ptr<MojangAccountList> accounts()
	{
		return m_accounts;
	}

	std::shared_ptr<IconList> icons();

	Status status()
	{
		return m_status;
	}

	MultiMCVersion version()
	{
		return m_version;
	}

	std::shared_ptr<QNetworkAccessManager> qnam()
	{
		return m_qnam;
	}

	std::shared_ptr<HttpMetaCache> metacache()
	{
		return m_metacache;
	}

	std::shared_ptr<UpdateChecker> updateChecker()
	{
		return m_updateChecker;
	}

	std::shared_ptr<NewsChecker> newsChecker()
	{
		return m_newsChecker;
	}

	std::shared_ptr<LWJGLVersionList> lwjgllist();

	std::shared_ptr<ForgeVersionList> forgelist();

	std::shared_ptr<MinecraftVersionList> minecraftlist();

	std::shared_ptr<JavaVersionList> javalist();

	/*!
	 * Installs update from the given update files directory.
	 */
	void installUpdates(const QString &updateFilesDir, bool restartOnFinish = false);

	/*!
	 * Sets MultiMC to install updates from the given directory when it exits.
	 */
	void setUpdateOnExit(const QString &updateFilesDir);

	/*!
	 * Gets the path to install updates from on exit.
	 * If this is an empty string, no updates should be installed on exit.
	 */
	QString getExitUpdatePath() const;

	/*!
	 * Opens a json file using either a system default editor, or, if note empty, the editor
	 * specified in the settings
	 */
	bool openJsonEditor(const QString &filename);

	/// this is the root of the 'installation'. Used for automatic updates
	const QString &root()
	{
		return rootPath;
	}
	/// this is the where the binary files reside
	const QString &bin()
	{
		return binPath;
	}
	/// this is the work/data path. All user data is here.
	const QString &data()
	{
		return dataPath;
	}
	/**
	 * this is the original work path before it was changed by the adjustment mechanism
	 */
	const QString &origcwd()
	{
		return origcwdPath;
	}

private:
	void initLogger();

	void initGlobalSettings();

	void initHttpMetaCache();

	void initTranslations();

private:
	friend class UpdateCheckerTest;
	friend class DownloadUpdateTaskTest;

	std::shared_ptr<QTranslator> m_qt_translator;
	std::shared_ptr<QTranslator> m_mmc_translator;
	std::shared_ptr<SettingsObject> m_settings;
	std::shared_ptr<InstanceList> m_instances;
	std::shared_ptr<UpdateChecker> m_updateChecker;
	std::shared_ptr<NewsChecker> m_newsChecker;
	std::shared_ptr<MojangAccountList> m_accounts;
	std::shared_ptr<IconList> m_icons;
	std::shared_ptr<QNetworkAccessManager> m_qnam;
	std::shared_ptr<HttpMetaCache> m_metacache;
	std::shared_ptr<LWJGLVersionList> m_lwjgllist;
	std::shared_ptr<ForgeVersionList> m_forgelist;
	std::shared_ptr<MinecraftVersionList> m_minecraftlist;
	std::shared_ptr<JavaVersionList> m_javalist;
	QsLogging::DestinationPtr m_fileDestination;
	QsLogging::DestinationPtr m_debugDestination;

	QString m_updateOnExitPath;

	QString rootPath;
	QString binPath;
	QString dataPath;
	QString origcwdPath;

	Status m_status = MultiMC::Failed;
	MultiMCVersion m_version;
};
