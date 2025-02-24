#include <QApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QStandardPaths>
#include <QTranslator>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "client/kimaiclient.h"
#include "gui/mainwindow.h"
#include "settings/settings.h"

using namespace kemai;

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif

    QApplication app(argc, argv);
    app.setApplicationName("Kemai");
    app.setOrganizationName("Kemai");

    // Get kemai data directory and log file path
    auto kemaiSettings = Settings::get();
    auto appDataDir    = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto logFilePath   = QDir(appDataDir).absoluteFilePath("kemai.log");

    // Init spdlog console and rotating file (3 x 5Mb)
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto rotfile = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFilePath.toStdString(), 1024 * 1024 * 5, 3);
    std::vector<spdlog::sink_ptr> sinks{console, rotfile};

    auto logger = std::make_shared<spdlog::logger>("kemai", sinks.begin(), sinks.end());
    spdlog::register_logger(logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);

    // Setup Qt and app translations
    QTranslator qtTranslator;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if (qtTranslator.load("qt_" + kemaiSettings.kemai.language.name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
#else
    if (qtTranslator.load("qt_" + kemaiSettings.kemai.language.name(), QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
#endif
    {
        app.installTranslator(&qtTranslator);
    }

    QTranslator appTranslator;
    if (appTranslator.load(kemaiSettings.kemai.language, "kemai", "_", ":/l10n"))
    {
        app.installTranslator(&appTranslator);
    }

    // Setup trusted certificates
    KimaiClient::addTrustedCertificates(kemaiSettings.trustedCertificates);

    // Startup
    MainWindow mainWindow;
    mainWindow.restoreGeometry(kemaiSettings.kemai.geometry);
    mainWindow.show();

    return app.exec();
}
