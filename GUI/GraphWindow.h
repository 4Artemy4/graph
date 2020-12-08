//
// Created by art on 11/29/20.
//

#ifndef LABA4_GRAPHWINDOW_H
#define LABA4_GRAPHWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <iostream>
#include <QtGui/QPainter>
#include "../gr/Graph.h"
#include "Node.h"

class GraphWindow : public QWidget {
private:
    graph::Graph<Node *, size_t> graph;
    QHBoxLayout *layout;
    QPushButton *addEdges;
    QPushButton *removeNodes;
public:
    GraphWindow(QWidget *parent) : QWidget(parent) {
        addEdges = new QPushButton("add/del arc between vertexes");
        connect(addEdges, &QPushButton::pressed, this, [=] {connectSelectedVertexes();});
        removeNodes = new QPushButton("remove nodes");
        connect(removeNodes, &QPushButton::pressed, this, [=] {removeSelectedNodes();});
        layout = new QHBoxLayout();
        layout->addWidget(addEdges);
        layout->addWidget(removeNodes);
        layout->setAlignment(Qt::Alignment::enum_type::AlignTop);
        this->setLayout(layout);
    }

public:
    void connectSelectedVertexes() {
        for (auto i = graph.beginE(); i != graph.endE(); i++) {
            if ((*(*i).iter1)->getIsSelected() && (*(*i).iter2)->getIsSelected() && (*i).iter2 != (*i).iter1) {
                if (*(*i).weight==0) graph.addEdge(i, 6);
                else graph.removeEdges(i);
            }
        }
        paintEvent(nullptr);
    }

    void removeSelectedNodes() {
        for (auto i = graph.beginV(); i != graph.endV(); ++i) {
            if ((*i)->getIsSelected()) {
                delete (*i);
                graph.removeVertex(i);
                --i;
            }
        }
        paintEvent(nullptr);
    }

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override{
        Node *temp = new Node(this);
        temp->move(this->mapFromGlobal(QCursor::pos()).x() - DIAMETER / 2,
                   this->mapFromGlobal(QCursor::pos()).y() - DIAMETER / 2);
        graph.addVertex(temp);
        paintEvent(nullptr);
    }

    void paintEvent(QPaintEvent *event) override {
        if(event == nullptr){
            for (auto i = graph.cbeginV(); i != graph.cendV(); ++i) (*i)->show();
            return;
        }
        QPainter painter(this);
        QPen pen;
        pen.setColor(QColor::fromRgb(50, 50, 200));
        pen.setWidth(5);
        painter.setPen(pen);
        for (auto i = graph.cbeginE(); i != graph.cendE(); ++i) {
            if (*(*i).weight != 0) {
                auto cord1 = (*(*i).iter1)->geometry();
                auto cord2 = (*(*i).iter2)->geometry();
                painter.drawLine(cord1.x()+DIAMETER/2, cord1.y()+DIAMETER/2, cord2.x()+DIAMETER/2, cord2.y()+DIAMETER/2);
            }
        }
        this->update();
    }

};


#endif //LABA4_GRAPHWINDOW_H
