// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
	if (len < 0) throw invalid_argument("len<0");
	else if (len == 0) {
		BitLen = 0;
		MemLen = 0;
		pMem = nullptr;
	}
	else {
		BitLen = len;
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n<0 || n>= BitLen) throw invalid_argument("n isnt exist");
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM res = 1;
	if (n < 0) throw invalid_argument("n<0");
	return res << n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0) || (n >= BitLen)) throw invalid_argument("n isnt exist");
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[i] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) throw invalid_argument("n isnt exist");
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[i] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0) || (n >= BitLen)) throw invalid_argument("n isnt exist");
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	int res = pMem[i] & mask;
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (*this != bf) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
   }
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 0;
	if (BitLen == bf.BitLen) {
		res = 1;
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				res *= 0;
		}
	}
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField res(0);
	TBitField a(0);
	if (BitLen <= bf.BitLen) {
		res=bf;
		a=*this;
	}
	else
	{
		res=*this;
		a=bf;
	}
	for (int i = 0; i < a.MemLen; i++) {
		res.pMem[i]|= a.pMem[i];
	}
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(0);
	TBitField a(0);
	if (BitLen <= bf.BitLen) {
		res = bf;
		a = *this;
	}
	else
	{
		res = *this;
		a = bf;
	}
	for (int i = 0; i < a.MemLen; i++) {
		res.pMem[i] &= a.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);

	for (int i = 0; i < BitLen; i++)
	{
		if (res.GetBit(i)!=0)
		{
			res.ClrBit(i);
		}
		else
		{
			res.SetBit(i);
		}
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int bit;
	for (int i=0; i < bf.BitLen; i++) {
		istr >> bit;
		bf.SetBit(bit);
	}
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i)!=0)
			ostr << 1;
		else
			ostr << 0;
}
    return ostr;
}
