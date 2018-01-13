#include "stdafx.h"

#include "Replics.h"

Replics::Replics()
{
    auto welcome_t0 = codepage_to_utf8("����� ���������� �\n"
                                       "������������� �����,\n"
                                       "�����. ������� �� \n"
                                       "�������� ��������\n"
                                       "�� �����������!",
        1251);
    auto welcome_t1 = codepage_to_utf8("����� ��� ��\n"
                                       "��������������\n"
                                       "��������?",
        1251);
    auto welcome_t2 = codepage_to_utf8("���������� ���������!", 1251);

    _replics.push_back({ welcome_t0, welcome_t1, welcome_t2 });

    auto s0_t0 = codepage_to_utf8("���� ��������\n"
                                  "��������� ������������\n"
                                  "������ ��������������\n"
                                  "������� ��������!",
        1251);
    auto s0_t1 = codepage_to_utf8("�� ��� ���� \"�����\"\n"
                                  "�� �������...",
        1251);

    auto s0_t2 = codepage_to_utf8("��������� ���������!\n"
                                  "���������� � �������\n"
                                  "���������� � ���������\n"
                                  "������ ��������!",
        1251);

    _replics.push_back({ s0_t0, s0_t1, s0_t2 });

    auto s1_t0 = codepage_to_utf8("�������� ��� �����\n"
                                  "�� �������� �\n"
                                  "�������������\n"
                                  "������������!",
        1251);
    auto s1_t1 = codepage_to_utf8("...",
        1251);

    _replics.push_back({ s1_t0, s1_t1 });

    auto s2_t0 = codepage_to_utf8("������� ������� ��\n"
                                  "�����, � �����\n"
                                  "��� ����� ������.",
        1251);

    _replics.push_back({ s2_t0 });

    auto s3_t0 = codepage_to_utf8("�����-�� ���� ���� ����\n"
                                  "������ �����������,\n"
                                  "�� ����� ���\n"
                                  "����������� ����.",
        1251);
    auto s3_t1 = codepage_to_utf8("�������, ��� �� ��\n"
                                  "������... ��������.",
        1251);

    _replics.push_back({ s3_t0, s3_t1 });

    auto s4_t0 = codepage_to_utf8("������, �����, �� ����\n"
                                  "�������� � ������\n"
                                  "�������.",
        1251);
    auto s4_t1 = codepage_to_utf8("���� �� ������, ��\n"
                                  "������� � �� ����\n"
                                  "���� �����������.",
        1251);

    _replics.push_back({ s4_t0, s4_t1 });

    auto s5_t0 = codepage_to_utf8("��� ������� ���\n"
                                  "��������: \"���� ���\n"
                                  "�������, ���� ���\n"
                                  "���������!\"",
        1251);
    auto s5_t1 = codepage_to_utf8("� ��� ��� ������?",
        1251);
    auto s5_t2 = codepage_to_utf8("��� ����������\n"
                                  "��������.",
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
