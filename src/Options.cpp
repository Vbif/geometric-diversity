#include "stdafx.h"

#include "Options.h"

Options::Options()
{
    // настройки по-умолчанию
    EnemiesCount = 10;
    Speed = 200;
    Time = 20;
}

void Options::LoadFrom(const char* filename)
{
    boost::system::error_code code;

    auto input = Core::fileSystem.OpenRead(filename, code);
    if (code) {
        Log::Error("Loading options error: " + code.message());
        return;
    }

    IO::TextReader reader(input.get());

    std::vector<std::string> tokens;
    std::string line;
    bool readMore = true;

    while (readMore) {

        readMore = reader.ReadAsciiLine(line);
        tokens.clear();

        utils::tokenize(line, tokens, std::string(" ="));
        if (tokens.size() != 2)
            continue;

        SetProperty(tokens[0], tokens[1]);
    }
}

void Options::SetProperty(const std::string& name, const std::string& value)
{
    uint32_t intValue = utils::lexical_cast<uint32_t>(value);

    if (name == "CountTarget")
        EnemiesCount = intValue;
    else if (name == "Speed")
        Speed = intValue;
    else if (name == "Time")
        Time = intValue;
    else
        Log::Warn("Unknown property name in options file");
}
