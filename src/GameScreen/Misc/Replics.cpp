#include "stdafx.h"

#include "Replics.h"

Replics::Replics()
{
    auto welcome_t0 = codepage_to_utf8("Добро пожаловать в\n"
                                       "тренировочный центр,\n"
                                       "кадет. Сегодня ты \n"
                                       "научишся стрелять\n"
                                       "по круглозадым!",
        1251);
    auto welcome_t1 = codepage_to_utf8("Разве это не\n"
                                       "геометрический\n"
                                       "шовинизм?",
        1251);
    auto welcome_t2 = codepage_to_utf8("Прекратить разговоры!", 1251);

    _replics.push_back({ welcome_t0, welcome_t1, welcome_t2 });

    auto s0_t0 = codepage_to_utf8("Этот новейший\n"
                                  "симулятор обеспечивает\n"
                                  "полную реалистичность\n"
                                  "военных действий!",
        1251);
    auto s0_t1 = codepage_to_utf8("Но тут даже \"круги\"\n"
                                  "не круглые...",
        1251);

    auto s0_t2 = codepage_to_utf8("Отставить разговоры!\n"
                                  "Приступить к полному\n"
                                  "погружению в атмосферу\n"
                                  "боевых действий!",
        1251);

    _replics.push_back({ s0_t0, s0_t1, s0_t2 });

    auto s1_t0 = codepage_to_utf8("Существо без углов\n"
                                  "не способно к\n"
                                  "аналитической\n"
                                  "деятельности!",
        1251);
    auto s1_t1 = codepage_to_utf8("...",
        1251);

    _replics.push_back({ s1_t0, s1_t1 });

    auto s2_t0 = codepage_to_utf8("Сколько квадрат не\n"
                                  "корми, а углов\n"
                                  "все равно четыре.",
        1251);

    _replics.push_back({ s2_t0 });

    auto s3_t0 = codepage_to_utf8("Когда-то меня тоже вела\n"
                                  "дорога приключений,\n"
                                  "но потом мне\n"
                                  "прострелили угол.",
        1251);
    auto s3_t1 = codepage_to_utf8("Главное, что бы не\n"
                                  "колено... Наверное.",
        1251);

    _replics.push_back({ s3_t0, s3_t1 });

    auto s4_t0 = codepage_to_utf8("Прости, кадет, но твоя\n"
                                  "столовая в другом\n"
                                  "корпусе.",
        1251);
    auto s4_t1 = codepage_to_utf8("Одна из причин, по\n"
                                  "которой я не хочу\n"
                                  "быть сантехником.",
        1251);

    _replics.push_back({ s4_t0, s4_t1 });

    auto s5_t0 = codepage_to_utf8("Как говорит наш\n"
                                  "замполит: \"Семь раз\n"
                                  "прицель, один раз\n"
                                  "пристрель!\"",
        1251);
    auto s5_t1 = codepage_to_utf8("А что это значит?",
        1251);
    auto s5_t2 = codepage_to_utf8("Это квадратная\n"
                                  "мудрость.",
        1251);

    _replics.push_back({ s5_t0, s5_t1, s5_t2 });
}

void Replics::StartReplic(SquareLife* soldier, SquareLife* general)
{
    _soldier = soldier;
    _general = general;
    SaySequence(_replics[0]);
}

void Replics::RandomReplic()
{
    _soldier->Shut();
    _general->Shut();

    size_t index = math::random(size_t(1), _replics.size() - 1);
    SaySequence(_replics[index]);
}

void Replics::SaySequence(const std::vector<std::string>& seq)
{
    switch (seq.size()) {
    case 1:
        SaySequence1(seq);
        break;
    case 2:
        SaySequence2(seq);
        break;
    case 3:
        SaySequence3(seq);
        break;
    default:
        Log::Error("Cannot say this sequence");
        break;
    }
}

void Replics::SaySequence1(const std::vector<std::string>& seq)
{
    _general->Say(seq[0]);
}

void Replics::SaySequence2(const std::vector<std::string>& seq)
{
    _general->Say(seq[0], [this, &seq]() {
        _soldier->Say(seq[1]);
    });
}

void Replics::SaySequence3(const std::vector<std::string>& seq)
{
    _general->Say(seq[0], [this, &seq]() {
        _soldier->Say(seq[1], [this, &seq]() {
            _general->Say(seq[2]);
        });
    });
}
