#include "Player.h"

void Player::logo() const
{
	IO::setColor(IO::White);
	IO::print("          �����������������������������������������������������������\n");
	IO::print("          ��                                                                                                                ��\n");
	IO::print("          ��                                                                                                                ��\n");
	IO::print("          ��   �����������                                                                                         ��\n");
	IO::print("          ��   �����������                                                                                         ��\n");
	IO::print("          ��           ���                                ���         ���      ���    ���   ���              ���     ��\n");
	IO::print("          ��           ���             ����             ���         ���    ���      ���     ���          ���       ��\n");
	IO::print("          ��           ���           ���    ��    ����������  ���  ���                   ���      ���         ��\n");
	IO::print("          ��           ���          ���     ���         ���         �����          ���         ���  ���           ��\n");
	IO::print("          ��           ���          ���     ���         ���         ����            ���            ���              ��\n");
	IO::print("          ��           ���          ������            ���         ���              ���         ���  ���           ��\n");
	IO::print("          ��           ���          ���                  ���         ���              ���       ���      ���         ��\n");
	IO::print("          ��           ���           ���                 ���         ���              ���     ���          ���       ��\n");
	IO::print("          ��           ���            ���                ���         ���              ���    ���            ���      ��\n");
	IO::print("          ��           ���              ����            ���         ���              ���   ���              ���     ��\n");
	IO::print("          ��                                                                                                                ��\n");
	IO::print("          ��                                                                                                                ��\n");
	IO::print("          �����������������������������������������������������������\n");
}

void Player::Register()
{
	logo();
	IO::print("          [ Please enter a name for the game. ]\n");
	IO::print("          >> ");
	cin >> name;
	IO::print("          [ Please choose the type of game. ]\n");
	IO::print("          1. Games alone\n");
	IO::print("          2. A game of two\n");
	IO::print("          >> ");
	cin >> GameType;
	IO::clear();
}