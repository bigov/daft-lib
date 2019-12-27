
# Следует указывать в явном виде,
# какие операции копирования и перемещения поддерживает класс

> Открытый интерфейс каждого класса должен четко указывать, какие операции
> копирования и перемещения поддерживает класс.
> Обычно это должно принимать форму явного объявления и / или удаления
> соответствующих операций в публичном разделе декларации.


    ```c++
    class Copyable {
     public:
      Copyable(const Copyable& other) = default;
      Copyable& operator=(const Copyable& other) = default;

      // The implicit move operations are suppressed by the declarations above.
    };

    class MoveOnly {
     public:
      MoveOnly(MoveOnly&& other);
      MoveOnly& operator=(MoveOnly&& other);

      // The copy operations are implicitly deleted, but you can
      // spell that out explicitly if you want:
      MoveOnly(const MoveOnly&) = delete;
      MoveOnly& operator=(const MoveOnly&) = delete;
    };

    class NotCopyableOrMovable {
     public:
      // Not copyable or movable
      NotCopyableOrMovable(const NotCopyableOrMovable&) = delete;
      NotCopyableOrMovable& operator=(const NotCopyableOrMovable&)
          = delete;

      // The move operations are implicitly disabled, but you can
      // spell that out explicitly if you want:
      NotCopyableOrMovable(NotCopyableOrMovable&&) = delete;
      NotCopyableOrMovable& operator=(NotCopyableOrMovable&&)
          = delete;
    };
    ```

