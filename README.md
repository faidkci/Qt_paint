# Qt_paint
Данная программа является графическим редактором. В ней реализованы следующие функции:

1.	Возможность выбора цвета. Она представляет собой четыре кнопки: три со стандартными цветами RGB и еще одну, в которой можно выбрать кастомный цвет.
2.	Сохранение изображения в файл и его загрузка из файла.
3.	Возможность рисовать геометрические фигуры: треугольник,  прямоугольник и ромб. Эта функция позволяет рисовать данные геометрические фигуры в различных цветах и с различными параметрами размера, отношения сторон и углов.

Для работы с фигурами был разработан базовый класс Figure, который наследован от QGraphicsItem. Весь основной функционал программы реализован в этом классе, после чего были созданны еще три класса, которые наследованы от класса Figure, но в каждом из них реализован метод отрисовки конкретной фигуры. На рисунке ниже можно увидеть логику наследования для базового класса Figure.
