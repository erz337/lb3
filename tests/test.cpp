// Copyright 2021 Your Name <erzunov2002@gmail.com>
#include <gtest/gtest.h>
#include <SharedPtr.hpp>
#include <string.h>

TEST(SharedPtr, Default) { //тест конструктор по умолчанию
  SharedPtr <int> ptr = SharedPtr<int>();
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtr, Init) { //тест конструктор
  int* pt = new int(1);
  SharedPtr ptr = SharedPtr(pt);
  EXPECT_EQ(ptr.get(), pt);
  EXPECT_EQ(ptr.use_count(), 1);
  delete pt;
}

TEST(SharedPtr, Copy) { //тест конструктор копирования
  int* pt = new int(1);
  const SharedPtr ptr1= SharedPtr(pt);
  SharedPtr ptr2 = SharedPtr (ptr1);
  EXPECT_EQ(*ptr2, *ptr1);
  EXPECT_EQ(ptr1.use_count(), 2);
  EXPECT_EQ(ptr2.use_count(), 2);
  delete pt;
}

TEST(SharedPtr, Move) { //тест конструктор перемещения
  int* pt = new int(1);
  SharedPtr ptr = SharedPtr(SharedPtr(pt));
  EXPECT_EQ(*ptr, 1);
  EXPECT_EQ(ptr.use_count(), 1);
  int* pt2 = new int(2);
  SharedPtr <int> ptr11(pt2);
  SharedPtr <int> ptr22(std::move(ptr11));
  EXPECT_EQ(*ptr22, 2);
  EXPECT_EQ(ptr11.get(), nullptr);
  EXPECT_EQ(ptr22.use_count(), 1);
  delete pt;
  delete pt2;
}

TEST(SharedPtr, OverloadEq) { //тест на перегрузку оператора "="
  int* a = new int(1);
  SharedPtr <int> p(a);
  SharedPtr <int> p1 = p;
  EXPECT_EQ(*p, *p1);
  EXPECT_EQ(p.use_count(), 2);
  EXPECT_EQ(p1.use_count(), 2);
  SharedPtr <int> p2 = std::move(p);
  EXPECT_EQ(*p2, 1);
  EXPECT_EQ(p.get(), nullptr);
  EXPECT_EQ(p2.use_count(), 2);
  delete a;
}

TEST(SharedPtr, Bool) { //тест указ. на объект
  int* pt = new int(10);
  SharedPtr <int> ptr(pt);
  EXPECT_TRUE(ptr);
  SharedPtr <int> ptr1;
  EXPECT_FALSE(ptr1);
  delete pt;
}

TEST(SharedPtr, Get) { //тест на получение объекта
  auto* str = new std::string("ptr");
  auto* ptr = new SharedPtr <std::string> (str);
  EXPECT_EQ((*ptr)->length(), 3);
  delete str;
  delete ptr;
}

TEST(SharedPtr, Reset) { //Тест на сброс
  int* pt = new int(1);
  SharedPtr <int> ptr(pt);
  ptr.reset();
  EXPECT_FALSE(ptr);
  int* pt2 = new int(2);
  SharedPtr <int> p1(pt2);
  ptr.reset(pt2);
  EXPECT_EQ(*ptr, *p1);
  delete pt;
  delete pt2;
}

TEST(SharedPtr, Swap) { //Тест на подмену
  int* pt = new int(1);
  int* pt2 = new int(2);
  SharedPtr <int> ptr1(pt);
  SharedPtr <int> ptr2(pt2);
  SharedPtr <int> ptr3(ptr2);
  ptr1.swap(ptr2);
  EXPECT_EQ(*ptr1, 2);
  EXPECT_EQ(ptr1.use_count(), 2);
  EXPECT_EQ(*ptr2, 1);
  EXPECT_EQ(ptr2.use_count(), 1);
  delete pt;
  delete pt2;
}