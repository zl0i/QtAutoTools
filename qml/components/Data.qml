pragma Singleton
import QtQuick 2.12

QtObject {
    readonly property var modelFlagsWinDeployQt: [
        {
            "name": "--debug",
            "description": "Assume debug binaries"
        },
        {

            "name": "--release",
            "description": " Assume release binaries"
        },
        {
            "name": "--pdb",
            "description": "Deploy .pdb files (MSVC)"
        },
        {
            "name": "--force",
            "description": "Force updating files"
        },
        {
            "name": "--dry-run",
            "description": " Simulation mode. Behave normally, but do not copy/update any files"
        },
        {
            "name": "--no-patchqt",
            "description": "Do not patch the Qt5Core library"
        },
        {
            "name": "--no-plugins",
            "description": "Skip plugin deployment"
        },
        {
            "name": "--no-libraries",
            "description": "Skip library deployment"
        },
        {
            "name": "--no-quick-import",
            "description": "Skip deployment of Qt Quick imports"
        },
        {
            "name": "--no-translations",
            "description": "Skip deployment of translations"
        },
        {
            "name":  "--no-system-d3d-compiler",
            "description": "Skip deployment of the system D3D compiler"
        },
        {
            "name": "--compiler-runtime",
            "description": "Deploy compiler runtime (Desktop only)"
        },
        {
            "name": " --no-compiler-runtime",
            "description": "Do not deploy compiler runtime (Desktop only)"
        },
        {
            "name": "--webkit2",
            "description": "Deployment of WebKit2 (web process)"
        },
        {
            "name":  "--no-webkit2",
            "description": "Skip deployment of WebKit2"
        },
        {
            "name": "--json",
            "description": "Print to stdout in JSON format"
        },
        {
            "name": "--angle",
            "description": "Force deployment of ANGLE"
        },
        {
            "name": "--no-angle",
            "description": "Disable deployment of ANGLE"
        },
        {
            "name":  "--no-opengl-sw",
            "description": "Do not deploy the software rasterizer library"
        }
    ]
    readonly property var modelLibraryWindDeployQt: [
        "bluetooth", "concurrent", "core", "declarative", "designer", "designercomponents", "enginio",
        "gamepad", "gui", "qthelp", "multimedia", "multimediawidgets", "multimediaquick", "network", "nfc",
        "opengl", "positioning", "printsupport", "qml", "qmltooling", "quick", "quickparticles", "quickwidgets",
        "script", "scripttools", "sensors", "serialport", "sql", "svg", "test", "webkit", "webkitwidgets",
        "websockets", "widgets", "winextras", "xml", "xmlpatterns", "webenginecore", "webengine",
        "webenginewidgets", "3dcore", "3drenderer", "3dquick", "3dquickrenderer", "3dinput", "3danimation",
        "3dextras", "geoservices", "webchannel", "texttospeech", "serialbus", "webview"
    ]

    readonly property var modelLanguages: [
        {
            "name": "ru",
            "description": "Русский"
        },
        {
            "name": "us",
            "description": "США"
        },
        {
            "name": "de",
            "description": "Германия"
        },
        {
            "name": "fr",
            "description": "Франция"
        },
        {
            "name": "ua",
            "description": "Украина"
        },
        {
            "name": "kz",
            "description": "Казахстан"
        },
        {
            "name": "by",
            "description": "Беларусь"
        },
        {
            "name": "gr",
            "description": "Греция"
        },
        {
            "name": "es",
            "description": "Испания"
        },
        {
            "name": "eg",
            "description": "Египет"
        },
        {
            "name": "in",
            "description": "Индия"
        },
        {
            "name": "cn",
            "description": "Китай"
        },
        {
            "name": "gb",
            "description": "Великобритания"
        },
        {
            "name": "jp",
            "description": "Япония"
        },
        {
            "name": "au",
            "description": "Австрия"
        },
        {
            "name": "br",
            "description": "Бразилия"
        }
    ]

}
