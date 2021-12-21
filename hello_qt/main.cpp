#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QGridLayout>

int main(int argc, char** argv)
{
  QApplication application(argc, argv);
  QPushButton  button("Hello world!", nullptr);
  auto slider = new QSlider(Qt::Vertical);
  auto layout = new QGridLayout();

  layout->addWidget(slider, 0, 0);
//  layout->addWidget(spinBox, 0, 1);
//  layout->addWidget(resetButton, 2, 1);
  layout->setRowStretch(1, 1);
  //setLayout(layout);
  layout->layout();

  slider->setRange(8, 128);
  slider->setValue(6);
  slider->setObjectName("volume");

  button.resize(640, 480);
  button.show();
//  slider->show();

  QApplication::exec();

  return 0;
}
