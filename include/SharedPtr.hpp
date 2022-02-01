// Copyright 2021 Your Name <erzunov2002@gamil.com>
// реализация указателя который считает количество ссылок на объект
#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <cstdio>
#include "atomic"
#include "utility"
template <typename T>
class SharedPtr {
 private:
  T* _mptr;
  std::atomic_uint* _count;

 public:
  SharedPtr() //конструктор по умолчанию
      : _mptr(nullptr), _count(nullptr)
  {
  }

  explicit SharedPtr(T* ptr) //конструктор
  {
    _mptr = ptr;
    _count = new std::atomic_uint(1); //при создании первого объекта создается счетчик ссылок
  }

  SharedPtr(const SharedPtr& r) //конструктор копирования (посчет сылок +1 , создание нового объекта)
  {
    *this = r;  //указатель на адресс объекта класса
  }

  SharedPtr(SharedPtr&& r) //конструктор перемещения (кладет объект в r)
  {
    *this = std::move(r);
  }

  ~SharedPtr() //деструктор
  {
    if (_count != nullptr) { //если счетчик ссылок не пуст, вычитаем единицу из счетчика
      _count--;
    }
    else { //если ссылки закончились, удаляем счетчик и очищаем память
      delete _count;
      delete _mptr;
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& //перегрузка оператора =
  {
    if (this != &r)
    {
      _mptr = r._mptr;
      _count = r._count;
      if (_count != nullptr)
      {
        (*_count)++;
      }
    }
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr& //перегрузка оператора = ч.2
  {
    if (this != &r) {
      _mptr = r._mptr;
      _count = r._count;
      r._count = nullptr;
      r._mptr = nullptr;
    }
    return *this;
  }

  // проверяет, указывает ли указатель на объект
  operator bool() const
  {
    return (_mptr != nullptr);
  }

  auto operator*() const -> T& //перегрузка *
  {
    return *_mptr;
  }

  auto operator->() const -> T* //перегрузка ->
  {
    return _mptr;
  }

  auto get() -> T* //возвращение указателя
  {
    return _mptr;
  }
  void reset() //сброс
  {
    *this = SharedPtr();
  }
  void reset(T* ptr)//сброс
  {
    *this = SharedPtr(ptr);
  }

  void swap(SharedPtr& r) //подмена
  {
    std::swap(_mptr, r._mptr);
    std::swap(_count, r._count);
  }
  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот же управляемый объект
  auto use_count() const -> size_t
  {
    if (_count == nullptr){
      return 0;
    }
    return *_count;
  }
};

#endif // INCLUDE_SHAREDPTR_HPP_
