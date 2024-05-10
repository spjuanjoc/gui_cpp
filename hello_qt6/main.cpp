#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>

int main(int argc, char** argv)
{
  QApplication application(argc, argv);
  QPushButton  button("Hello Qt6", nullptr);
  auto         slider = new QSlider(Qt::Vertical);
  auto         layout = new QGridLayout();

  layout->addWidget(slider, 0, 0);
  layout->setRowStretch(1, 1);
  layout->layout();

  slider->setRange(8, 128);
  slider->setValue(6);
  slider->setObjectName("volume");

  button.resize(640, 480);
  button.show();

  QApplication::exec();

  return 0;
}
