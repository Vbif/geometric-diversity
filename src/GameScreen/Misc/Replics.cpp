#include "stdafx.h"

#include "Replics.h"

Replics::Replics()
{
    auto welcome_t0 = codepage_to_utf8("����� ���������� � �������������\n"
                                       "�����, �����. ������� �� ��������\n"
                                       "�������� �� �����������!",
        1251);
    auto welcome_t1 = codepage_to_utf8("����� ��� �� ��������������\n"
                                       "��������?",
        1251);
    auto welcome_t2 = codepage_to_utf8("���������� ���������!", 1251);

    _replics.push_back({ welcome_t0, welcome_t1, welcome_t2 });
}

void Replics::StartReplic(SquareLife& soldier, SquareLife& general)
{
    _soldier = &soldier;
    _general = &general;
    SaySequence3(_replics[0]);
}

void Replics::SaySequence3(const std::vector<std::string>& seq)
{
    _general->Say(seq[0], [this, &seq]() {
        _soldier->Say(seq[1], [this, &seq]() {
            _general->Say(seq[2]);
        });
    });
}
