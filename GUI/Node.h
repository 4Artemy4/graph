//
// Created by art on 11/29/20.
//

#ifndef LABA4_NODE_H
#define LABA4_NODE_H

#define DIAMETER 60

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QShortcut>
#include <QMouseEvent>

class Node : public QPushButton {
    bool isSelected = false;
public:
    Node(QWidget *parent) : QPushButton(parent) {
        this->setMask(QRegion(0, 0, DIAMETER, DIAMETER, QRegion::Ellipse));
        this->setFixedWidth(DIAMETER);
        this->setFixedHeight(DIAMETER);
        this->setMask(QRegion(0, 0, DIAMETER, DIAMETER, QRegion::Ellipse));
        setColor(QColor::fromRgb(200, 10, 20));
        connect(this, &QPushButton::clicked, parent, [=]() {
            showConfDialog();
        });

    }

    bool getIsSelected() const {
        return isSelected;
    }

    void setIsSelected(const bool newValue) {
        isSelected = newValue;
    }

private:
    void setColor(const QColor &color) {
        this->setStyleSheet("border-style: solid;"
                            "border-width: 5px;"
                            "border-radius: " + QString::number(DIAMETER / 2) + "px;"
                            "border-color: " + color.name() + ";"
                            "font: bold 14px;"
        );
    }

    void showConfDialog() {
        auto *dialog = new QWidget();
        auto *layout = new QVBoxLayout();

        dialog->setGeometry(QCursor::pos().x() - 150, QCursor::pos().y() - 70, 300, 140);
        dialog->setWindowTitle(this->text());

        auto *aimLabel = new QLabel("Write Vertex Data");
        layout->addWidget(aimLabel);
        QFont f1 = aimLabel->font();
        f1.setPixelSize(14);
        aimLabel->setFont(f1);

        auto *aimEdit = new QLineEdit(this->text(), dialog);
        layout->addWidget(aimEdit);
        aimEdit->setFont(f1);

        auto *saveButton = new QPushButton("Save", dialog);
        layout->addWidget(saveButton);
        connect(saveButton, &QPushButton::pressed, dialog, [=] {
            dialog->setWindowTitle(aimEdit->text());
            this->setText(aimEdit->text());
            dialog->close();
        });

        dialog->setLayout(layout);
        dialog->show();
    }

    void mousePressEvent(QMouseEvent *e) override {
        if (e->button() == Qt::RightButton) {
            if (isSelected) setColor(QColor::fromRgb(200, 10, 20));
            else setColor(QColor::fromRgb(10, 200, 20));
            isSelected = !isSelected;
        }
        QAbstractButton::mousePressEvent(e);
    }

};

#endif //LABA4_NODE_H
