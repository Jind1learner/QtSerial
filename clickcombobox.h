

#ifndef CLICKCOMBOBOX_H
#define CLICKCOMBOBOX_H

#include <QComboBox>
#include <QWidget>
#include <QMouseEvent>

class ClickComboBox : public QComboBox
{
    Q_OBJECT

public:
    ClickComboBox(QWidget * parent = 0);

protected:
    //virtual void mousePressEvent(QMouseEvent *e);
    virtual void focusInEvent(QFocusEvent *e);
    //virtual void mouseReleaseEvent(QMouseEvent * event );
signals:
    void click();
};

#endif // CLICKCOMBOBOX_H

