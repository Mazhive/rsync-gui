#include "argumenthandler.h"

ArgumentHandler::ArgumentHandler(const QCoreApplication &app) {
    QCommandLineParser parser;
    parser.setApplicationDescription("Rsync-GUI Wrapper");
    
    // Voeg de standaard help/version toe
    parser.addHelpOption();
    parser.addVersionOption();

    // DIT IS DE FIX: 
    // Vertel de parser dat hij onbekende opties (zoals --delete) niet moet 
    // proberen te verwerken, maar gewoon moet overslaan/doorlaten.
    parser.setOptionsAfterPositionalArgumentsMode(QCommandLineParser::ParseAsPositionalArguments);

    // Vang alles op
    parser.addPositionalArgument("params", "Extra rsync parameters");
    
    // We gebruiken parse() in plaats van process() om 'Unknown option' errors te voorkomen
    parser.parse(app.arguments());

    // Haal nu alle argumenten op die NA de programmanaam komen
    QStringList args = app.arguments();
    args.removeFirst(); // Verwijder de programmanaam zelf (./RemotePull)
    
    m_combinedArgs = args.join(" ");
}

QString ArgumentHandler::getCombinedArgs() const {
    return m_combinedArgs;
}
