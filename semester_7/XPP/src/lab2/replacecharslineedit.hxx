#ifndef REPLACECHARSLINEEDIT_HXX
#define REPLACECHARSLINEEDIT_HXX

#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ReplaceCharsLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ReplaceCharsLineEdit(QWidget *parent = nullptr);

signals:

};

#endif // REPLACECHARSLINEEDIT_HXX
