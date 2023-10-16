// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (*this != s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    int res = 0;
    if (MaxPower == s.MaxPower)
        res = (BitField == s.BitField);
    return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (*this == s)
        return 0;
    else
        return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet res(BitField.GetLength());
    res = BitField | s.BitField;
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < MaxPower && Elem >= 0) {
        TSet res(BitField);
        res.InsElem(Elem);
        return res;
    }
    else throw invalid_argument("elem isnt correct");
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < MaxPower && Elem >= 0)
    {
        TSet res(BitField);
        res.DelElem(Elem);
        return res;
    }
    else
    {
        throw invalid_argument("elem isnt correct");
    }
}


TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(BitField.GetLength());
    res = BitField & s.BitField;
    res.MaxPower = res.BitField.GetLength();
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(BitField);
    res.BitField = ~res.BitField;
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int elem;
    for (int i = 0; i < s.MaxPower; i++)
    {
        istr >> elem;
        s.InsElem(elem);
    }
    return istr;
}
    

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i) != 0)
        {
            ostr << s.BitField.GetBit(i);
        }
        
    }
    return ostr;
}
