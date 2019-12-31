#include "clickcombobox.h"
#include <QListView>

ClickComboBox::ClickComboBox(QWidget * parent):QComboBox(parent)
{
    ((QListView*)(view()))->setSpacing(8);
}

void ClickComboBox::focusInEvent(QFocusEvent *e)
{
    emit click();
    QComboBox::focusInEvent(e);
}
