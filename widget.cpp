#include "widget.h"
#include "ui_widget.h"

/** Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    /// Устанавливаем параметры окна приложения
    this->resize(600,600);
    this->setFixedSize(600,600);

    ui->setupUi(this);
    scene   = new CustomScene();    /// Инициализируем кастомизированную сцену

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(0,0,520,520);   /// Устанавливаем размеры графической сцены

    /// Создаем кастомизированный курсор из ресурсного файла
    QCursor cursor = QCursor(QPixmap(":/cursor/cursorTarget.png"));
    ui->graphicsView->setCursor(cursor);    /// Устанавливаем курсор в QGraphicsView
    triangle = new Triangle();  /// Инициализируем треугольник
    triangle->setPos(60,60);  /// Устанавливаем стартовую позицию треугольника
    triangle->setZValue(2);
    scene->addItem(triangle);   /// Добавляем треугольник на графическую сцену

    /** Разрешаем отслеживание положение курсора мыши
     * без необходимости нажатия на кнопки мыши
     * Применяем это свойство именно для QGraphicsView,
     * в котором установлена графическая сцена
     * */
    ui->graphicsView->setMouseTracking(true);

    /// Подключаем сигнал от графической сцены к слоту треугольника
    connect(scene, &CustomScene::signalTargetCoordinate, triangle, &Triangle::slotTarget);
    /// Соединяем сигнала стрельбы с графической сцены со слотом разрешения стрельбы треугольника
    connect(scene, &CustomScene::signalShot, triangle, &Triangle::slotShot);
    /// Соединяем сигнал на создание пули со слотом, создающим пули в игре
    connect(triangle, &Triangle::signalBullet, this, &Widget::slotBullet);

    // Поставим стены
    scene->addRect(0,0,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,500,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(500,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(170,250,180,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(250,170,20,180,QPen(Qt::NoPen),QBrush(Qt::darkGray));

    /// Инициализируем таймер для создания мишеней
    timerTarget = new QTimer();
    connect(timerTarget, &QTimer::timeout, this, &Widget::slotCreateTarget);
    timerTarget->start(1500);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotBullet(QPointF start, QPointF end)
{
    /// Добавляем на сцену пулю
    Bullet *bullet = new Bullet(start, end, triangle);
    bullet->setCallbackFunc(slotHitTarget);
    scene->addItem(bullet);
}

void Widget::slotCreateTarget()
{
    Target *target = new Target();  /// Создаём цель
    scene->addItem(target);         /// Помещаем цель в сцену со случайной позицией
    target->setPos(qrand() % ((500 - 40 + 1) - 40) + 40,
                  qrand() % ((500 - 40 + 1) - 40) + 40);
    target->setZValue(-1);          /// Помещаем цель ниже Героя
    targets.append(target);         /// Добавляем цель в список
}

void Widget::slotHitTarget(QGraphicsItem *item)
{
    /** Получив сигнал от Пули
     * Перебираем весь список целей и наносим ему случайный урон
     * */
    foreach (QGraphicsItem *targ, targets) {
        if(targ == item){
            /// Кастуем объект из списка в класс Target
            Target *t = qgraphicsitem_cast <Target *> (targ);
            t->hit(randomBetween(1,3)); /// Наносим урон
        }
    }
}

QList<QGraphicsItem *> Widget::targets; /// реализация списка
