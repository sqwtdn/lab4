# Code for model of pi^0 decay detection 

## GeometrySize.hh:
В этом файле содержится информация о размерах и параметрах геометрических объектов в симуляции, таких как размеры калориметров, детекторов или других частей эксперимента.

## TupleID.hh:
Нужен для идентификации секций калориметра и трекового детектора в левом и правом плечах.

## CalorimeterSensitiveDetector.hh:
Заголовочный файл, в котором подключаем библиотеки, задаем методы и переменные, нужные для файла *CalorimeterSensitiveDetector.cc*.

## CalorimeterSensitiveDetector.cc:
- **ProcessHits**: происходит обработка столкновений и накопление информации о событиях, в каком сегменте детекторной системы происходит передача энергии.
- **Initialize**: создание нулевого массива для левого и правого плеча калориметра.
- **EndOfEvent**: записываются результаты в ветки деревьев левого и правого плеча системы калориметров для анализа с помощью ROOT.

## MyDetectorConstruction.hh:
Заголовочный файл, в котором подключаем библиотеки, задаем методы и переменные, нужные для файла *MyDetectorConstruction.cc*.

## MyDetectorConstruction.cc:
- **Construct**: основной метод для построения геометрии детектора:
    1. задается мировой объем.
    2. задается сам детектор и положение в пространстве его левого и правого плеча.
- **defineMaterials**: задаются материалы объектов.
- **CreateCalorimeterSection**: создает и настраивает объемы секции калориметра, которая состоит из нескольких слоев.
- **CreateDetector**: создает детектор и его части, включая секции калориметра, трекового детектора и магнит.
    1. создается основной объем детектора.
    2. в цикле создаются несколько секций калориметра.
    3. создается магнит, который размещается в детекторе рядом с секциями трекового детектора.
- **CreateTrackingLayer**: создает и возвращает логический объем для слоя трекового детектора.
    1. создается основной и логический объем слоя.
    2. создается логический объем для кремниевой ячейки, которая будет размещена в слое.
    3. в цикле создаются и размещаются несколько кремниевых ячеек на сетке внутри слоя. Каждая ячейка имеет определенные координаты вдоль осей X и Y.
- **CreateTrackingSection**: создает и возвращает логический объем для сектора трекового детектора, состоящего из двух слоев.
    1. создается основной и логический объем сектора.
    2. вызывается метод `CreateTrackingLayer()`, чтобы создать слой трекового детектора.
    3. размещаются два слоя: правый и левый, с определенными смещениями вдоль оси Z.
- **CreateMagnet**: создается основной и логический объем магнита.
- **ConstructSDandField**: создает постоянное магнитное поле вдоль оси Y и настраивает менеджер поля для его применения к магнитному логическому объему. 
- **setupDetectors**: создает объекты для чувствительных детекторов калориметра и трекера, добавляет их в менеджер чувствительных детекторов и привязывает эти детекторы к соответствующим логическим объемам.

## MyPrimaryGenerator.hh:
Заголовочный файл, в котором подключаем библиотеки, задаем методы и переменные, нужные для файла *MyPrimaryGenerator.cc*.

## MyPrimaryGenerator.cc:
- **GeneratePrimaries**: для распада pi^0-мезона задается угол разлета между 0.1 и π - 0.1 радиан и устанавливаются стандартные параметры частицы (направление импульса, энергия), иначе генерирует первичные частицы (электрон и гамма-квант) с заданными параметрами.
- **MyPrimaryGenerator**: инициализирует генератор первичных частиц для одной частицы, создает объект `piDecay` для моделирования распада пиона и получает указатель на таблицу частиц, а также сохраняет флаг `isPiDecay`, определяющий режим генерации частиц.
- **деструктор**: удаляет данные.

## MyRunAction.hh:
Заголовочный файл, в котором подключаем библиотеки, задаем методы и переменные, нужные для файла *MyRunAction.cc*.

* MyRunAction.cc:
- **BeginOfRunAction**: открывает файл для сохранения данных (*PiDecay.root*) и создает деревья для хранения информации о калориметрах и трековых детекторах (для левых и правых плечей), настраивает ветви для сегментов калориметров и координат с временными метками для трековых детекторов.
- **EndOfRunAction**: завершает запись данных симуляции.

## PiDecayGenerator.hh:
Заголовочный файл, в котором подключаем библиотеки, задаем структуры, методы и переменные, нужные для файла *PiDecayGenerator.cc*.

## PiDecayGenerator.cc:
- **PiDecayGenerator**: инициализирует генератор случайных чисел.
- **decayPi**: моделирует распад pi^0-мезона. Случайное число выбирается с равномерным распределением. Если это число меньше вероятности распада на два фотона, вызывается метод `decayPiOnTwoPhotons()`. В противном случае происходит распад на электрон, позитрон и фотон, используя метод `decayPiOnElectrPositrAndPhoton()`.
- **decayPiOnTwoPhotons**: моделирует распад pi^0-мезона на два фотона. Сначала задаются импульс, углы phi и theta, задающие направление вылета первого фотона. Затем создаются два фотона с равными энергиями и противоположными импульсами. 
- **decayPiOnElectrPositrAndPhoton**: моделирует распад pi^0-мезона на электрон, позитрон и фотон. Сначала задаётся система отсчёта распада с полной энергией pi^0-мезона. Затем создаётся объект генерации распада TGenPhaseSpace, который настраивается на трёхчастичный распад с заданными массами продуктов. В цикле метод генерирует распад, сравнивает случайное число с весом события и извлекает параметры частиц (электрон, позитрон, фотон).

## TrackerSensitiveDetector.hh:
Заголовочный файл, в котором подключаем библиотеки, задаем структуры, методы и переменные, нужные для файла *TrackerSensitiveDetector.cc*.

## TrackerSensitiveDetector.cc:
- **ProcessHits**: обрабатывает взаимодействия частиц в чувствительном детекторе. Он проверяет, является ли частица первичной (созданной в первичном взаимодействии) и не фотоном. Если эти условия выполнены, он извлекает номер копии детектора, положение, глобальное время и энергию, переданную частицей. Затем создаётся объект `TrackerData`, который сохраняется в векторе `data` для последующего анализа.
- **Initialize**: инициализирует чувствительный детектор в начале каждого события и очищает вектор `data`, удаляя данные от предыдущего события.
- **EndOfEvent**: сохраняет данные о треках в конце каждого события. Он перебирает все данные о треках, собирая информацию о позиции и времени, и записывает их в соответствующие ветви дерева для левого или правого плечей детекторной системы.

## lab4.cc:
Инициализирует и запускает симуляцию в Geant4.

## start.mac:
Макрос, с помощью которого запускаем симуляцию 1000000 раз.

## vis.mac:
Макрос, отвечающий за визуализацию симуляции.
