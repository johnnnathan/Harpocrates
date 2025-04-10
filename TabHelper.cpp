#include "TabHelper.h"

//Constructor for the dropdowns, usually the same so a waste to repeat self.
QComboBox* makeDropdown(){
    QComboBox *temp = new QComboBox();
    temp->addItem("Binary");
    temp->addItem("Decimal");
    temp->addItem("Hex");
    temp->addItem("ASCII");
    temp->addItem("AUTO");
    return temp;
}
