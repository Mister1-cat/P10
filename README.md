# Лаборатораня работа №1
***
## Задание
Реализовать имитацию рабочего стола используя светодиодную панель P10 и джойстик.

***

## Изучение SPI ##
**SPI (Serial Peripheral Interface)** - последовательный синхронный стандарт передачи данных в режиме полного дуплекса, 
предназначенный для обеспечения простого и недорогого высокоскоростного сопряжения микроконтроллеров и периферии

Любая отладочная плата серии STM32 обладает возможностью реализаци подобного способа передачи данных.

**О процессе передачи данных**

Сам же процесс передачи осуществляется последовательно, с формированием пакетов объёмом 1 байт ( 8 бит). Однако, бывают 
случаи, когда его объём уменьшается до 4 бит.

Общий принцип передачи данных изображён на рисунке ниже.

![SPI communication system.png](Additional%20files%2FSPI%20communication%20system.png)

 
Подлежащие передаче данные ведущее и ведомое устройства помещают в сдвиговые регистры. После этого ведущее 
устройство начинает генерировать импульсы синхронизации на линии *SCLK*, что приводит к взаимному обмену данными. 
Передача данных осуществляется бит за битом от ведущего по линии *MOSI* и от ведомого по линии *MISO*. Передача 
осуществляется, как правило, начиная со старших битов, но некоторые производители допускают изменение порядка 
передачи битов программными методами. После передачи каждого пакета данных ведущее устройство, в целях 
синхронизации ведомого устройства, может перевести линию *SS* в высокое состояние.

**Приимущества метода передачи данных**
- Средняя скорость передачи данных
- Возможность произвольного выбора длины пакета
- Простая аппаратная реализация
- Использованием лишь четырёх пинов
- Максимальная тактовая частота ограничена лишь производительностью устройств

**Недостатки метода передачи данных**
- Ведомое устройство не контралирует поток данных
- Нет официальных стандартов (устрйоства не имеют сертефикацию)
- Отсутвие *"горячего"* подключения устройств
- Нет обратной связи от ведомого устройства (возможна передача данных в пустоту или с серьёзным искажением)

***
## Изучение устройства LEDP10 ##

Начнём с внешнего вида панели*, её вы можете наблюдать на изображении ниже

**Панель, представленная ниже, является версией с SMD светодиодами, с изображениями панели, на LED светодиодах
можно ознакомиться в каталоге Additional files под хороший саундтрек (весь последющий текст идёт всё так же для LED
версии панели, которая имеется у нас в лаборатории)*


![P10.jpg](Additional%20files%2FP10.jpg)![LEDP10_RED.png]


Вверху она показана в включённом состоянии, вниху же - в выключенном.

Итак, основные параметры данной панели можно выделить следующие: 
- **Размер:** 32 (длина) на 16 (высота) в светодиодах
- **Питающее напряжение**: 5 вольт постоянного тока
- **Максимальное потребление тока**: 4 ампера
- **Максимальная мощность**: 20 Ватт

Это основные характеристики данной рабочей матрицы. Дальше рассмотрим **обратную сторону панели***:

![Position of components.jpg](Additional%20files%2FPosition%20of%20components.jpg)
**Образаю внимание, что это фотография вяза из статьи на хабре и реальная панель несколько отличается, просто здесь
данва исчерпывающая информация о компонентах, которая потом нужна будет для рассмотра принципиальной схемы*

Под цифрами обозначены различные узлы данной системы
1. **SM74HC245D** — неинвертирующий буфер (D17)
2. **88SM74HC04** — 6-канальный инвертор
3. **SM74HC138D** — 8-битный дешифратор (D18)
4. **PM4953 (4 еденицы)** — сборка из 2 P-канальных MOSFET (VT1-VT4)
5. **74HC595D (16 едениц)** — сдвиговый регистр с защёлкой (D1-D16)
6. Два разъёма, подключение осуществлеяется через разъём **6.1**, разъём 6.2 же необхдим для подключения следующей панели
последовательно.

![Position of components_new.jpg](Additional%20files%2FPosition%20of%20components_new.jpg)



Выше приведено изображение матрицы, с которой был реализован проект, с точки зрения компоновки есть отличия в детали 1. 
Что достаточно странно и не совсем понятно, так как все найденные схемы отличаются от того, что есть у нас.

Ниже приведено изображение, содержащее принципиальную схему устройства, по которой можно понять весь принцип 
работы данной панели. Однако эта схема акутальна для фотографии панели с хабра, но так как многие элементы аналогичны
нашим, то можно сказать, что она вполне приминима к данной панели.

![Schematic diagram.gif](Additional%20files%2FSchematic%20diagram.gif)


*******

## Подключение к светодиодной матрице LEDP10 ##

Подключение к матрице в рамках лабораторной работы будет осуществляться путём подключения сигнальных проводов от платы STM32 
к специальному кабелю, установленному в крайний левый слот *(его можно увидеть на изображении выше, он имеет набор пинов, 
окружённых чёрным корпусом)*

Крайний правый порт нужен для последовательно подключения связки панелей.

Ниже приведён пример распиновки порта (а так же кабеля (так как он дублирует их)) относительно ключа (левая 
полоска, едва выходящая из контура кабеля).

![Pinout contacts.jpg](Additional%20files%2FPinout%20contacts.jpg)

Рассмотрим назначение каждого из пинов
- **A** и **B** - необходим для переключения между строками
- **OE** - отвечает за запуск / отключение матрицы *(с помощью ШИМ сигнала можно регулировать яркость (настоятельно рекомендую при длительной работе с матрицей))*
- **SCK** - канал для синхронизации частот работы переферии *(подклчается к аналогичному пину на STM32)*
- **MOSI** - канал передачи данных *(подклчается к аналогичному пину на STM32)*
- **SCLK** - канал подтверждения конца загрузки байта данных.

Если вы подключили всё правильно, всё перепроверили, но матрица так и не работает или работает с артефактами, то попробуйте 
подключить пины отзеркалено, это связано с тем, что один из кабелей меняет распиновку. 

*******

## Особенности работы с матрицей ##

В матрицу стоит направлять пакеты данных размерностью 1 байт (8 бит), загружать можно как десятичные, так и двоичные 
числа, важно понимать, что каждый байт данных отвечает за часть строки. То есть байт данных принимает вид 11111111 -
при отравке такого байта данных - стрка потухнет или не будет гореть, так как управление светодиодами тут инверсивное
, то есть **1 - заставляет светодиод потухнуть, а 0 - зажечься**. 

Рассматривая матрицу, а именно её принципиальную схему или же при попытках выводить на неё изображение, мы замечаем,
что матрица разбита на **16 блоков** с размерностью **4(высота) x 8(длина)**.Представление одного таккого блока вы можете наблюдать на изображении ниже


![BIT_ON_BOX.png](Additional%20files%2FBIT_ON_BOX.png)

Разными цветами выделены разные строки. При загрузке данных, чтобы загружать данные в какую-то из строк необходимо 
выставить пины **A и B** в определённую комбинацию сигналов. Ниже приведена таблица, показывающся взаимодейсвтие 
строк и комбинаций каналов. Отмечу, что счёт начинается **СНИЗУ ВВЕРХ**.

![Line_chanal_A_and_B.png](Additional%20files%2FLine_chanal_A_and_B.png)

Загрузка данных в матрицу начинается с верхней правой ячейки с дальнейшим переходом сверху-вниз с постепенным заполнением 
матрицы. Из-за оосбенностей конструции матрицы, вы будете вынуждены загружать в неё информацию по 4 строки* за раз.
То есть для создания иллюзи изображения, вам будет необходимо переключатьсья между различными строками, постоянно загружая туда
данные. Однако, приведённое ниже изображение актуально исключительно как наглядное пособие.

**4 строки - под ними подрузамеваются все ячейки 4-рёх различных цветов, условно, строка номер 1 - красная, 2 - жёлтая
, 3 - оранжевая и т.д. На изображении ниже цифрами обозначен байт даных для каждой из строк*

![BOX_PANEL.png](Additional%20files%2FBOX_PANEL.png)

Для того, чтобы заполнить матрицу целиком и при этом все пакеты даннных встали на нужные позции. Нужно договориться
что мы заполняем всю матрицу целиком, в каждую из 4 строк загружаем по 16 байт данных. Так же стоит учесть, что загрузка 
данных в каждую из строк происходит методом **"проталкивания"**. То есть после загрузки первого байта данных, он встанет в 
позицию 1, при загрузке следом второго байта данных, первый байт данных сместится в позицию 2, а второй байт даных установится 
в позицию 1.

![BOX_PANEL_FOR_CODE.png](Additional%20files%2FBOX_PANEL_FOR_CODE.png)

Изображение выше наглядно показаывает положение каждого из байтов данных при последовательной загрузки всех 16-ти 
байтов для каждой из 4-х строк (64 байта данных на всю панель).

******************
## Настрйока микроконтроллера и SPI
![PINS_MK.png](Additional%20files%2FPINS_MK.png)

На изображении выше вы можете наблюдать изображение микроконтроллера с 
всеми активными пинами. В данном проекте используется **SPI5** *(могут быть активированы другие, 
однако, мне удолось достичь наиболее оптимальных параметров именно на SPI5 (могу порекомендовать 
применять SPI2 как альтернативу))*.

**Перечень используемых пинов**

- **PD4** - *A* - отвечает за выбор строки для загрузки данных
- **PD5** - *B* - отвечает за выбор строки для загрузки данных
- **PD6** - *OE* - отвечает за включение / выключение панели
- **PD7** - *SCLK* - канал для прменения полученных данных (необходимо 
подать высокий и следом сразу низкий сигнал)
- **PC14** - *RCC_OSC_32_IN* - канал для подключения внешнего тактового резонатора низкой частоты
- **PC15** - *RCC_OSC_32_OUT* - канал для подключения внешнего тактового резонатора низкой частоты
- **PF7** - *SPI5_SCK* - канал для тактирования ведомого устройства от ведущего
- **PF9** - *SPI5_MOSI* -канал для передачи данных
- **PH0** - *RCC_OSC_IN* - канал для подключения внешнего тактового резонатора высокой частоты
- **PH1** - *RCC_OSC_OUT* - канал для подключения внешнего тактового резонатора высокой частоты
- **PA4** - *ADC1_IN4* -канал с АЦП для снятия значения с реостата

![Setings_SPI5.png](Additional%20files%2FSetings_SPI5.png)

Выше вы можете наблюдать параметры настройки SPI5. Вы можете попробовать поменять 
Prescaler с целью улучшения качества изображения или же просто поэкспеременитровать.

В проекте не задействован ни один таймер, так как в нём нет необходимости,
так как в рамках проекта изначально планировалась возможность изменения скорости 
движения, однако, для этого вы можете найти в коде коэффициент **a** и изменить 
соответствующие ему параметры*.

**Орентироваться можете на коментарии внутри кода*
*******************
 ## Последовательность для загрузки данных в матрицу ###

1. Выдаём по SPI данные для сдвиговых регистров. Для одной матрицы 32x16 это 16 байт (16 8-битных регистров).
2. Устанавливаем лог. 0 на ножке nOE.
3. Устанавливаем лог. уровни на ножках A и B в соответствии с обновляемой группой светодиодов (одной из четырёх). Это подаёт +5В на аноды светодиодов выбранной группы.
4. Выдаём на ножку SCLK короткий положительный импульс. Это подаёт землю на катоды светодиодов в соответствии с загруженными в регистры байтами.
5. Устанавливаем лог. 1 на ножке nOE. При этом четверть экрана (одна группа светодиодов) загорается и горит до следующего обновления следующей группы светодиодов.
Повторяем пункты 1-5 с постоянным периодом.

*******************

## Листинги и описание, алгоритмы кода

Вся информация данного типа находится внутри отчёта, расположенного по адресу `/Additional files/Report`.

Описане кода находится внутри файлов `/Drive/Core/Src/main.c` и `Drive/Core/Src/display.c` в коде, вы можете орентироваться внутри кода на коментарии, оставленные к
каждой функции или частям кода, которые могут быть не совсем понятны

*******************
## Практическое подключение матрицы к STM32
Даное подключение актуально только для данного проекта, когда вы будете писать свой проект, то вам понадобиться 
опираться на приведённые выше изображения распиновки матрицы и подключать её к своей STM32 в соответсви с вашими 
пинами, активированными при формировании проекта в CubaMX.

**Пример подключения для STM32**

![STM32_NUCLEA.jpg](Additional%20files%2FSTM32_NUCLEA.jpg)

**Пример подключения для штекера**

![SHTECER.jpg](Additional%20files%2FSHTECER.jpg)

**Пример подключения для штекера, обратная сторона**

![SHTECER_2.jpg](Additional%20files%2FSHTECER_2.jpg)
*******************
 ## Демонстрация работы панели (старая версия) ###
![Work_code.gif](Additional%20files%2FWork_code.gif)


*******************
 ## Демонстрация работы панели (новая версия (актуальная)) ###
![Work_code._now.gif](Additional%20files%2FWork_code._now.gif)

Новая версия наследует все возможности старой, в дополнение имея лишь подвижные облака
