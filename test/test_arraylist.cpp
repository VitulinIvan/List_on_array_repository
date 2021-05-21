#include "ArrayList.h"

#include <../gtest/gtest.h>
#include <sstream>

TEST(TArrayList, create_arraylist)
{
	ASSERT_NO_THROW(TArrayList<int>());
}

TEST(TArrayList, correct_ins_first)
{
    const int size = 4;
    vector<int> expEq;
    TArrayList<int> A(size);
    for (int i = 0; i < size; i++)
    {
        A.InsFirst(i + 1);
        expEq.push_back(size - i);
    }
    vector<int>res = A.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, correct_ins_last)
{
    const int size = 4;
    vector<int> expEq;
    TArrayList<int> A(size);
    for (int i = 0; i < size; i++)
    {
        A.InsLast(i + 1);
        expEq.push_back(i + 1);
    }
    vector<int>res = A.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, correct_ins)
{
    const int size = 4;
    vector<int> expEq;
    TArrayList<int> A(size * 2);
    for (int i = 0; i < size; i++)
    {
        A.InsLast(i + 1);
    }
    TArrayListIterator<int> iter = A.begin();
    for (int i = 1; i < size / 2 + size % 2; i++)
    {
        ++iter;
    }
    for (int i = 0; i < size; i++)
    {
        A.Ins(iter, i + 1);
        ++iter;
    }
    for (int i = 0; i < size / 2 + size % 2; i++)
    {
        expEq.push_back(i + 1);
    }
    for (int i = 0; i < size; i++)
    {
        expEq.push_back(i + 1);
    }
    for (int i = size / 2 + size % 2; i < size; i++)
    {
        expEq.push_back(i + 1);
    }
    vector<int>res = A.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, correct_del_first)
{
    const int size = 4;
    vector<int> expEq;
    TArrayList<int> A(size);
    A.InsLast(1);
    for (int i = 1; i < size; i++)
    {
        A.InsLast(i + 1);
        expEq.push_back(i + 1);
    }
    A.DelFirst();
    vector<int>res = A.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, correct_del_last)
{
    const int size = 4;
    vector<int> expEq;
    TArrayList<int> A(size);
    for (int i = 0; i < size - 1; i++)
    {
        A.InsLast(i + 1);
        expEq.push_back(i + 1);
    }
    A.InsLast(size);
    A.DelLast();
    vector<int>res = A.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, correct_del)
{
    const int size = 8;
    vector<int> expEq;
    TArrayList<int> A(size);
    for (int i = 0; i < size; i++)
    {
        A.InsLast(i + 1);
    }
    TArrayListIterator<int> iter = A.begin();
    for (int i = 0; i < size / 4 + size % 2; i++)
    {
        ++iter;
    }
    for (int i = 0; i < size / 2; i++)
    {
        TArrayListIterator<int> tmp = iter;
        ++iter;
        A.Del(tmp);
    }
    for (int i = 0; i < size / 4 + size % 2; i++)
    {
        expEq.push_back(i + 1);
    }
    for (int i = size / 2 + size / 4 + size % 2; i < size; i++)
    {
        expEq.push_back(i + 1);
    }
    vector<int>res = A.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, use_iterator)
{
    const int size = 4;
    TArrayList<int> A(size);
    string expStr = "";
    for (int i = 0; i < size; i++)
    {
        expStr += (i + 1) + '0';
        A.InsLast(i + 1);
    }
    TArrayListIterator<int> iter = A.begin();
    string res = "";
    for (; iter != A.end(); ++iter)
    {
        res += *iter + '0';
    }
    EXPECT_EQ(expStr, res);
}

TEST(TArrayList, find_elems_mod_n_equals_0)
{
    const int size = 4;
    int n = 2;
    vector<int> expEq;
    TArrayList<int> A(size);
    for (int i = 0; i < size; i++)
    {
        A.InsLast(i + 1);
        if ((i + 1) % n == 0)
            expEq.push_back(i + 1);
    }
    vector<int> res;
    res = A.ElemsModZero(n);
    EXPECT_EQ(expEq, res);
}

TEST(TArrayList, write_to_file)
{
    const int size = 4;
    TArrayList<int> A(size);
    for (int i = 0; i < size; i++)
        A.InsLast(i + 1);
    A.WriteToFile("ArrayListOI.txt");
    string expList = "1234";
    string ArrayList = "";
    ifstream fin("ArrayListOI.txt");
    fin >> ArrayList;
    fin.close();
    EXPECT_EQ(expList, ArrayList);
}
